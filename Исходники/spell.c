int
study_book(struct obj *spellbook, const struct nh_cmd_arg *arg)
{
    int booktype = spellbook->otyp;
    boolean confused = (Confusion != 0);
    boolean too_hard = FALSE;

    if (u.uoccupation_progress[tos_book] && !confused &&
        spellbook == u.utracked[tos_book] &&
        /* handle the sequence: start reading, get interrupted, have book
           become erased somehow, resume reading it */
        booktype != SPE_BLANK_PAPER) {
        if (turnstate.continue_message)
            pline("You continue your efforts to memorize the spell.");
    } else {
        /* Restarting reading the book */

        /* KMH -- Simplified this code */
        if (booktype == SPE_BLANK_PAPER) {
            pline("This spellbook is all blank.");
            makeknown(booktype);
            return 1;
        }
        switch (objects[booktype].oc_level) {
        case 1:
        case 2:
            u.uoccupation_progress[tos_book] = -objects[booktype].oc_delay;
            break;
        case 3:
        case 4:
            u.uoccupation_progress[tos_book] =
                -(objects[booktype].oc_level - 1) * objects[booktype].oc_delay;
            break;
        case 5:
        case 6:
            u.uoccupation_progress[tos_book] =
                -objects[booktype].oc_level * objects[booktype].oc_delay;
            break;
        case 7:
            u.uoccupation_progress[tos_book] = -8 * objects[booktype].oc_delay;
            break;
        default:
            impossible("Unknown spellbook level %d, book %d;",
                       objects[booktype].oc_level, booktype);
            return 0;
        }

        /* Books are often wiser than their readers (Rus.) */
        spellbook->in_use = TRUE;
        if (!spellbook->blessed && spellbook->otyp != SPE_BOOK_OF_THE_DEAD) {
            if (spellbook->cursed) {
                too_hard = TRUE;
            } else {
                /* uncursed - chance to fail */
                int read_ability =
                    ACURR(A_INT) + 4 + u.ulevel / 2 -
                    2 * objects[booktype].oc_level +
                    ((ublindf && ublindf->otyp == LENSES) ? 2 : 0);
                /* only wizards know if a spell is too difficult */
                if (Role_if(PM_WIZARD) && read_ability < 20 && !confused) {
                    const char *qbuf;

                    qbuf = msgprintf("This spellbook is %sdifficult to "
                                     "comprehend. Continue?",
                                     (read_ability < 12 ? "very " : ""));
                    if (yn(qbuf) != 'y') {
                        spellbook->in_use = FALSE;
                        return 1;
                    }
                }
                /* it's up to random luck now */
                if (rnd(20) > read_ability) {
                    too_hard = TRUE;
                }
            }
        }

        if (too_hard) {
            boolean gone = cursed_book(spellbook);

            helpless(-u.uoccupation_progress[tos_book], hr_paralyzed,
                     "frozen by a spellbook", NULL);
            u.uoccupation_progress[tos_book] = 0;
            if (gone || !rn2(3)) {
                if (!gone)
                    pline("The spellbook crumbles to dust!");
                if (!objects[spellbook->otyp].oc_name_known &&
                    !objects[spellbook->otyp].oc_uname)
                    docall(spellbook);
                useup(spellbook);
            } else
                spellbook->in_use = FALSE;
            return 1;
        } else if (confused) {
            if (!confused_book(spellbook)) {
                spellbook->in_use = FALSE;
            }
            helpless(-u.uoccupation_progress[tos_book], hr_busy,
                     "absorbed in a spellbook",
                     "You're finally able to put the book down.");
            u.uoccupation_progress[tos_book] = 0;
            u.utracked[tos_book] = 0;
            return 1;
        }
        spellbook->in_use = FALSE;

        pline("You begin to %s the runes.",
              spellbook->otyp == SPE_BOOK_OF_THE_DEAD ? "recite" : "memorize");
    }

    u.utracked[tos_book] = spellbook;

    one_occupation_turn(learn, "studying", occ_book);

    return 1;
}