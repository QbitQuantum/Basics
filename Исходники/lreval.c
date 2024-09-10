MODULE classify_token_as_action (void)
{
    typedef struct {                    /*  Lookup table structure:          */
        char   *name;                   /*    Action name                    */
        event_t event;                  /*    Corresponding event            */
    } ACTION_LOOKUP;

    /*  Table of actions                                                     */
    /*      arranged alphabetically for cosmetic purposes                    */
    static ACTION_LOOKUP
        lookup [] = {
            { "animate",  animate_event  },
            { "caps",     caps_event     },
            { "check",    check_event    },
            { "cobol",    cobol_event    },
            { "defaults", defaults_event },
            { "event",    event_event    },
            { "exist",    exist_event    },
            { "headline", headline_event },
            { "module",   module_event   },
            { "normal",   normal_event   },
            { "not",      not_event      },
            { "plain",    plain_event    },
            { "state",    state_event    },
            { "test",     test_event     },
            { "title",    title_event    },
            /*  Sentinel marks end of table                                  */
            {  NULL,      other_event    }
        };
    ACTION_LOOKUP
        *lptr;                          /*  Index into lookup table          */

    StrLwr (token);                     /*  Actions names are lower-case     */
    for (lptr = lookup; lptr-> name; lptr++)
        if (streq (lptr-> name, token))
            break;                      /*  Scan till we find match, or end  */

    the_next_event = lptr-> event;      /*    and set appropriate event      */
}