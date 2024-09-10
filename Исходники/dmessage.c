/* NOT [BDyess] 8/22/95 */
void
dmessage(char *message, unsigned int flags, unsigned int from, unsigned int to)
{
    struct distress dist;
    int len;
    /*char dead[20], alive[20];*/

    /* aha! A new type distress/macro call came in. parse it appropriately */
    if (F_gen_distress && (flags == (MTEAM | MDISTR | MVALID))) {
	if (paradise)
	    printf("RCD: %s\n", message);
	HandleGenDistr(message, from, to, &dist);
	len = makedistress(&dist, message, distmacro[dist.distype].macro);
	if (UseLite)
	    rcdlite(&dist);
	if (len <= 0)
	    return;
	flags ^= MDISTR;
    }
    /*
       keep track of how many queued messages there are for use with the
       infoIcon [BDyess]
    */
    if (infoIcon) {
	if (to == me->p_no && flags & MINDIV) {	/* personal message */
	    me_messages++;
	} else if (flags & MTEAM) {	/* team message */
	    team_messages++;
	} else {		/* message for all */
	    all_messages++;
	}
	if (iconified)
	    drawIcon();
    }
    logit(message);

    /*
       fix for upgrade bug.  Forced UDP would resend numbers, (thinking them
       speed changes) screwing up upgrading on those twinkish sturgeon
       servers. [BDyess]
    */
    if (strncmp(message, "UPG->", 5) == 0)
	upgrading = 1;
    if (upgrading && !(me->p_flags & PFORBIT))
	upgrading = 0;

    if ((from != me->p_no) || pigSelf)
	rsvp_borg_call(message, from);

    /* beep when a personal message is sent while iconified [BDyess] */
    if (to == me->p_no && (flags & MINDIV) && iconified) {
	W_Beep();
    }
    if (from == 255 &&
	strcmp(message, "Tractor beam aborted warp engagement") == 0) {
	me->p_flags &= ~PFWARPPREP;
    }
    /* want a warning for personal kills, so check here [BDyess] */
    /* and personal deaths [BDyess] */
    if(strncmp(message,"GOD->ALL",8) && (0 == strcmp(message,pseudo))) {
      hwarning(message+9);
    }
    print_message(message, flags, from, to);
}