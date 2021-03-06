/*
 * File: cmd-obj.c
 * Purpose: Handle objects in various ways
 *
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke
 * Copyright (c) 2007-9 Andrew Sidwell, Chris Carr, Ed Graham, Erik Osheim
 *
 * This work is free software; you can redistribute it and/or modify it
 * under the terms of either:
 *
 * a) the GNU General Public License as published by the Free Software
 *    Foundation, version 2, or
 *
 * b) the "Angband licence":
 *    This software may be copied and distributed for educational, research,
 *    and not for profit purposes provided that this copyright and statement
 *    are included in all such copies.  Other copyrights may also apply.
 */

#include "reposband.h"
#include "cave.h"
#include "cmds.h"
#include "effects.h"
#include "game-cmd.h"
#include "object/object.h"
#include "object/inventory.h"
#include "object/tvalsval.h"
#include "spells.h"
#include "target.h"

/*** Utility bits and bobs ***/

/*
 * Check to see if the player can use a rod/wand/staff/activatable object.
 */
static int check_devices(object_type *o_ptr)
{
	int fail;
	const char *msg;
	const char *what = NULL;

	/* Get the right string */
	switch (o_ptr->tval)
	{
		case TV_ROD:   msg = "zap the rod";   break;
		case TV_WAND:  msg = "use the wand";  what = "wand";  break;
		case TV_STAFF: msg = "use the staff"; what = "staff"; break;
		default:       msg = "activate it";  break;
	}

	/* Figure out how hard the item is to use */
	fail = get_use_device_chance(o_ptr);

	/* Roll for usage */
	if (randint1(1000) < fail)
	{
		flush();
		msg_format("You failed to %s properly.", msg);
		return FALSE;
	}

	/* Notice empty staffs */
	if (what && o_ptr->pval <= 0)
	{
		flush();
		msg_format("The %s has no charges left.", what);
		o_ptr->ident |= (IDENT_EMPTY);
		return FALSE;
	}

	return TRUE;
}


/*
 * Return the chance of an effect beaming, given a tval.
 */
static int beam_chance(int tval)
{
	switch (tval)
	{
		case TV_WAND: return 20;
		case TV_ROD:  return 10;
	}

	return 0;
}


typedef enum {
	ART_TAG_NONE,
	ART_TAG_NAME,
	ART_TAG_KIND,
	ART_TAG_VERB,
	ART_TAG_VERB_IS
} art_tag_t;

static art_tag_t art_tag_lookup(const char *tag)
{
	if (strncmp(tag, "name", 4) == 0)
		return ART_TAG_NAME;
	else if (strncmp(tag, "kind", 4) == 0)
		return ART_TAG_KIND;
	else if (strncmp(tag, "s", 1) == 0)
		return ART_TAG_VERB;
	else if (strncmp(tag, "is", 2) == 0)
		return ART_TAG_VERB_IS;
	else
		return ART_TAG_NONE;
}

/*
 * Print an artifact activation message.
 *
 * In order to support randarts, with scrambled names, we re-write
 * the message to replace instances of {name} with the artifact name
 * and instances of {kind} with the type of object.
 *
 * This code deals with plural and singular forms of verbs correctly
 * when encountering {s}, though in fact both names and kinds are
 * always singular in the current code (gloves are "Set of" and boots
 * are "Pair of")
 */
static void activation_message(object_type *o_ptr, const char *message)
{
	char buf[1024] = "\0";
	const char *next;
	const char *s;
	const char *tag;
	const char *in_cursor;
	size_t end = 0;

	in_cursor = message;

	next = strchr(in_cursor, '{');
	while (next)
	{
		/* Copy the text leading up to this { */
		strnfcat(buf, 1024, &end, "%.*s", next - in_cursor, in_cursor); 

		s = next + 1;
		while (*s && isalpha((unsigned char) *s)) s++;

		if (*s == '}')		/* Valid tag */
		{
			tag = next + 1; /* Start the tag after the { */
			in_cursor = s + 1;

			switch(art_tag_lookup(tag))
			{
			case ART_TAG_NAME:
				end += object_desc(buf, 1024, o_ptr, ODESC_PREFIX | ODESC_BASE); 
				break;
			case ART_TAG_KIND:
				object_kind_name(&buf[end], 1024-end, o_ptr->k_idx, TRUE);
				end += strlen(&buf[end]);
				break;
			case ART_TAG_VERB:
				strnfcat(buf, 1024, &end, "s");
				break;
			case ART_TAG_VERB_IS:
				if((end > 2) && (buf[end-2] == 's'))
					strnfcat(buf, 1024, &end, "are");
				else
					strnfcat(buf, 1024, &end, "is");
			default:
				break;
			}
		}
		else    /* An invalid tag, skip it */
		{
			in_cursor = next + 1;
		}

		next = strchr(in_cursor, '{');
	}
	strnfcat(buf, 1024, &end, in_cursor);

	msg_print(buf);
}



/*** Inscriptions ***/

/* Remove inscription */
void do_cmd_uninscribe(cmd_code code, cmd_arg args[])
{
	object_type *o_ptr = object_from_item_idx(args[0].item);

	if (obj_has_inscrip(o_ptr))
		msg_print("Inscription removed.");

	o_ptr->note = 0;

	p_ptr->notice |= (PN_COMBINE | PN_SQUELCH | PN_SORT_QUIVER);
	p_ptr->redraw |= (PR_INVEN | PR_EQUIP);
}

/* Add inscription */
void do_cmd_inscribe(cmd_code code, cmd_arg args[])
{
	object_type *o_ptr = object_from_item_idx(args[0].item);

	o_ptr->note = quark_add(args[1].string);

	p_ptr->notice |= (PN_COMBINE | PN_SQUELCH | PN_SORT_QUIVER);
	p_ptr->redraw |= (PR_INVEN | PR_EQUIP);
}


/*** Taking off/putting on ***/

/* Take off an item */
void do_cmd_takeoff(cmd_code code, cmd_arg args[])
{
	int item = args[0].item;
	
	if (!item_is_available(item, NULL, USE_EQUIP))
	{
		msg_print("You are not wielding that item.");
		return;
	}

	if (!obj_can_takeoff(object_from_item_idx(item)))
	{
		msg_print("You cannot take off that item.");
		return;
	}

	(void)inven_takeoff(item, 255);
	pack_overflow();
	p_ptr->energy_use = 50;
}


/*
 * Wield or wear a single item from the pack or floor
 */
void wield_item(object_type *o_ptr, int item, int slot)
{
	object_type object_type_body;
	object_type *i_ptr = &object_type_body;

	cptr fmt;
	char o_name[80];

	bool combined_ammo = FALSE;
	int num = 1;

	/* If we are stacking ammo in the quiver */
	if (obj_is_ammo(o_ptr))
	{
		num = o_ptr->number;
		combined_ammo = object_similar(o_ptr, &p_ptr->inventory[slot],
			OSTACK_QUIVER);
	}

	/* Take a turn */
	p_ptr->energy_use = 100;

	/* Obtain local object */
	object_copy(i_ptr, o_ptr);

	/* Modify quantity */
	i_ptr->number = num;

	/* Decrease the item (from the pack) */
	if (item >= 0)
	{
		inven_item_increase(item, -num);
		inven_item_optimize(item);
	}

	/* Decrease the item (from the floor) */
	else
	{
		floor_item_increase(0 - item, -num);
		floor_item_optimize(0 - item);
	}

	/* Get the wield slot */
	o_ptr = &p_ptr->inventory[slot];

	if (combined_ammo)
	{
		/* Add the new ammo to the already-quiver-ed ammo */
		object_absorb(o_ptr, i_ptr);
	}
	else 
	{
		/* Take off existing item */
		if (o_ptr->k_idx)
			(void)inven_takeoff(slot, 255);

		/* If we are wielding ammo we may need to "open" the slot by shifting
		 * later ammo up the quiver; this is because we already called the
		 * inven_item_optimize() function. */
		if (slot >= QUIVER_START)
			open_quiver_slot(slot);
	
		/* Wear the new stuff */
		object_copy(o_ptr, i_ptr);

		/* Increment the equip counter by hand */
		p_ptr->equip_cnt++;
	}

	/* Increase the weight */
	p_ptr->total_weight += i_ptr->weight * num;

	/* Do any ID-on-wield */
	object_notice_on_wield(o_ptr);

	/* Where is the item now */
	if (slot == INVEN_WIELD)
		fmt = "You are wielding %s (%c).";
	else if (slot == INVEN_BOW)
		fmt = "You are shooting with %s (%c).";
	else if (slot == INVEN_LIGHT)
		fmt = "Your light source is %s (%c).";
	else if (combined_ammo)
		fmt = "You combine %s in your quiver (%c).";
	else if (slot >= QUIVER_START && slot < QUIVER_END)
		fmt = "You add %s to your quiver (%c).";
	else
		fmt = "You are wearing %s (%c).";

	/* Describe the result */
	object_desc(o_name, sizeof(o_name), o_ptr, ODESC_PREFIX | ODESC_FULL);

	/* Message */
	message_format(MSG_WIELD, 0, fmt, o_name, index_to_label(slot));

	/* Cursed! */
	if (cursed_p(o_ptr))
	{
		/* Warn the player */
		message_format(MSG_CURSED, 0, "Oops! It feels deathly cold!");

		/* Sense the object */
		object_notice_curses(o_ptr);
	}

	/* Save quiver size */
	save_quiver_size(p_ptr);

	/* See if we have to overflow the pack */
	pack_overflow();

	/* Recalculate bonuses, torch, mana */
	p_ptr->notice |= PN_SORT_QUIVER;
	p_ptr->update |= (PU_BONUS | PU_TORCH | PU_MANA);
	p_ptr->redraw |= (PR_INVEN | PR_EQUIP);
}


/* Wield or wear an item */
void do_cmd_wield(cmd_code code, cmd_arg args[])
{
	object_type *equip_o_ptr;
	char o_name[80];

	unsigned n;

	int item = args[0].item;
	int slot = args[1].number;
	object_type *o_ptr = object_from_item_idx(item);

	if (!item_is_available(item, NULL, USE_INVEN | USE_FLOOR))
	{
		msg_print("You do not have that item to wield.");
		return;
	}

	/* Check the slot */
	if (!slot_can_wield_item(slot, o_ptr))
	{
		msg_print("You cannot wield that item there.");
		return;
	}

	equip_o_ptr = &p_ptr->inventory[slot];

	/* If the slot is open, wield and be done */
	if (!equip_o_ptr->k_idx) 
	{
		wield_item(o_ptr, item, slot);
		return;
	}

	/* If the slot is in the quiver and objects can be combined */
	if (obj_is_ammo(equip_o_ptr) && object_similar(equip_o_ptr, o_ptr,
		OSTACK_QUIVER))
	{
		wield_item(o_ptr, item, slot);
		return;
	}

	/* Prevent wielding into a cursed slot */
	if (cursed_p(equip_o_ptr))
	{
		object_desc(o_name, sizeof(o_name), equip_o_ptr, ODESC_BASE);
		msg_format("The %s you are %s appears to be cursed.", o_name,
				   describe_use(slot));
		return;
	}

	/* "!t" checks for taking off */
	n = check_for_inscrip(equip_o_ptr, "!t");
	while (n--)
	{
		/* Prompt */
		object_desc(o_name, sizeof(o_name), equip_o_ptr,
					ODESC_PREFIX | ODESC_FULL);
		
		/* Forget it */
		if (!get_check(format("Really take off %s? ", o_name))) return;
	}

	wield_item(o_ptr, item, slot);
}

/* Drop an item */
void do_cmd_drop(cmd_code code, cmd_arg args[])
{
	int item = args[0].item;
	object_type *o_ptr = object_from_item_idx(item);
	int amt = args[1].number;

	if (!item_is_available(item, NULL, USE_INVEN | USE_EQUIP))
	{
		msg_print("You do not have that item to drop it.");
		return;
	}

	/* Hack -- Cannot remove cursed items */
	if ((item >= INVEN_WIELD) && cursed_p(o_ptr))
	{
		msg_print("Hmmm, it seems to be cursed.");
		return;
	}

	inven_drop(item, amt);
	p_ptr->energy_use = 50;
}

/* Destroy an item */
void do_cmd_destroy(cmd_code code, cmd_arg args[])
{
	object_type *o_ptr;
	int item = args[0].item;

	if (!item_is_available(item, NULL, USE_INVEN | USE_EQUIP | USE_FLOOR))
	{
		msg_print("You do not have that item to ignore it.");
		return;
	}

	o_ptr = object_from_item_idx(item);

	if ((item >= INVEN_WIELD) && cursed_p(o_ptr)) {
		msg_print("You cannot ignore cursed items.");
	} else {	
		char o_name[80];

		object_desc(o_name, sizeof o_name, o_ptr, ODESC_PREFIX | ODESC_FULL);
		message_format(MSG_DESTROY, 0, "Ignoring %s.", o_name);

		o_ptr->ignore = TRUE;
		p_ptr->notice |= PN_SQUELCH;
	}
}



/*** Using items the traditional way ***/

/*
 * Use an object the right way.
 *
 * There may be a BIG problem with any "effect" that can cause "changes"
 * to the inventory.  For example, a "scroll of recharging" can cause
 * a wand/staff to "disappear", moving the inventory up.  Luckily, the
 * scrolls all appear BEFORE the staffs/wands, so this is not a problem.
 * But, for example, a "staff of recharging" could cause MAJOR problems.
 * In such a case, it will be best to either (1) "postpone" the effect
 * until the end of the function, or (2) "change" the effect, say, into
 * giving a staff "negative" charges, or "turning a staff into a stick".
 * It seems as though a "rod of recharging" might in fact cause problems.
 * The basic problem is that the act of recharging (and destroying) an
 * item causes the inducer of that action to "move", causing "o_ptr" to
 * no longer point at the correct item, with horrifying results.
 */
void do_cmd_use(cmd_code code, cmd_arg args[])
{
	int item = args[0].item;
	object_type *o_ptr = object_from_item_idx(item);
	int effect;
	bool ident = FALSE, used = FALSE;
	bool was_aware = object_flavor_is_aware(o_ptr);
	int dir = 5;
	int px = p_ptr->px, py = p_ptr->py;
	int snd, boost, level;
	use_type use;
	int items_allowed = 0;

	/* Determine how this item is used. */
	if (obj_is_rod(o_ptr))
	{
		if (!obj_can_zap(o_ptr))
		{
			msg_print("That rod is still charging.");
			return;
		}

		use = USE_TIMEOUT;
		snd = MSG_ZAP_ROD;
		items_allowed = USE_INVEN | USE_FLOOR;
	}
	else if (obj_is_wand(o_ptr))
	{
		if (!obj_has_charges(o_ptr))
		{
			msg_print("That wand has no charges.");
			return;
		}

		use = USE_CHARGE;
		snd = MSG_ZAP_ROD;
		items_allowed = USE_INVEN | USE_FLOOR;
	}
	else if (obj_is_staff(o_ptr))
	{
		if (!obj_has_charges(o_ptr))
		{
			msg_print("That staff has no charges.");
			return;
		}

		use = USE_CHARGE;
		snd = MSG_USE_STAFF;
		items_allowed = USE_INVEN | USE_FLOOR;
	}
	else if (obj_is_food(o_ptr))
	{
		use = USE_SINGLE;
		snd = MSG_EAT;
		items_allowed = USE_INVEN | USE_FLOOR;
	}
	else if (obj_is_potion(o_ptr))
	{
		use = USE_SINGLE;
		snd = MSG_QUAFF;
		items_allowed = USE_INVEN | USE_FLOOR;
	}
	else if (obj_is_scroll(o_ptr))
	{
		/* Check player can use scroll */
		if (!player_can_read())
			return;

		use = USE_SINGLE;
		snd = MSG_GENERIC;
		items_allowed = USE_INVEN | USE_FLOOR;
	}
	else if (obj_is_activatable(o_ptr))
	{
		if (!obj_can_activate(o_ptr))
		{
			msg_print("That item is still charging.");
			return;
		}

		use = USE_TIMEOUT;
		snd = MSG_ACT_ARTIFACT;
		items_allowed = USE_EQUIP;
	}
	else
	{
		msg_print("The item cannot be used at the moment");
	}

	/* Check if item is within player's reach. */
	if (items_allowed == 0 || !item_is_available(item, NULL, items_allowed))
	{
		msg_print("You cannot use that item from its current location.");
		return;
	}

	/* track the object used */
	track_object(item);

	/* Figure out effect to use */
	effect = object_effect(o_ptr);

	/* If the item requires a direction, get one (allow cancelling) */
	if (obj_needs_aim(o_ptr))
		dir = args[1].direction;

	/* Check for use if necessary, and execute the effect */
	if ((use != USE_CHARGE && use != USE_TIMEOUT) ||
	    check_devices(o_ptr))
	{
		/* Special message for artifacts */
		if (artifact_p(o_ptr))
		{
			message(snd, 0, "You activate it.");
			if (a_info[o_ptr->name1].effect_msg)
				activation_message(o_ptr, a_info[o_ptr->name1].effect_msg);
			level = a_info[o_ptr->name1].level;
		}
		else
		{
			/* Make a noise! */
			sound(snd);
			level = k_info[o_ptr->k_idx].level;
		}

		/* A bit of a hack to make ID work better.
			-- Check for "obvious" effects beforehand. */
		if (effect_obvious(effect)) object_flavor_aware(o_ptr);

		/* Boost damage effects if skill > difficulty */
		boost = p_ptr->state.skills[SKILL_DEVICE] - level;
		if (boost < 0) boost = 0;

		/* Do effect */
		used = effect_do(effect, &ident, was_aware, dir,
			beam_chance(o_ptr->tval), boost);

		/* Quit if the item wasn't used and no knowledge was gained */
		if (!used && (was_aware || !ident)) return;
	}

	/* If the item is a null pointer or has been wiped, be done now */
	if (!o_ptr || o_ptr->k_idx <= 1) return;

	if (ident) object_notice_effect(o_ptr);

	/* Food feeds the player */
	if (o_ptr->tval == TV_FOOD || o_ptr->tval == TV_POTION)
		(void)set_food(p_ptr->food + o_ptr->pval);

	/* Use the turn */
	p_ptr->energy_use = 100;

	/* Mark as tried and redisplay */
	p_ptr->notice |= (PN_COMBINE | PN_REORDER);
	p_ptr->redraw |= (PR_INVEN | PR_EQUIP | PR_OBJECT);

	/*
	 * If the player becomes aware of the item's function, then mark it as
	 * aware and reward the player with some experience.  Otherwise, mark
	 * it as "tried".
	 */
	if (ident && !was_aware)
	{
		/* Object level */
		int lev = k_info[o_ptr->k_idx].level;

		object_flavor_aware(o_ptr);
		if (o_ptr->tval == TV_ROD) object_notice_everything(o_ptr);
		gain_exp((lev + (p_ptr->lev / 2)) / p_ptr->lev);
		p_ptr->notice |= PN_SQUELCH;
	}
	else if (used)
	{
		object_flavor_tried(o_ptr);
	}

	/* If there are no more of the item left, then we're done. */
	if (!o_ptr->number) return;

	/* Chargeables act differently to single-used items when not used up */
	if (used && use == USE_CHARGE)
	{
		/* Use a single charge */
		o_ptr->pval--;

		/* Describe charges */
		if (item >= 0)
			inven_item_charges(item);
		else
			floor_item_charges(0 - item);
	}
	else if (used && use == USE_TIMEOUT)
	{
		/* Artifacts use their own special field */
		if (o_ptr->name1)
		{
			const artifact_type *a_ptr = &a_info[o_ptr->name1];
			o_ptr->timeout = randcalc(a_ptr->time, 0, RANDOMISE);
		}
		else
		{
			const object_kind *k_ptr = &k_info[o_ptr->k_idx];
			o_ptr->timeout += randcalc(k_ptr->time, 0, RANDOMISE);
		}
	}
	else if (used && use == USE_SINGLE)
	{
		/* Destroy a potion in the pack */
		if (item >= 0)
		{
			inven_item_increase(item, -1);
			inven_item_describe(item);
			inven_item_optimize(item);
		}

		/* Destroy a potion on the floor */
		else
		{
			floor_item_increase(0 - item, -1);
			floor_item_describe(0 - item);
			floor_item_optimize(0 - item);
		}
	}
	
	/* Hack to make Glyph of Warding work properly */
	if (cave_feat[py][px] == FEAT_GLYPH)
	{
		/* Shift any objects to further away */
		for (o_ptr = get_first_object(py, px); o_ptr; o_ptr =
			get_next_object(o_ptr))
		{
			drop_near(o_ptr, 0, py, px, FALSE);
		}

		/* Delete the "moved" objects from their original position */
		delete_object(py, px);
	}


}


/*** Refuelling ***/

static void refill_lamp(object_type *j_ptr, object_type *o_ptr, int item)
{
	/* Refuel */
	j_ptr->timeout += o_ptr->timeout ? o_ptr->timeout : o_ptr->pval;

	/* Message */
	msg_print("You fuel your lamp.");

	/* Comment */
	if (j_ptr->timeout >= FUEL_LAMP)
	{
		j_ptr->timeout = FUEL_LAMP;
		msg_print("Your lamp is full.");
	}

	/* Refilled from a lantern */
	if (o_ptr->sval == SV_LIGHT_LANTERN)
	{
		/* Unstack if necessary */
		if (o_ptr->number > 1)
		{
			object_type *i_ptr;
			object_type object_type_body;

			/* Get local object */
			i_ptr = &object_type_body;

			/* Obtain a local object */
			object_copy(i_ptr, o_ptr);

			/* Modify quantity */
			i_ptr->number = 1;

			/* Remove fuel */
			i_ptr->timeout = 0;

			/* Unstack the used item */
			o_ptr->number--;
			p_ptr->total_weight -= i_ptr->weight;

			/* Carry or drop */
			if (item >= 0)
				item = inven_carry(p_ptr, i_ptr);
			else
				drop_near(i_ptr, 0, p_ptr->py, p_ptr->px, FALSE);
		}

		/* Empty a single lantern */
		else
		{
			/* No more fuel */
			o_ptr->timeout = 0;
		}

		/* Combine / Reorder the pack (later) */
		p_ptr->notice |= (PN_COMBINE | PN_REORDER);

		/* Redraw stuff */
		p_ptr->redraw |= (PR_INVEN);
	}

	/* Refilled from a flask */
	else
	{
		/* Decrease the item (from the pack) */
		if (item >= 0)
		{
			inven_item_increase(item, -1);
			inven_item_describe(item);
			inven_item_optimize(item);
		}

		/* Decrease the item (from the floor) */
		else
		{
			floor_item_increase(0 - item, -1);
			floor_item_describe(0 - item);
			floor_item_optimize(0 - item);
		}
	}

	/* Recalculate torch */
	p_ptr->update |= (PU_TORCH);

	/* Redraw stuff */
	p_ptr->redraw |= (PR_EQUIP);
}


static void refuel_torch(object_type *j_ptr, object_type *o_ptr, int item)
{
	bitflag f[OF_SIZE];
	bitflag g[OF_SIZE];

	/* Refuel */
	j_ptr->timeout += o_ptr->timeout + 5;

	/* Message */
	msg_print("You combine the torches.");

	/* Transfer the LIGHT flag if refuelling from a torch with it to one
	   without it */
	object_flags(o_ptr, f);
	object_flags(j_ptr, g);
	if (of_has(f, OF_LIGHT) && !of_has(g, OF_LIGHT))
	{
		of_on(j_ptr->flags, OF_LIGHT);
		if (!j_ptr->name2 && o_ptr->name2)
			j_ptr->name2 = o_ptr->name2;
		msg_print("Your torch shines further!");
	}

	/* Over-fuel message */
	if (j_ptr->timeout >= FUEL_TORCH)
	{
		j_ptr->timeout = FUEL_TORCH;
		msg_print("Your torch is fully fueled.");
	}

	/* Refuel message */
	else
	{
		msg_print("Your torch glows more brightly.");
	}

	/* Decrease the item (from the pack) */
	if (item >= 0)
	{
		inven_item_increase(item, -1);
		inven_item_describe(item);
		inven_item_optimize(item);
	}

	/* Decrease the item (from the floor) */
	else
	{
		floor_item_increase(0 - item, -1);
		floor_item_describe(0 - item);
		floor_item_optimize(0 - item);
	}

	/* Recalculate torch */
	p_ptr->update |= (PU_TORCH);

	/* Redraw stuff */
	p_ptr->redraw |= (PR_EQUIP);
}


void do_cmd_refill(cmd_code code, cmd_arg args[])
{
	object_type *j_ptr = &p_ptr->inventory[INVEN_LIGHT];
	bitflag f[OF_SIZE];

	int item = args[0].item;
	object_type *o_ptr = object_from_item_idx(item);

	if (!item_is_available(item, NULL, USE_INVEN | USE_FLOOR))
	{
		msg_print("You do not have that item to refill with it.");
		return;
	}

	/* Check what we're wielding. */
	object_flags(j_ptr, f);

	if (j_ptr->tval != TV_LIGHT)
	{
		msg_print("You are not wielding a light.");
		return;
	}

	else if (of_has(f, OF_NO_FUEL))
	{
		msg_print("Your light cannot be refilled.");
		return;
	}

	/* It's a lamp */
	if (j_ptr->sval == SV_LIGHT_LANTERN)
		refill_lamp(j_ptr, o_ptr, item);

	/* It's a torch */
	else if (j_ptr->sval == SV_LIGHT_TORCH)
		refuel_torch(j_ptr, o_ptr, item);

	p_ptr->energy_use = 50;
}



/*** Spell casting ***/

/* Gain a specific spell, specified by spell number (for mages). */
void do_cmd_study_spell(cmd_code code, cmd_arg args[])
{
	int spell = args[0].choice;

	int item_list[INVEN_TOTAL + MAX_FLOOR_STACK];
	int item_num;
	int i;

	/* Check the player can study at all atm */
	if (!player_can_study())
		return;

	/* Check that the player can actually learn the nominated spell. */
	item_tester_hook = obj_can_browse;
	item_num = scan_items(item_list, N_ELEMENTS(item_list), (USE_INVEN | USE_FLOOR));

	/* Check through all available books */
	for (i = 0; i < item_num; i++)
	{
		if (spell_in_book(spell, item_list[i]))
		{
			if (spell_okay_to_study(spell))
			{
				/* Spell is in an available book, and player is capable. */
				spell_learn(spell);
				p_ptr->energy_use = 100;
			}
			else
			{
				/* Spell is present, but player incapable. */
				msg_format("You cannot learn that spell.");
			}

			return;
		}
	}
}

/* Cast a spell from a book */
void do_cmd_cast(cmd_code code, cmd_arg args[])
{
	int spell = args[0].choice;
	int dir = args[1].direction;

	int item_list[INVEN_TOTAL + MAX_FLOOR_STACK];
	int item_num;
	int i;

	cptr verb = ((cp_ptr->spell_book == TV_MAGIC_BOOK) ? "cast" : "recite");
	cptr noun = ((cp_ptr->spell_book == TV_MAGIC_BOOK) ? "spell" : "prayer");

	/* Check the player can cast spells at all */
	if (!player_can_cast())
		return;

	/* Check spell is in a book they can access */
	item_tester_hook = obj_can_browse;
	item_num = scan_items(item_list, N_ELEMENTS(item_list), (USE_INVEN | USE_FLOOR));

	/* Check through all available books */
	for (i = 0; i < item_num; i++)
	{
		if (spell_in_book(spell, item_list[i]))
		{
			if (spell_okay_to_cast(spell))
			{
				/* Get the spell */
				const magic_type *s_ptr = &mp_ptr->info[spell];	
				
				/* Verify "dangerous" spells */
				if (s_ptr->smana > p_ptr->csp)
				{
					/* Warning */
					msg_format("You do not have enough mana to %s this %s.", verb, noun);
					
					/* Flush input */
					flush();
					
					/* Verify */
					if (!get_check("Attempt it anyway? ")) return;
				}

				/* Cast a spell */
				if (spell_cast(spell, dir))
					p_ptr->energy_use = 100;
			}
			else
			{
				/* Spell is present, but player incapable. */
				msg_format("You cannot %s that %s.", verb, noun);
			}

			return;
		}
	}

}


/* Gain a random spell from the given book (for priests) */
void do_cmd_study_book(cmd_code code, cmd_arg args[])
{
	int book = args[0].item;
	object_type *o_ptr = object_from_item_idx(book);

	int spell = -1;
	int i, k = 0;

	cptr p = ((cp_ptr->spell_book == TV_MAGIC_BOOK) ? "spell" : "prayer");

	/* Check the player can study at all atm */
	if (!player_can_study())
		return;

	/* Check that the player has access to the nominated spell book. */
	if (!item_is_available(book, obj_can_browse, (USE_INVEN | USE_FLOOR)))
	{
		msg_format("That item is not within your reach.");
		return;
	}

	/* Extract spells */
	for (i = 0; i < SPELLS_PER_BOOK; i++)
	{
		int s = get_spell_index(o_ptr, i);
		
		/* Skip non-OK spells */
		if (s == -1) continue;
		if (!spell_okay_to_study(s)) continue;
		
		/* Apply the randomizer */
		if ((++k > 1) && (randint0(k) != 0)) continue;
		
		/* Track it */
		spell = s;
	}

	if (spell < 0)
	{
		msg_format("You cannot learn any %ss in that book.", p);
	}
	else
	{
		spell_learn(spell);
		p_ptr->energy_use = 100;	
	}
}
