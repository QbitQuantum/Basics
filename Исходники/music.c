/* So you want music... */
int
do_play_instrument(struct obj *instr, const struct nh_cmd_arg *arg)
{
    char c = 'y';
    const char *buf;
    int x, y;
    boolean ok;

    if (Underwater) {
        pline(msgc_cancelled, "You can't play music underwater!");
        return 0;
    }
    if (Upolyd && !can_blow_instrument(youmonst.data) &&
        (instr->otyp == BUGLE || instr->otyp == WOODEN_FLUTE ||
         instr->otyp == MAGIC_FLUTE || instr->otyp == TOOLED_HORN ||
         instr->otyp == FIRE_HORN || instr->otyp == FROST_HORN)) {
        pline(msgc_cancelled,
              "You are incapable of playing %s in your current form!",
              the(xname(instr)));
        return 0;
    }
    if (instr->otyp != LEATHER_DRUM && instr->otyp != DRUM_OF_EARTHQUAKE) {
        c = yn("Improvise?");
    }
    if (c == 'n') {
        if (u.uevent.uheard_tune == 2 && yn("Play the passtune?") == 'y') {
            buf = msg_from_string(gamestate.castle_tune);
        } else {
            /* Note: This is explicitly not getarglin(); we don't want
               command repeat to repeat the tune. */
            buf = getlin("What tune are you playing? [5 notes, A-G]", FALSE);
            if (*buf == '\033')
                buf = "";
            buf = msgmungspaces(buf);
            /* convert to uppercase and change any "H" to the expected "B" */
            buf = msgcaseconv(buf, highc_htob, highc_htob, highc_htob);
        }
        pline(msgc_occstart, "You extract a strange sound from %s!",
              the(xname(instr)));

        /* Check if there was the Stronghold drawbridge near and if the tune
           conforms to what we're waiting for. */
        if (Is_stronghold(&u.uz)) {
            exercise(A_WIS, TRUE);      /* just for trying */
            if (!strcmp(buf, gamestate.castle_tune)) {
                /* Search for the drawbridge */
                for (y = youmonst.my - 1; y <= youmonst.my + 1; y++)
                    for (x = youmonst.mx - 1; x <= youmonst.mx + 1; x++)
                        if (isok(x, y))
                            if (find_drawbridge(&x, &y)) {
                                /* tune now fully known */
                                u.uevent.uheard_tune = 2;
                                if (level->locations[x][y].typ ==
                                    DRAWBRIDGE_DOWN)
                                    close_drawbridge(x, y);
                                else
                                    open_drawbridge(x, y);
                                return 1;
                            }
            } else if (canhear()) {
                if (u.uevent.uheard_tune < 1)
                    u.uevent.uheard_tune = 1;
                /* Okay, it wasn't the right tune, but perhaps we can give the
                   player some hints like in the Mastermind game */
                ok = FALSE;
                for (y = youmonst.my - 1; y <= youmonst.my + 1 && !ok; y++)
                    for (x = youmonst.mx - 1; x <= youmonst.mx + 1 && !ok; x++)
                        if (isok(x, y))
                            if (IS_DRAWBRIDGE(level->locations[x][y].typ) ||
                                is_drawbridge_wall(x, y) >= 0)
                                ok = TRUE;
                if (ok) {       /* There is a drawbridge near */
                    int tumblers, gears;
                    boolean matched[5];

                    tumblers = gears = 0;
                    for (x = 0; x < 5; x++)
                        matched[x] = FALSE;

                    for (x = 0; x < (int)strlen(buf); x++)
                        if (x < 5) {
                            if (buf[x] == gamestate.castle_tune[x]) {
                                gears++;
                                matched[x] = TRUE;
                            } else
                                for (y = 0; y < 5; y++)
                                    if (!matched[y] &&
                                        buf[x] == gamestate.castle_tune[y] &&
                                        buf[y] != gamestate.castle_tune[y]) {
                                        tumblers++;
                                        matched[y] = TRUE;
                                        break;
                                    }
                        }
                    if (tumblers)
                        if (gears)
                            You_hear(msgc_hint,
                                     "%d tumbler%s click and %d gear%s turn.",
                                     tumblers, plur(tumblers), gears,
                                     plur(gears));
                        else
                            You_hear(msgc_hint, "%d tumbler%s click.", tumblers,
                                     plur(tumblers));
                    else if (gears) {
                        You_hear(msgc_hint, "%d gear%s turn.", gears,
                                 plur(gears));
                        /* could only get `gears == 5' by playing five correct
                           notes followed by excess; otherwise, tune would have 
                           matched above */
                        if (gears == 5)
                            u.uevent.uheard_tune = 2;
                    }
                }
            }
        }
        return 1;
    } else
        return do_improvisation(instr, arg);
}