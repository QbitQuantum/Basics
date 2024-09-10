void TERMWINDOWMEMBER StartPrinting(const char *FileName)
    {
    if (OC.Printing)
        {
        fclose(OC.PrintFile);
        }

#ifdef WINCIT
	sprintf(OC.PrintfileName, "%s.%ld", FileName, GetCurrentThreadId());
#else
	CopyStringToBuffer(OC.PrintfileName, FileName);
#endif

    normalizeString(OC.PrintfileName);

    if (citOpen(OC.PrintfileName, CO_A, &OC.PrintFile))
        {
        if (cfg.VerboseConsole)
            {
            CitWindowsNote(NULL, getmsg(MSG_CONSOLE, 37));
            }

        OC.Printing = TRUE;
        }
    else
        {
        if (cfg.VerboseConsole)
            {
            CitWindowsNote(NULL, getmsg(MSG_CONSOLE, 38));
            }

        OC.Printing = FALSE;
        }
    }