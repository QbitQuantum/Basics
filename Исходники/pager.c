/*
 * Look in the "data" file for more info.  Called if the user typed in the
 * whole name (user_typed_name == TRUE), or we've found a possible match
 * with a character/glyph.
 */
static void
checkfile(const char *inp, struct permonst *pm, boolean user_typed_name,
          boolean without_asking)
{
    dlb *fp;
    char buf[BUFSZ], newstr[BUFSZ];
    char *ep, *dbase_str;
    long txt_offset = 0;
    int chk_skip;
    boolean found_in_file = FALSE, skipping_entry = FALSE;

    fp = dlb_fopen(DATAFILE, "r");
    if (!fp) {
        pline("Cannot open data file!");
        return;
    }

    /* To prevent the need for entries in data.base like *ngel to account for
       Angel and angel, make the lookup string the same for both
       user_typed_name and picked name. */
    if (pm != NULL && !user_typed_name)
        dbase_str = strcpy(newstr, pm->mname);
    else
        dbase_str = strcpy(newstr, inp);

    for (ep = dbase_str; *ep; ep++)
        *ep = lowc(*ep);

    if (!strncmp(dbase_str, "interior of ", 12))
        dbase_str += 12;
    if (!strncmp(dbase_str, "a ", 2))
        dbase_str += 2;
    else if (!strncmp(dbase_str, "an ", 3))
        dbase_str += 3;
    else if (!strncmp(dbase_str, "the ", 4))
        dbase_str += 4;
    if (!strncmp(dbase_str, "tame ", 5))
        dbase_str += 5;
    else if (!strncmp(dbase_str, "peaceful ", 9))
        dbase_str += 9;
    if (!strncmp(dbase_str, "invisible ", 10))
        dbase_str += 10;
    if (!strncmp(dbase_str, "statue of ", 10))
        dbase_str[6] = '\0';
    else if (!strncmp(dbase_str, "figurine of ", 12))
        dbase_str[8] = '\0';

    /* Make sure the name is non-empty. */
    if (*dbase_str) {
        /* adjust the input to remove " [seen" and "named " and convert to
           lower case */
        const char *alt = 0;  /* alternate description */

        if ((ep = strstri_mutable(dbase_str, " [seen")) != 0)
            *ep = '\0';

        if ((ep = strstri_mutable(dbase_str, " named ")) != 0)
            alt = ep + 7;
        else
            ep = strstri_mutable(dbase_str, " called ");
        if (!ep)
            ep = strstri_mutable(dbase_str, ", ");
        if (ep && ep > dbase_str)
            *ep = '\0';

        /* 
         * If the object is named, then the name is the alternate description;
         * otherwise, the result of makesingular() applied to the name is. This
         * isn't strictly optimal, but named objects of interest to the user
         * will usually be found under their name, rather than under their
         * object type, so looking for a singular form is pointless.
         */

        if (!alt)
            alt = makesingular(dbase_str);
        else if (user_typed_name)
            alt = msglowercase(alt);

        /* skip first record; read second */
        txt_offset = 0L;
        if (!dlb_fgets(buf, BUFSZ, fp) || !dlb_fgets(buf, BUFSZ, fp)) {
            impossible("can't read 'data' file");
            dlb_fclose(fp);
            return;
        } else if (sscanf(buf, "%8lx\n", &txt_offset) < 1 || txt_offset <= 0)
            goto bad_data_file;

        /* look for the appropriate entry */
        while (dlb_fgets(buf, BUFSZ, fp)) {
            if (*buf == '.')
                break;  /* we passed last entry without success */

            if (digit(*buf)) {
                /* a number indicates the end of current entry */
                skipping_entry = FALSE;
            } else if (!skipping_entry) {
                if (!(ep = strchr(buf, '\n')))
                    goto bad_data_file;
                *ep = 0;
                /* if we match a key that begins with "~", skip this entry */
                chk_skip = (*buf == '~') ? 1 : 0;
                if (pmatch(&buf[chk_skip], dbase_str) ||
                    (alt && pmatch(&buf[chk_skip], alt))) {
                    if (chk_skip) {
                        skipping_entry = TRUE;
                        continue;
                    } else {
                        found_in_file = TRUE;
                        break;
                    }
                }
            }
        }
    }

    if (found_in_file) {
        long entry_offset;
        int entry_count;
        int i;

        /* skip over other possible matches for the info */
        do {
            if (!dlb_fgets(buf, BUFSZ, fp))
                goto bad_data_file;
        } while (!digit(*buf));

        if (sscanf(buf, "%ld,%d\n", &entry_offset, &entry_count) < 2) {
        bad_data_file:impossible("'data' file in wrong format");
            dlb_fclose(fp);
            return;
        }

        if (user_typed_name || without_asking || yn("More info?") == 'y') {
            struct nh_menulist menu;

            if (dlb_fseek(fp, txt_offset + entry_offset, SEEK_SET) < 0) {
                pline("? Seek error on 'data' file!");
                dlb_fclose(fp);
                return;
            }

            init_menulist(&menu);

            for (i = 0; i < entry_count; i++) {
                if (!dlb_fgets(buf, BUFSZ, fp))
                    goto bad_data_file;
                if ((ep = strchr(buf, '\n')) != 0)
                    *ep = 0;
                if (strchr(buf + 1, '\t') != 0)
                    tabexpand(buf + 1);
                add_menutext(&menu, buf + 1);
            }

            display_menu(&menu, NULL, FALSE, PLHINT_ANYWHERE,
                         NULL);
        }
    } else if (user_typed_name)
        pline("I don't have any information on those things.");

    dlb_fclose(fp);
}