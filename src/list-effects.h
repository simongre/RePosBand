/*
 * File: list-effects.h
 * Purpose: List of effect types
 */

/*
 * "rating" is the power rating for an item activation, as a damage-per-blow
 * equivalent (x2). These ratings are used in the calculation of the power (and
 * therefore cost) of an item which has the effect as an activation, but NOT
 * for other items (e.g. potions, scrolls). Hence the use of INIHIBIT_POWER.
 */

/*     name            aim?   rating	short description	*/
EFFECT(XXX,            FALSE,  0,	NULL)
EFFECT(POISON,         FALSE,  0,	"poisons you for 2d7+10 turns")
EFFECT(BLIND,          FALSE,  0,	"blinds you for 4d25+75 turns")
EFFECT(SCARE,          FALSE,  0,	"induces fear in you for 1d10+10 turns")
EFFECT(CONFUSE,        FALSE,  0,	"confuses you for 4d5+10 turns")
EFFECT(HALLUC,         FALSE,  0,	"causes you to hallucinate")
EFFECT(PARALYZE,       FALSE,  0,	"induces paralysis for 1d5+5 turns")
EFFECT(SLOW,           FALSE,  0,	"slows you for 1d25+15 turns")

EFFECT(CURE_POISON,    FALSE,  1,	"neutralizes poison")
EFFECT(CURE_BLINDNESS, FALSE,  4,	"cures blindness")
EFFECT(CURE_PARANOIA,  FALSE,  2,	"removes your fear")
EFFECT(CURE_CONFUSION, FALSE,  4,	"cures confusion")
EFFECT(CURE_MIND,      FALSE,  8,	"cures confusion and hallucination, removes fear and grants you temporary resistance to confusion")
EFFECT(CURE_BODY,      FALSE,  7,	"heals cut damage, and cures stunning, poison and blindness")

EFFECT(CURE_LIGHT,     FALSE,  5,	"heals you a small amount (15% of your wounds, minimum 15HP), heals some cut damage, makes you a little less confused, and cures blindness")
EFFECT(CURE_SERIOUS,   FALSE,  8,	"heals you a fair amount (1/5 of your wounds, minimum 25HP), heals cut damage, and cures blindness and confusion")
EFFECT(CURE_CRITICAL,  FALSE, 10,	"heals you a large amount (1/4 of your wounds, minimum 30HP), heals cut damage, and cures stunning, poisoning, blindness, and confusion")
EFFECT(CURE_FULL,      FALSE, 12,	"heals you a really large amount (35% of max HP, minimum 300HP), heals cut damage, and cures stunning, poisoning, blindness, and confusion")
EFFECT(CURE_FULL2,     FALSE, 18,	"restores 1200 hit points, heals cut damage, and cures stunning, poisoning, blindness, and confusion")
EFFECT(CURE_NONORLYBIG,FALSE, 21,	"restores 5000 hit points, restores experience and stats, heals cut damage, and cures stunning, poison, blindness, and confusion")
EFFECT(CURE_TEMP,      FALSE,  9,	"heals cut damage, and cures all stunning, poison, blindness and confusion")
EFFECT(HEAL1,          FALSE, 13,	"heals 500 hit points")
EFFECT(HEAL2,          FALSE, 16,	"heals 1000 hit points")
EFFECT(HEAL3,          FALSE, 14,	"heals 500 hit points, heals cut damage, and cures stunning")

EFFECT(GAIN_EXP,       FALSE, INHIBIT_POWER, "grants 100,000 experience points")
EFFECT(LOSE_EXP,       FALSE,  0,	"drains a quarter of your experience")
EFFECT(RESTORE_EXP,    FALSE,  8,	"restores your experience")

EFFECT(RESTORE_MANA,   FALSE, 20,	"restores your mana points to maximum")

EFFECT(GAIN_STR,       FALSE, INHIBIT_POWER, "restores and increases your strength")
EFFECT(GAIN_INT,       FALSE, INHIBIT_POWER, "restores and increases your intelligence")
EFFECT(GAIN_WIS,       FALSE, INHIBIT_POWER, "restores and increases your wisdom")
EFFECT(GAIN_DEX,       FALSE, INHIBIT_POWER, "restores and increases your dexterity")
EFFECT(GAIN_CON,       FALSE, INHIBIT_POWER, "restores and increases your constitution")
EFFECT(GAIN_CHR,       FALSE, INHIBIT_POWER, "restores and increases your charisma")
EFFECT(GAIN_ALL,       FALSE, INHIBIT_POWER, "restores and increases all your stats")
EFFECT(BRAWN,          FALSE, 30,	"raises your strength at the expense of a random attribute")
EFFECT(INTELLECT,      FALSE, 25,	"raises your intelligence at the expense of a random attribute")
EFFECT(CONTEMPLATION,  FALSE, 25,	"raises your wisdom at the expense of a random attribute")
EFFECT(TOUGHNESS,      FALSE, 30,	"raises your constitution at the expense of a random attribute")
EFFECT(NIMBLENESS,     FALSE, 25,	"raises your dexterity at the expense of a random attribute")
EFFECT(PLEASING,       FALSE,  5,	"raises your charisma at the expense of a random attribute")
EFFECT(LOSE_STR,       FALSE,  0,	"reduces your strength with damage 5d5")
EFFECT(LOSE_INT,       FALSE,  0,	"reduces your intelligence with damage 5d5")
EFFECT(LOSE_WIS,       FALSE,  0,	"reduces your wisdom with damage 5d5")
EFFECT(LOSE_DEX,       FALSE,  0,	"reduces your dexterity with damage 5d5")
EFFECT(LOSE_CON,       FALSE,  0,	"reduces your constitution with damage 5d5")
EFFECT(LOSE_CHR,       FALSE,  0,	"reduces your intelligence with damage 5d5")
EFFECT(LOSE_CON2,      FALSE,  0,	"reduces your constitution with damage 10d10")
EFFECT(RESTORE_STR,    FALSE, 10,	"restores your strength")
EFFECT(RESTORE_INT,    FALSE,  8,	"restores your intelligence")
EFFECT(RESTORE_WIS,    FALSE,  8,	"restores your wisdom")
EFFECT(RESTORE_DEX,    FALSE,  9,	"restores your dexterity")
EFFECT(RESTORE_CON,    FALSE, 10,	"restores your constitution")
EFFECT(RESTORE_CHR,    FALSE,  4,	"restores your charisma")
EFFECT(RESTORE_ALL,    FALSE, 15,	"restores all your stats")

EFFECT(RESTORE_ST_LEV, FALSE, 17,	"restores all your stats and your experience points")

EFFECT(TMD_INFRA,      FALSE,  5,	"extends your infravision by 50 feet for 4d25+100 turns")
EFFECT(TMD_SINVIS,     FALSE,  7,	"cures blindness and allows you to see invisible things for 2d6+12 turns")
EFFECT(TMD_ESP,        FALSE, 10,	"cures blindness and gives you telepathy for 6d6+12 turns")

EFFECT(ENLIGHTENMENT,  FALSE, 22,	"completely lights up and magically maps the level")
EFFECT(ENLIGHTENMENT2, FALSE, INHIBIT_POWER, "increases your intelligence and wisdom, detects and maps everything in the surrounding area, and identifies all items in your pack")

EFFECT(HERO,           FALSE,  7,	"restores 10 hit points, removes fear and grants you resistance to fear and +12 to-hit for 1d25+25 turns")
EFFECT(SHERO,          FALSE,  9,	"restores 30 hit points, removes fear and grants you resistance to fear, +24 to-hit, and -10AC for 1d25+25 turns")

EFFECT(RESIST_ACID,    FALSE,  4,	"grants temporary resistance to acid for 1d10+10 turns")
EFFECT(RESIST_ELEC,    FALSE,  4,	"grants temporary resistance to electricity for 1d10+10 turns")
EFFECT(RESIST_FIRE,    FALSE,  4,	"grants temporary resistance to fire for 1d10+10 turns")
EFFECT(RESIST_COLD,    FALSE,  4,	"grants temporary resistance to cold for 1d10+10 turns")
EFFECT(RESIST_POIS,    FALSE,  4,	"grants temporary resistance to poison for 1d10+10 turns")
EFFECT(RESIST_ALL,     FALSE, 10,	"grants temporary resistance to acid, electricity, fire, cold and poison for 1d20+20 turns")

EFFECT(DETECT_TREASURE,   FALSE,  6,	"detects gold and objects nearby")
EFFECT(DETECT_TRAP,       FALSE,  6,	"detects traps nearby")
EFFECT(DETECT_DOORSTAIR,  FALSE,  6,	"detects doors and stairs nearby")
EFFECT(DETECT_INVIS,      FALSE,  6,	"detects invisible creatures nearby")
EFFECT(DETECT_EVIL,       FALSE,  6,	"detects evil creatures nearby")
EFFECT(DETECT_ALL,        FALSE, 10,	"detects treasure, traps, doors, stairs, and all creatures nearby")

EFFECT(ENCHANT_TOHIT,  FALSE, 15,	"attempts to magically enhance a weapon's to-hit bonus")
EFFECT(ENCHANT_TODAM,  FALSE, 20,	"attempts to magically enhance a weapon's to-dam bonus")
EFFECT(ENCHANT_WEAPON, FALSE, 22,	"attempts to magically enhance a weapon both to-hit and to-dam")
EFFECT(ENCHANT_ARMOR,  FALSE, 12,	"attempts to magically enhance a piece of armour")
EFFECT(ENCHANT_ARMOR2, FALSE, 15,	"attempts to magically enhance a piece of armour with high chance of success")
EFFECT(IDENTIFY,       FALSE,  9,	"reveals to you the extent of an item's magical powers")
EFFECT(REMOVE_CURSE,   FALSE,  8,	"removes all ordinary curses from all equipped items")
EFFECT(REMOVE_CURSE2,  FALSE, 20,	"removes all curses from all equipped items")
EFFECT(LIGHT,          FALSE,  4,	"lights up an area and inflicts 2d8 damage on light-sensitive creatures")
EFFECT(SUMMON_MON,     FALSE,  0,	"summons monsters at the current dungeon level")
EFFECT(SUMMON_UNDEAD,  FALSE,  0,	"summons undead monsters at the current dungeon level")
EFFECT(TELE_PHASE,     FALSE,  5,	"teleports you randomly up to 10 squares away")
EFFECT(TELE_LONG,      FALSE,  6,	"teleports you randomly up to 100 squares away")
EFFECT(TELE_LEVEL,     FALSE, 15,	"teleports you one level up or down")
EFFECT(CONFUSING,      FALSE,  8,	"causes your next attack upon a monster to confuse it")
EFFECT(MAPPING,        FALSE, 10,	"maps the area around you")
EFFECT(RUNE,           FALSE, 20,	"inscribes a glyph of warding beneath you, which monsters cannot move onto")

EFFECT(ACQUIRE,        FALSE, INHIBIT_POWER, "creates a good object nearby")
EFFECT(ACQUIRE2,       FALSE, INHIBIT_POWER, "creates a few good items nearby")
EFFECT(ANNOY_MON,      FALSE,  0,	"awakens all nearby sleeping monsters and hastens all monsters within line of sight")
EFFECT(CREATE_TRAP,    FALSE,  0,	"creates traps surrounding you")
EFFECT(DESTROY_TDOORS, FALSE,  6,	"destroys all traps and doors surrounding you")
EFFECT(RECHARGE,       FALSE, 11,	"tries to recharge a wand or staff, destroying the wand or staff on failure")
EFFECT(BANISHMENT,     FALSE, 20,	"removes all non-unique monsters represented by a chosen symbol from the level, dealing you damage in the process")
EFFECT(DARKNESS,       FALSE,  0,	"darkens the nearby area and blinds you for 1d5+3 turns")
EFFECT(PROTEVIL,       FALSE,  6,	"grants you protection from evil for 1d25 plus 3 times your character level turns")
EFFECT(SATISFY,        FALSE,  7,	"magically renders you well-fed, curing any gastrointestinal problems")
EFFECT(CURSE_WEAPON,   FALSE,  0,	"curses your currently wielded melee weapon")
EFFECT(CURSE_ARMOR,    FALSE,  0,	"curses your currently worn body armor")
EFFECT(BLESSING,       FALSE,  6,	"increases your AC and to-hit bonus for 1d12+6 turns")
EFFECT(BLESSING2,      FALSE,  7,	"increases your AC and to-hit bonus for 1d24+12 turns")
EFFECT(BLESSING3,      FALSE,  8,	"increases your AC and to-hit bonus for 1d48+24 turns")
EFFECT(RECALL,         FALSE, 15,	"returns you from the dungeon or takes you to the dungeon after a short delay")
EFFECT(DEEP_DESCENT,   FALSE, 19,	"teleports you two levels down")

EFFECT(EARTHQUAKES,    FALSE,  5,	"causes an earthquake around you")
EFFECT(DESTRUCTION2,   FALSE, 12,	"destroys an area around you in the shape of a circle radius 15, and blinds you for 1d10+10 turns")

EFFECT(LOSHASTE,       FALSE,  0,	"hastes all monsters within line of sight")
EFFECT(LOSSLOW,        FALSE,  7,	"slows all non-unique monsters within line of sight")
EFFECT(LOSSLEEP,       FALSE,  8,	"sleeps all non-unique creatures within line of sight")
EFFECT(LOSCONF,        FALSE, 10,	"confuses all non-unique creatures within line of sight")
EFFECT(LOSKILL,        FALSE, 25,	"removes all non-unique monsters within 20 squares, dealing you damage in the process")
EFFECT(ILLUMINATION,   FALSE,  4,	"lights up the surrounding area, hurting light-sensitive creatures")
EFFECT(CLAIRVOYANCE,   FALSE, 23,	"maps the entire level and detects nearby objects, traps, doors, and stairs")
EFFECT(PROBING,        FALSE,  8,	"gives you information on the health and abilities of monsters you can see")

EFFECT(HASTE,          FALSE, 10,	"hastens you for 2d10+20 turns")
EFFECT(HASTE1,         FALSE, 10,	"hastens you for d20+20 turns")
EFFECT(HASTE2,         FALSE, 13,	"hastens you for d75+75 turns")

EFFECT(DISPEL_EVIL,    FALSE, 12,	"deals five times your level's damage to all evil creatures that you can see")
EFFECT(DISPEL_EVIL60,  FALSE,  9,	"deals 60 damage to all evil creatures that you can see")
EFFECT(DISPEL_UNDEAD,  FALSE,  9,	"deals 60 damage to all undead creatures that you can see")
EFFECT(DISPEL_ALL,     FALSE, 11,	"deals 120 damage to all creatures that you can see")

EFFECT(SLEEPII,        FALSE,  8,	"puts to sleep the monsters around you")
EFFECT(STAR_BALL,      FALSE, 18,	"fires a ball of electricity in all directions, each one causing 150 damage")
EFFECT(RAGE_BLESS_RESIST, FALSE, 21,	"bestows upon you berserk rage, bless, and resistance")
EFFECT(RESTORE_LIFE,   FALSE,  8,	"restores your experience to full")
EFFECT(REM_FEAR_POIS,  FALSE,  3,	"cures you of fear and poison")
EFFECT(FIREBRAND,      FALSE, 25,	"brands bolts with fire, in an unbalanced fashion")

EFFECT(FIRE_BOLT,      TRUE,   5,	"creates a fire bolt with damage 9d8")
EFFECT(FIRE_BOLT2,     TRUE,   7,	"creates a fire bolt with damage 12d8")
EFFECT(FIRE_BOLT3,     TRUE,   9,	"creates a fire bolt with damage 16d8")
EFFECT(FIRE_BOLT72,    TRUE,   9,	"creates a fire ball with damage 72")
EFFECT(FIRE_BALL,      TRUE,  11,	"creates a fire ball with damage 144")
EFFECT(FIRE_BALL2,     TRUE,  11,	"creates a large fire ball with damage 120")
EFFECT(FIRE_BALL200,   TRUE,  13,	"creates a large fire ball with damage 200")
EFFECT(COLD_BOLT,      TRUE,   4,	"creates a frost bolt with damage 6d8")
EFFECT(COLD_BOLT2,     TRUE,   7,	"creates a frost bolt with damage 12d8")
EFFECT(COLD_BALL2,     TRUE,  13,	"creates a large frost ball with damage 200")
EFFECT(COLD_BALL50,    TRUE,   8,	"creates a frost ball with damage 50")
EFFECT(COLD_BALL100,   TRUE,  10,	"creates a frost ball with damage 100")
EFFECT(COLD_BALL160,   TRUE,  12,	"creates a frost ball with damage 160")
EFFECT(ACID_BOLT,      TRUE,   4,	"creates an acid bolt with damage 5d8")
EFFECT(ACID_BOLT2,     TRUE,   6,	"creates an acid bolt with damage 10d8")
EFFECT(ACID_BOLT3,     TRUE,   7,	"creates an acid bolt with damage 12d8")
EFFECT(ACID_BALL,      TRUE,  11,	"creates an acid ball with damage 125")
EFFECT(ELEC_BOLT,      TRUE,   5,	"creates a lightning bolt (that always beams) with damage 6d6")
EFFECT(ELEC_BALL,      TRUE,   9,	"creates a lightning ball with damage 64")
EFFECT(ELEC_BALL2,     TRUE,  14,	"creates a large lightning ball with damage 250")

EFFECT(DRAIN_LIFE1,    TRUE,   9,	"drains up to 90 hit points of life from a target creature")
EFFECT(DRAIN_LIFE2,    TRUE,  10,	"drains up to 120 hit points of life from a target creature")
EFFECT(DRAIN_LIFE3,    TRUE,  11,	"drains up to 150 hit points of life from a target creature")
EFFECT(DRAIN_LIFE4,    TRUE,  12,	"drains up to 250 hit points of life from a target creature")
EFFECT(MISSILE,        TRUE,   3,	"fires a magic missile with damage 3d4")
EFFECT(MANA_BOLT,      TRUE,   7,	"fires a mana bolt with damage 12d8")
EFFECT(BIZARRE,        TRUE,  20,	"does bizarre things")
EFFECT(ARROW,          TRUE,  11,	"fires a magical arrow with damage 150")
EFFECT(STINKING_CLOUD, TRUE,   3,	"fires a stinking cloud with damage 12")
EFFECT(STONE_TO_MUD,   TRUE,   6,	"turns rock into mud")
EFFECT(TELE_OTHER,     TRUE,  11,	"teleports a target monster away")
EFFECT(CONFUSE2,       TRUE,   3,	"confuses a target monster")

EFFECT(MON_HEAL,       TRUE,   0,	"heals a single monster 4d6 hit points")
EFFECT(MON_HASTE,      TRUE,   0,	"hastes a single monster")
EFFECT(MON_SLOW,       TRUE,   3,	"attempts to magically slow a single monster")
EFFECT(MON_CONFUSE,    TRUE,   3,	"attempts to magically confuse a single monster")
EFFECT(MON_SLEEP,      TRUE,   3,	"attempts to induce magical sleep in a single monster")
EFFECT(MON_CLONE,      TRUE,   0,	"hastes, heals, and magically duplicates a single monster")
EFFECT(MON_SCARE,      TRUE,   3,	"attempts to induce magical fear in a single monster")

EFFECT(LIGHT_LINE,     TRUE,   6,	"lights up part of the dungeon in a straight line")
EFFECT(DISARMING,      TRUE,   7,	"destroys traps, unlocks doors and reveals all secret doors in a given direction")
EFFECT(TDOOR_DEST,     TRUE,   5,	"destroys traps and doors")
EFFECT(POLYMORPH,      TRUE,   7,	"polymorphs a monster into another kind of creature")

EFFECT(STARLIGHT,      FALSE,  5,	"fires a line of light in all directions, each one causing light-sensitive creatures 6d8 damage")
EFFECT(STARLIGHT2,     FALSE,  7,	"fires a line of light in all directions, each one causing 10d8 damage")
EFFECT(BERSERKER,      FALSE, 10,	"puts you in a berserker rage for d50+50 turns")

EFFECT(WONDER,         TRUE,   9,	"creates random and unpredictable effects")

EFFECT(WAND_BREATH,    TRUE,  12,	"shoots a large ball of one of the base elements for 120-200 damage")
EFFECT(STAFF_MAGI,     FALSE, 20,	"restores both intelligence and manapoints to maximum")
EFFECT(STAFF_HOLY,     FALSE, 12,	"inflicts damage on evil creatures you can see, cures 50 hit points, heals all temporary effects and grants you protection from evil")
EFFECT(DRINK_GOOD,     FALSE,  0,	NULL)
EFFECT(DRINK_BREATH,   TRUE,   8,	"causes you to breathe either cold or flames for 80 damage")
EFFECT(DRINK_SALT,     FALSE,  0,	"induces vomiting and paralysis for 4 turns, resulting in severe hunger but also curing poison")
EFFECT(DRINK_DEATH,    FALSE,  0,	"inflicts 5000 points of damage")
EFFECT(DRINK_RUIN,     FALSE,  0,	"inflicts 10d10 points of damage and decreases all your stats")
EFFECT(DRINK_DETONATE, FALSE,  0,	"inflicts 50d20 points of damage, severe cuts, and stunning")
EFFECT(FOOD_GOOD,      FALSE,  0,	NULL)
EFFECT(FOOD_WAYBREAD,  FALSE,  4,	"restores 4d8 hit points and neutralizes poison")
EFFECT(SHROOM_EMERGENCY, FALSE, 7,	"grants temporary resistance to fire and cold, cures 200HP, but also makes you hallucinate wildly")
EFFECT(SHROOM_TERROR,    FALSE, 5,	"speeds up you temporarily but also makes you mortally afraid")
EFFECT(SHROOM_STONE,     FALSE, 5,	"turns your skin to stone briefly, which grants an extra 40AC but slows you down")
EFFECT(SHROOM_DEBILITY,  FALSE, 5,	"restores some mana but also drains either your strength or constitution")
EFFECT(SHROOM_SPRINTING, FALSE, 5,	"hastes you for a while, but then makes you slower for a while afterward")
EFFECT(SHROOM_PURGING,  FALSE, 5,	"makes you very hungry but restores constitution and strength")
EFFECT(RING_ACID,      TRUE,  11,	"grants acid resistance for d20+20 turns and creates an acid ball of damage 70")
EFFECT(RING_FLAMES,    TRUE,  11,	"grants fire resistance for d20+20 turns and creates a fire ball of damage 80")
EFFECT(RING_ICE,       TRUE,  11,	"grants cold resistance for d20+20 turns and creates a cold ball of damage 75")
EFFECT(RING_LIGHTNING, TRUE,  11,	"grants electricity resistance for d20+20 turns and creates a lightning ball of damage 85")

EFFECT(DRAGON_BLUE,    TRUE,   18,	"allows you to breathe lightning for 100 damage")
EFFECT(DRAGON_GREEN,   TRUE,   19,	"allows you to breathe poison gas for 150 damage")
EFFECT(DRAGON_RED,     TRUE,   20,	"allows you to breathe fire for 200 damage")
EFFECT(DRAGON_MULTIHUED, TRUE, 20,	"allows you to breathe the elements for 250 damage")
EFFECT(DRAGON_BRONZE,  TRUE,   INHIBIT_POWER,	"allows you to breathe confusion for 120 damage")
EFFECT(DRAGON_GOLD,    TRUE,   19,	"allows you to breathe sound for 130 damage")
EFFECT(DRAGON_CHAOS,   TRUE,   23,	"allows you to breathe chaos or disenchantment for 220 damage")
EFFECT(DRAGON_LAW,     TRUE,   23,	"allows you to breathe sound/shards for 230 damage")
EFFECT(DRAGON_BALANCE, TRUE,   24,	"allows you to breathe balance for 250 damage")
EFFECT(DRAGON_SHINING, TRUE,   21,	"allows you to breathe light or darkness for 200 damage")
EFFECT(DRAGON_POWER,   TRUE,   25,	"allows you to breathe for 300 damage")

EFFECT(TRAP_DOOR,      FALSE,  0,	"a trap door which drops you down a level")
EFFECT(TRAP_PIT,       FALSE,  0,	"a pit trap - the fall might hurt")
EFFECT(TRAP_PIT_SPIKES, FALSE, 0,	 "a pit trap, with nasty spikes")
EFFECT(TRAP_PIT_POISON, FALSE, 0,	"a pit trap, with poisoned spikes")
EFFECT(TRAP_RUNE_SUMMON, FALSE, 0,	"a rune which summons monsters")
EFFECT(TRAP_RUNE_TELEPORT, FALSE, 0,	"a rune which teleports")
EFFECT(TRAP_SPOT_FIRE, FALSE,  0,	"a magical fire trap")
EFFECT(TRAP_SPOT_ACID, FALSE,  0,	"a magical acid trap")
EFFECT(TRAP_DART_SLOW, FALSE,  0,	"a dart which slows movements")
EFFECT(TRAP_DART_LOSE_STR, FALSE, 0,	"a dart which drains strength")
EFFECT(TRAP_DART_LOSE_DEX, FALSE, 0,	"a dart which drains dexterity")
EFFECT(TRAP_DART_LOSE_CON, FALSE, 0,	"a dart which drains constitution")
EFFECT(TRAP_GAS_BLIND, FALSE,  0,	"blinding gas")
EFFECT(TRAP_GAS_CONFUSE, FALSE, 0,	"confusing gas")
EFFECT(TRAP_GAS_POISON, FALSE, 0,	"poison gas")
EFFECT(TRAP_GAS_SLEEP, FALSE,  0,	"soporific gas")
