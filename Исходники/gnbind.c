/*
outrip(winid, int)
	    -- The tombstone code.  If you want the traditional code use
	       genl_outrip for the value and check the #if in rip.c.
*/
void gnome_outrip(winid wid, int how)
{
    /* Follows roughly the same algorithm as genl_outrip() */
    char buf[BUFSZ];
    char ripString[BUFSZ]="\0";
    extern const char *killed_by_prefix[];

    /* Put name on stone */
    Sprintf(buf, "%s\n", plname);
    Strcat(ripString, buf);

    /* Put $ on stone */
    Sprintf(buf, "%ld Au\n",
#ifndef GOLDOBJ
            u.ugold);
#else
            done_money);
#endif
    Strcat(ripString, buf);

    /* Put together death description */
    switch (killer_format) {
    default:
        impossible("bad killer format?");
    case KILLED_BY_AN:
        Strcpy(buf, killed_by_prefix[how]);
        Strcat(buf, an(killer));
        break;
    case KILLED_BY:
        Strcpy(buf, killed_by_prefix[how]);
        Strcat(buf, killer);
        break;
    case NO_KILLER_PREFIX:
        Strcpy(buf, killer);
        break;
    }
    /* Put death type on stone */
    Strcat(ripString, buf);
    Strcat(ripString, "\n");

    /* Put year on stone */
    Sprintf(buf, "%4d\n", getyear());
    Strcat(ripString, buf);

    ghack_text_window_rip_string( ripString);
}