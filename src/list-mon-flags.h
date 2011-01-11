/* list-mon-flags.h - monster race flags
 *
 * Changing flag order will break savefiles. There is a hard-coded limit of
 * 96 flags, due to 12 bytes of storage for lore flags in the savefile. Flags
 * below start from 1 on line 11, so a flag's sequence number is its line
 * number minus 10.
 */

/* symbol       descr */
RF(NONE,        "")
RF(UNIQUE,      "")
RF(QUESTOR,     "")
RF(MALE,        "")
RF(FEMALE,      "")
RF(CHAR_CLEAR,  "")
RF(CHAR_MULTI,  "")
RF(ATTR_CLEAR,  "")
RF(ATTR_MULTI,  "")
RF(FORCE_DEPTH, "")
RF(XXX1,        "")
RF(FORCE_SLEEP, "")
RF(FORCE_EXTRA, "")
RF(FRIEND,      "")
RF(FRIENDS,     "")
RF(ESCORT,      "")
RF(ESCORTS,     "")
RF(NEVER_BLOW,  "")
RF(NEVER_MOVE,  "")
RF(RAND_25,     "")
RF(RAND_50,     "")
RF(ONLY_GOLD,   "")
RF(ONLY_ITEM,   "")
RF(DROP_40,     "")
RF(DROP_60,     "")
RF(DROP_1,      "")
RF(DROP_2,      "")
RF(DROP_3,      "")
RF(DROP_4,      "")
RF(DROP_GOOD,   "")
RF(DROP_GREAT,  "")
RF(DROP_20,     "")
RF(DROP_CHOSEN, "")
RF(STUPID,      "")
RF(SMART,       "")
RF(HAS_LITE,    "")
RF(ATTR_FLICKER, "")
RF(INVISIBLE,   "")
RF(COLD_BLOOD,  "")
RF(EMPTY_MIND,  "")
RF(WEIRD_MIND,  "")
RF(MULTIPLY,    "")
RF(REGENERATE,  "")
RF(LAWFUL,      "")
RF(CHAOTIC,     "")
RF(POWERFUL,    "")
RF(XXX6,        "")
RF(XXX7,        "")
RF(XXX8,        "")
RF(OPEN_DOOR,   "")
RF(BASH_DOOR,   "")
RF(PASS_WALL,   "")
RF(KILL_WALL,   "")
RF(MOVE_BODY,   "")
RF(KILL_BODY,   "")
RF(TAKE_ITEM,   "")
RF(KILL_ITEM,   "")
RF(BRAIN_1,     "")
RF(BRAIN_2,     "")
RF(BRAIN_3,     "")
RF(BRAIN_4,     "")
RF(BRAIN_5,     "")
RF(BRAIN_6,     "")
RF(BRAIN_7,     "")
RF(BRAIN_8,     "")
RF(ORC,         "")
RF(TROLL,       "")
RF(GIANT,       "")
RF(DRAGON,      "")
RF(DEMON,       "")
RF(UNDEAD,      "")
RF(EVIL,        "")
RF(ANIMAL,      "")
RF(METAL,       "")
RF(XXX9,        "")
RF(XXX10,       "")
RF(XXX11,       "")
RF(HURT_LIGHT,  "")
RF(HURT_ROCK,   "")
RF(HURT_FIRE,   "")
RF(HURT_COLD,   "")
RF(IM_ACID,     "")
RF(IM_ELEC,     "")
RF(IM_FIRE,     "")
RF(IM_COLD,     "")
RF(IM_POIS,     "")
RF(XXX12,       "")
RF(RES_NETH,    "")
RF(IM_WATER,    "")
RF(RES_PLAS,    "")
RF(RES_NEXUS,   "")
RF(RES_DISE,    "")
RF(XXX13,       "")
RF(NO_FEAR,     "")
RF(NO_STUN,     "")
RF(NO_CONF,     "")
RF(NO_SLEEP,    "")
RF(HAS_LIGHT,	"")
RF(VALA,		"")
RF(BRTH_DISEN,	"")
/* end flags */
