void
wanderer(void)
{
    int i, cnt = 0;
    struct room *hr = roomin(hero);
    struct linked_list  *item;
    struct thing    *tp;
    coord   cp;
    char    *loc;
    int which;

    /* Find a place for it -- avoid the player's room */

    do
    {
        do
        {
            cnt++;
            i = rnd_room();
        }
        while (!(hr != &rooms[i] || levtype == MAZELEV
               || levtype == THRONE || cnt > 5000));

        rnd_pos(&rooms[i], &cp);
    }
    while(!step_ok(cp.y, cp.x, NOMONST, NULL));

    /* Create a new wandering monster */

    item = new_item(sizeof *tp);
    which = randmonster(TRUE, FALSE);
    new_monster(item, which, &cp, FALSE);

    tp = THINGPTR(item);
    tp->t_pos = cp;     /* Assign the position to the monster */

    chase_it(&tp->t_pos, &player);

    i = rnd(7);

    if (on(*tp, ISSWARM) && i < 5)
        cnt = roll(2, 4);
    else if (on(*tp, ISFLOCK) && i < 5)
        cnt = roll(1, 4);
    else
        cnt = 0;

    for (i = 1; i <= cnt; i++)
    {
        struct linked_list  *ip = creat_mons(tp, which, NOMESSAGE);

        if (ip != NULL)
        {
            struct thing    *mp = THINGPTR(ip);

            if (on(*tp, ISFRIENDLY))
                turn_on(*mp, ISFRIENDLY);
            else
                turn_off(*mp, ISFRIENDLY);
        }
    }

    if (cnt > 0)
    {
        if (on(*tp, LOWCAST) || on(*tp, MEDCAST) || on(*tp, HIGHCAST))
            turn_on(*tp, CANCAST);

        tp->t_stats.s_hpt += roll(2, 8);
        tp->t_stats.s_lvl += roll(2, 3);
        tp->t_stats.s_arm -= roll(1, 6);
        tp->t_stats.s_str += roll(2, 3);
        tp->t_stats.s_intel += roll(2, 3);
        tp->t_stats.s_exp += roll(2, 8) * monsters[which].m_add_exp;
    }

    i = DISTANCE(cp, hero);

    if (i < 20)
        loc = "very close to you";
    else if (i < 400)
        loc = "nearby";
    else
        loc = "in the distance";

    if (wizard)
        msg("Started a wandering %s.", monsters[tp->t_index].m_name);
    else if (on(*tp, ISUNDEAD) && (player.t_ctype == C_CLERIC ||
            player.t_ctype == C_PALADIN || is_wearing(R_PIETY)))
        msg("You sense a new ungodly monster %s.", loc);
    else if (on(player, CANHEAR) || (player.t_ctype == C_THIEF &&
            rnd(20) == 0))
        msg("You hear a new %s moving %s.",
            monsters[tp->t_index].m_name, loc);
    else if (on(player, CANSCENT) || (player.t_ctype == C_THIEF &&
            rnd(20) == 0))
        msg("You smell a new %s %s.", monsters[tp->t_index].m_name,
            loc);
}