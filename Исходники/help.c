/*
 * helpSQL -- help with SQL commands
 *
 * Note: we assume caller removed any trailing spaces in "topic".
 */
void
helpSQL(const char *topic, unsigned short int pager)
{
#define VALUE_OR_NULL(a) ((a) ? (a) : "")

    if (!topic || strlen(topic) == 0)
    {
        /* Print all the available command names */
        int			screen_width;
        int			ncolumns;
        int			nrows;
        FILE	   *output;
        int			i;
        int			j;

#ifdef TIOCGWINSZ
        struct winsize screen_size;

        if (ioctl(fileno(stdout), TIOCGWINSZ, &screen_size) == -1)
            screen_width = 80;	/* ioctl failed, assume 80 */
        else
            screen_width = screen_size.ws_col;
#else
        screen_width = 80;		/* default assumption */
#endif

        ncolumns = (screen_width - 3) / (QL_MAX_CMD_LEN + 1);
        ncolumns = Max(ncolumns, 1);
        nrows = (QL_HELP_COUNT + (ncolumns - 1)) / ncolumns;

        output = PageOutput(nrows + 1, pager);

        fputs(_("Available help:\n"), output);

        for (i = 0; i < nrows; i++)
        {
            fprintf(output, "  ");
            for (j = 0; j < ncolumns - 1; j++)
                fprintf(output, "%-*s",
                        QL_MAX_CMD_LEN + 1,
                        VALUE_OR_NULL(QL_HELP[i + j * nrows].cmd));
            if (i + j * nrows < QL_HELP_COUNT)
                fprintf(output, "%s",
                        VALUE_OR_NULL(QL_HELP[i + j * nrows].cmd));
            fputc('\n', output);
        }

        ClosePager(output);
    }
    else
    {
        int			i,
                    j,
                    x = 0;
        bool		help_found = false;
        FILE	   *output = NULL;
        size_t		len,
                    wordlen;
        int			nl_count = 0;

        /*
         * We first try exact match, then first + second words, then first
         * word only.
         */
        len = strlen(topic);

        for (x = 1; x <= 3; x++)
        {
            if (x > 1)			/* Nothing on first pass - try the opening
								 * word(s) */
            {
                wordlen = j = 1;
                while (topic[j] != ' ' && j++ < len)
                    wordlen++;
                if (x == 2)
                {
                    j++;
                    while (topic[j] != ' ' && j++ <= len)
                        wordlen++;
                }
                if (wordlen >= len)		/* Don't try again if the same word */
                {
                    if (!output)
                        output = PageOutput(nl_count, pager);
                    break;
                }
                len = wordlen;
            }

            /* Count newlines for pager */
            for (i = 0; QL_HELP[i].cmd; i++)
            {
                if (pg_strncasecmp(topic, QL_HELP[i].cmd, len) == 0 ||
                        strcmp(topic, "*") == 0)
                {
                    nl_count += 5 + QL_HELP[i].nl_count;

                    /* If we have an exact match, exit.  Fixes \h SELECT */
                    if (pg_strcasecmp(topic, QL_HELP[i].cmd) == 0)
                        break;
                }
            }

            if (!output)
                output = PageOutput(nl_count, pager);

            for (i = 0; QL_HELP[i].cmd; i++)
            {
                if (pg_strncasecmp(topic, QL_HELP[i].cmd, len) == 0 ||
                        strcmp(topic, "*") == 0)
                {
                    PQExpBufferData buffer;

                    initPQExpBuffer(&buffer);
                    QL_HELP[i].syntaxfunc(&buffer);
                    help_found = true;
                    fprintf(output, _("Command:     %s\n"
                                      "Description: %s\n"
                                      "Syntax:\n%s\n\n"),
                            QL_HELP[i].cmd,
                            _(QL_HELP[i].help),
                            buffer.data);
                    /* If we have an exact match, exit.  Fixes \h SELECT */
                    if (pg_strcasecmp(topic, QL_HELP[i].cmd) == 0)
                        break;
                }
            }
            if (help_found)		/* Don't keep trying if we got a match */
                break;
        }

        if (!help_found)
            fprintf(output, _("No help available for \"%s\".\nTry \\h with no arguments to see available help.\n"), topic);

        ClosePager(output);
    }
}