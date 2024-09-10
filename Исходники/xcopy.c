static int XCOPY_ParseCommandLine(WCHAR *suppliedsource,
                                  WCHAR *supplieddestination, DWORD *pflags)
{
    const WCHAR EXCLUDE[]  = {'E', 'X', 'C', 'L', 'U', 'D', 'E', ':', 0};
    DWORD flags = *pflags;
    WCHAR *cmdline, *word, *end, *next;
    int rc = RC_INITERROR;

    cmdline = _wcsdup(GetCommandLineW());
    if (cmdline == NULL)
        return rc;

    /* Skip first arg, which is the program name */
    if ((rc = find_end_of_word(cmdline, &word)) != RC_OK)
        goto out;
    word = skip_whitespace(word);

    while (*word)
    {
        WCHAR first;
        if ((rc = find_end_of_word(word, &end)) != RC_OK)
            goto out;

        next = skip_whitespace(end);
        first = word[0];
        *end = '\0';
        strip_quotes(word, &end);
        WINE_TRACE("Processing Arg: '%s'\n", wine_dbgstr_w(word));

        /* First non-switch parameter is source, second is destination */
        if (first != '/') {
            if (suppliedsource[0] == 0x00) {
                lstrcpyW(suppliedsource, word);
            } else if (supplieddestination[0] == 0x00) {
                lstrcpyW(supplieddestination, word);
            } else {
                XCOPY_wprintf(XCOPY_LoadMessage(STRING_INVPARMS));
                goto out;
            }
        } else {
            /* Process all the switch options
                 Note: Windows docs say /P prompts when dest is created
                       but tests show it is done for each src file
                       regardless of the destination                   */
            switch (toupper(word[1])) {
            case 'I': flags |= OPT_ASSUMEDIR;     break;
            case 'S': flags |= OPT_RECURSIVE;     break;
            case 'Q': flags |= OPT_QUIET;         break;
            case 'F': flags |= OPT_FULL;          break;
            case 'L': flags |= OPT_SIMULATE;      break;
            case 'W': flags |= OPT_PAUSE;         break;
            case 'T': flags |= OPT_NOCOPY | OPT_RECURSIVE; break;
            case 'Y': flags |= OPT_NOPROMPT;      break;
            case 'N': flags |= OPT_SHORTNAME;     break;
            case 'U': flags |= OPT_MUSTEXIST;     break;
            case 'R': flags |= OPT_REPLACEREAD;   break;
            case 'H': flags |= OPT_COPYHIDSYS;    break;
            case 'C': flags |= OPT_IGNOREERRORS;  break;
            case 'P': flags |= OPT_SRCPROMPT;     break;
            case 'A': flags |= OPT_ARCHIVEONLY;   break;
            case 'M': flags |= OPT_ARCHIVEONLY |
                               OPT_REMOVEARCH;    break;

            /* E can be /E or /EXCLUDE */
            case 'E': if (CompareStringW(LOCALE_USER_DEFAULT,
                                         NORM_IGNORECASE | SORT_STRINGSORT,
                                         &word[1], 8,
                                         EXCLUDE, -1) == CSTR_EQUAL) {
                        if (XCOPY_ProcessExcludeList(&word[9])) {
                          XCOPY_FailMessage(ERROR_INVALID_PARAMETER);
                          goto out;
                        } else flags |= OPT_EXCLUDELIST;
                      } else flags |= OPT_EMPTYDIR | OPT_RECURSIVE;
                      break;

            /* D can be /D or /D: */
            case 'D': if (word[2]==':' && isdigit(word[3])) {
                          SYSTEMTIME st;
                          WCHAR     *pos = &word[3];
                          BOOL       isError = FALSE;
                          memset(&st, 0x00, sizeof(st));

                          /* Microsoft xcopy's usage message implies that the date
                           * format depends on the locale, but that is false.
                           * It is hardcoded to month-day-year.
                           */
                          st.wMonth = _wtol(pos);
                          while (*pos && isdigit(*pos)) pos++;
                          if (*pos++ != '-') isError = TRUE;

                          if (!isError) {
                              st.wDay = _wtol(pos);
                              while (*pos && isdigit(*pos)) pos++;
                              if (*pos++ != '-') isError = TRUE;
                          }

                          if (!isError) {
                              st.wYear = _wtol(pos);
                              while (*pos && isdigit(*pos)) pos++;
                              if (st.wYear < 100) st.wYear+=2000;
                          }

                          if (!isError && SystemTimeToFileTime(&st, &dateRange)) {
                              SYSTEMTIME st;
                              WCHAR datestring[32], timestring[32];

                              flags |= OPT_DATERANGE;

                              /* Debug info: */
                              FileTimeToSystemTime (&dateRange, &st);
                              GetDateFormatW(0, DATE_SHORTDATE, &st, NULL, datestring,
                                             sizeof(datestring)/sizeof(WCHAR));
                              GetTimeFormatW(0, TIME_NOSECONDS, &st,
                                             NULL, timestring, sizeof(timestring)/sizeof(WCHAR));

                              WINE_TRACE("Date being used is: %s %s\n",
                                         wine_dbgstr_w(datestring), wine_dbgstr_w(timestring));
                          } else {
                              XCOPY_FailMessage(ERROR_INVALID_PARAMETER);
                              goto out;
                          }
                      } else {
                          flags |= OPT_DATENEWER;
                      }
                      break;

            case '-': if (toupper(word[2])=='Y')
                          flags &= ~OPT_NOPROMPT;
                      break;
            case '?': XCOPY_wprintf(XCOPY_LoadMessage(STRING_HELP));
                      rc = RC_HELP;
                      goto out;
            default:
                WINE_TRACE("Unhandled parameter '%s'\n", wine_dbgstr_w(word));
                XCOPY_wprintf(XCOPY_LoadMessage(STRING_INVPARM), word);
                goto out;
            }
        }
        word = next;
    }

    /* Default the destination if not supplied */
    if (supplieddestination[0] == 0x00)
        lstrcpyW(supplieddestination, wchr_dot);

    *pflags = flags;
    rc = RC_OK;

 out:
    free(cmdline);
    return rc;
}