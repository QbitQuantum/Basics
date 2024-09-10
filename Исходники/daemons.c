daemon
runners(daemon_arg *arg)
{
    struct linked_list  *item;
    struct thing        *tp;

    NOOP(arg);

    for (item = mlist; item != NULL; item = next_mons)
    {
        curr_mons = item;
        next_mons = next(curr_mons);
        tp        = THINGPTR(item);

        if (on(*tp, ISHELD) && rnd(tp->t_stats.s_str +
            tp->t_stats.s_lvl) > 10 + rnd(50))
        {
            turn_off(*tp, ISHELD);
            turn_off(*tp, ISDISGUISE);
            turn_on(*tp, ISRUN);
            tp->t_ischasing = TRUE;
            tp->t_chasee = &player;
            tp->t_horde  = NULL;

            if (tp->t_stats.s_hpt < rnd(tp->maxstats.s_hpt))
                turn_on(*tp, ISFLEE);

            if (cansee(tp->t_pos.y, tp->t_pos.x))
                msg("The %s breaks free!", monsters[tp->t_index].m_name);
        }

        if (off(*tp, ISHELD) && on(*tp, ISRUN))
        {
            int flee = FALSE;

            flee = on(*tp, ISFLEE) ||
                     ( (tp->t_chasee == &player) &&
                         on(player, ISINWALL) &&
                         off(*tp, CANINWALL) && off(*tp, ISFAMILIAR) );

            if (off(*tp, ISSLOW) || tp->t_turn)
            {
                daemon_arg targ;

                targ.thingptr = tp;
                doctor(&targ);
                do_chase(tp, flee);
            }

            if (curr_mons && (on(*tp, ISHASTE) ||
               ((on(*tp, CANFLY) || on(*tp, ISFAST)) &&
               DISTANCE(hero, tp->t_pos) >= 4)))
            {
                daemon_arg targ;

                targ.thingptr = tp;
                doctor(&targ);
                do_chase(tp, flee);
            }

            if (curr_mons)
            {
                tp->t_turn ^= TRUE;
                tp->t_wasshot ^= FALSE; /* Not shot anymore */
            }

        }
    }

    curr_mons = next_mons = NULL;

    return;
}