int
do_chase(struct thing *th)
{
    struct room *rer, *ree;	/* room of chaser, room of chasee */
    int mindist = 32767, i, dist;
    int stoprun = FALSE;	/* TRUE means we are there */
    int sch;
    coord this;				/* Temporary destination for chaser */

    rer = roomin(&th->t_pos);	/* Find room of chaser */
    ree = roomin(th->t_dest);	/* Find room of chasee */
    /*
     * We don't count doors as inside rooms for this routine
     */
    if (CMVWINCH(stdscr, th->t_pos.y, th->t_pos.x) == DOOR)
	rer = NULL;
    this = *th->t_dest;
    /*
     * If the object of our desire is in a different room, 
     * than we are and we ar not in a corridor, run to the
     * door nearest to our goal.
     */
    if (rer != NULL && rer != ree)
	for (i = 0; i < rer->r_nexits; i++)	/* loop through doors */
	{
	    dist = DISTANCE(th->t_dest->y, th->t_dest->x,
			    rer->r_exit[i].y, rer->r_exit[i].x);
	    if (dist < mindist)			/* minimize distance */
	    {
		this = rer->r_exit[i];
		mindist = dist;
	    }
	}
    /*
     * this now contains what we want to run to this time
     * so we run to it.  If we hit it we either want to fight it
     * or stop running
     */
    if (!chase(th, &this))
    {
	if (ce(this, hero))
	{
	    return( attack(th) );
	}
	else if (th->t_type != 'F')
	    stoprun = TRUE;
    }
    else if (th->t_type == 'F')
	return(0);
    mvwaddrawch(cw, th->t_pos.y, th->t_pos.x, th->t_oldch);
    sch = CMVWINCH(cw, ch_ret.y, ch_ret.x);
    if (rer != NULL && (rer->r_flags & ISDARK) && sch == FLOOR
	&& DISTANCE(ch_ret.y, ch_ret.x, th->t_pos.y, th->t_pos.x) < 3
	&& off(player, ISBLIND))
	    th->t_oldch = ' ';
    else
	th->t_oldch = sch;

    if (cansee(unc(ch_ret)) && !on(*th, ISINVIS))
        mvwaddrawch(cw, ch_ret.y, ch_ret.x, th->t_type);
    mvwaddrawch(mw, th->t_pos.y, th->t_pos.x, ' ');
    mvwaddrawch(mw, ch_ret.y, ch_ret.x, th->t_type);
    th->t_pos = ch_ret;
    /*
     * And stop running if need be
     */
    if (stoprun && ce(th->t_pos, *(th->t_dest)))
	th->t_flags &= ~ISRUN;

    return(0);
}