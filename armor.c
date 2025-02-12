/*
    armor.c  -  This file contains misc functions for dealing with armor
   
    UltraRogue
    Copyright (C) 1984, 1985, 1986, 1987, 1990, 1991 Herb Chong
    All rights reserved.
    
    Based on "Advanced Rogue"
    Copyright (C) 1983, 1984 Michael Morgan, Ken Dalka and AT&T
    All rights reserved.

    Based on "Super-Rogue"
    Copyright (C) 1982, 1983 Robert D. Kindelberger
    All rights reserved.

    Based on "Rogue: Exploring the Dungeons of Doom"
    Copyright (C) 1980, 1981 Michael Toy, Ken Arnold and Glenn Wichman
    All rights reserved.
    
    See the file LICENSE.TXT for full copyright and licensing information.
*/

#include "rogue.h"

/*
    wear()
	The player wants to wear something, so let him/her put it on.
*/

void
wear()
{
    struct object   *obj;

    if (cur_armor != NULL) {
	addmsg("You are already wearing some");
	if (!terse)
	    addmsg(".  You'll have to take it off first");
	addmsg(".");
	endmsg();
	after = FALSE;
	return;
    }

    /* What does player want to wear? */
    if ((obj = get_object(pack, "wear", ARMOR, NULL)) == NULL)
	return;

    wear_ok(&player, obj, MESSAGE);
    waste_time();
    addmsg(terse ? "W" : "You are now w");
    msg("earing %s.", armors[obj->o_which].a_name);
    cur_armor = obj;
    obj->o_flags |= ISKNOW;
}

/*
 * take_off: Get the armor off of the players back
 */

void
take_off()
{
    struct object   *obj;

    extern char print_letters[];

    if ((obj = cur_armor) == NULL) {
	msg("%s wearing armor!", terse ? "Not" : "You aren't");
	return;
    }
    if (!dropcheck(cur_armor))
	return;
    addmsg(terse ? "Was" : "You used to be");
    msg(" wearing %c%c) %s.", ARMOR, print_letters[get_ident(obj)],
	inv_name(obj, LOWERCASE));
    cur_armor = NULL;
    if (on(player, STUMBLER)) {
	msg("Your foot feels a lot better now.");
	turn_off(player, STUMBLER);
    }
}


/*
 * wear_ok: enforce player class armor restrictions
 */

int
wear_ok(struct thing *wearee, struct object *obj, bool print_message)
{
    int which = obj->o_which;
    bool    ret_val = TRUE;
    int class_type = wearee->t_ctype;

    if (obj->o_type != ARMOR) {
	ret_val = FALSE;
	return (ret_val);
    }
    else
	switch (class_type) {
	    when    C_MAGICIAN: /* cannot wear metal */
	    case C_ILLUSION:
		switch (which) {
		    case RING_MAIL:
		    case SCALE_MAIL:
		    case PADDED_ARMOR:
		    case CHAIN_MAIL:
		    case BRIGANDINE:
		    case SPLINT_MAIL:
		    case GOOD_CHAIN:
		    case PLATE_MAIL:
		    case PLATE_ARMOR:
		    ret_val = FALSE;
		    otherwise:
		    break;
		}
	    when    C_THIEF:    /* cannot clank around */
	    case C_ASSASIN:
	    case C_NINJA:
		switch (which) {
		    case CHAIN_MAIL:
		    case BRIGANDINE:
		    case SPLINT_MAIL:
		    case GOOD_CHAIN:
		    case PLATE_MAIL:
		    case PLATE_ARMOR:
		    ret_val = FALSE;
		    otherwise:
		    break;
		}
	    when    C_CLERIC:   /* cannot wear plate */
	    case C_DRUID:
		switch (which) {
		    case PLATE_MAIL:
		    case PLATE_ARMOR:
		    case MITHRIL:
		    ret_val = FALSE;
		    otherwise:
		    break;
		}
	    case C_FIGHTER: /* wear anything */
	    case C_RANGER:
		break;
	    when    C_PALADIN:  /* cannot wear common stuff */
		switch (which) {
		    case SOFT_LEATHER:
		    case CUIRBOLILLI:
		    case HEAVY_LEATHER:
		    case STUDDED_LEATHER:
		    case PADDED_ARMOR:
		    case BRIGANDINE:
		    ret_val = FALSE;
		    otherwise:
		    break;
		}
	    case C_MONSTER:
		break;
	    otherwise:      /* Unknown class */
		debug("Unknown class %d.", class_type);
		break;
	}

    if (ret_val == FALSE && print_message == MESSAGE)
	switch (class_type) {
	    when    C_MAGICIAN:
	    case C_ILLUSION:
		msg("You cannot regenerate spell points while wearing that!");
	    when    C_THIEF:
	    case C_ASSASIN:
	    case C_NINJA:
		msg("Don't expect to be stealty while wearing that!");
	    when    C_CLERIC:
	    case C_DRUID:
	    case C_PALADIN:
		msg("Your god strongly disapproves of your wearing that!");
	    case C_FIGHTER:
	    case C_RANGER:
	    case C_MONSTER:
		break;
	}
    return (ret_val);
}
