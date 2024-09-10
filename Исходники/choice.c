INT
CommandChoice (LPTSTR param)
{
    LPTSTR lpOptions;
    TCHAR Options[6];
    LPTSTR lpText    = NULL;
    BOOL   bNoPrompt = FALSE;
    BOOL   bCaseSensitive = FALSE;
    BOOL   bTimeout = FALSE;
    INT    nTimeout = 0;
    TCHAR  cDefault = _T('\0');
    INPUT_RECORD ir;
    LPTSTR p, np;
    LPTSTR *arg;
    INT    argc;
    INT    i;
    INT    val;

    INT GCret;
    TCHAR Ch;
    DWORD amount,clk;

    LoadString(CMD_ModuleHandle, STRING_CHOICE_OPTION, Options, 4);
    lpOptions = Options;

    if (_tcsncmp (param, _T("/?"), 2) == 0)
    {
        ConOutResPaging(TRUE,STRING_CHOICE_HELP);
        return 0;
    }

    /* retrieve text */
    p = param;

    while (TRUE)
    {
        if (*p == _T('\0'))
            break;

        if (*p != _T('/'))
        {
            lpText = p;
            break;
        }
        np = _tcschr (p, _T(' '));
        if (!np)
            break;
        p = np + 1;
    }

    /* build parameter array */
    arg = split (param, &argc, FALSE);

    /* evaluate arguments */
    if (argc > 0)
    {
        for (i = 0; i < argc; i++)
        {
            if (_tcsnicmp (arg[i], _T("/c"), 2) == 0)
            {
                if (arg[i][2] == _T(':'))
                    lpOptions = &arg[i][3];
                else
                    lpOptions = &arg[i][2];

                if (_tcslen (lpOptions) == 0)
                {
                    ConErrResPuts(STRING_CHOICE_ERROR);
                    freep (arg);
                    return 1;
                }
            }
            else if (_tcsnicmp (arg[i], _T("/n"), 2) == 0)
            {
                bNoPrompt = TRUE;
            }
            else if (_tcsnicmp (arg[i], _T("/s"), 2) == 0)
            {
                bCaseSensitive = TRUE;
            }
            else if (_tcsnicmp (arg[i], _T("/t"), 2) == 0)
            {
                LPTSTR s;

                if (arg[i][2] == _T(':'))
                {
                    cDefault = arg[i][3];
                    s = &arg[i][4];
                }
                else
                {
                    cDefault = arg[i][2];
                    s = &arg[i][3];
                }

                if (*s != _T(','))
                {
                    ConErrResPuts(STRING_CHOICE_ERROR_TXT);
                    freep (arg);
                    return 1;
                }

                s++;
                nTimeout = _ttoi(s);
                bTimeout = TRUE;
            }
            else if (arg[i][0] == _T('/'))
            {
                ConErrResPrintf(STRING_CHOICE_ERROR_OPTION, arg[i]);
                freep (arg);
                return 1;
            }
        }
    }

    /* print text */
    if (lpText)
        ConOutPrintf (_T("%s"), lpText);

    /* print options */
    if (bNoPrompt == FALSE)
    {
        ConOutPrintf (_T("[%c"), lpOptions[0]);

        for (i = 1; (unsigned)i < _tcslen (lpOptions); i++)
            ConOutPrintf (_T(",%c"), lpOptions[i]);

        ConOutPrintf (_T("]?"));
    }

    ConInFlush ();

    if(!bTimeout)
    {
        while (TRUE)
        {
            ConInKey (&ir);

            val = IsKeyInString (lpOptions,
#ifdef _UNICODE
                                 ir.Event.KeyEvent.uChar.UnicodeChar,
#else
                                 ir.Event.KeyEvent.uChar.AsciiChar,
#endif
                                 bCaseSensitive);

            if (val >= 0)
            {
                ConOutPrintf (_T("%c\n"), lpOptions[val]);

                nErrorLevel = val + 1;

                break;
            }

            Beep (440, 50);
        }

        freep (arg);
        TRACE ("ErrorLevel: %d\n", nErrorLevel);
        return 0;
    }

    clk = GetTickCount ();
    amount = nTimeout*1000;

loop:
    GCret = GetCharacterTimeout (&Ch, amount - (GetTickCount () - clk));

    switch (GCret)
    {
    case GC_TIMEOUT:
        TRACE ("GC_TIMEOUT\n");
        TRACE ("elapsed %d msecs\n", GetTickCount () - clk);
        break;

    case GC_NOKEY:
        TRACE ("GC_NOKEY\n");
        TRACE ("elapsed %d msecs\n", GetTickCount () - clk);
        goto loop;

    case GC_KEYREAD:
        TRACE ("GC_KEYREAD\n");
        TRACE ("elapsed %d msecs\n", GetTickCount () - clk);
        TRACE ("read %c", Ch);
        if ((val=IsKeyInString(lpOptions,Ch,bCaseSensitive))==-1)
        {
            Beep (440, 50);
            goto loop;
        }
        cDefault=Ch;
        break;
    }

    TRACE ("exiting wait loop after %d msecs\n",
           GetTickCount () - clk);

    val = IsKeyInString (lpOptions, cDefault, bCaseSensitive);
    ConOutPrintf (_T("%c\n"), lpOptions[val]);

    nErrorLevel = val + 1;

    freep (arg);

    TRACE ("ErrorLevel: %d\n", nErrorLevel);

    return 0;
}