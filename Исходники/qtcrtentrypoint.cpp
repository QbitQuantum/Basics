int QtWinMainCRTStartup()
{
#ifdef __MSVCRT__
    __set_app_type (__GUI_APP);
#endif

    SetUnhandledExceptionFilter (_gnu_exception_handler);

    /*
    * Initialize floating point unit.
    */
    _fpreset ();			/* Supplied by the runtime library. */

    /*
    * Sets the default file mode.
    * If _CRT_fmode is set, also set mode for stdin, stdout
    * and stderr, as well
    * NOTE: DLLs don't do this because that would be rude!
    */
    _mingw32_init_fmode ();

    /* Adust references to dllimported data that have non-zero offsets.  */
    _pei386_runtime_relocator ();

    char *szCmd;
    STARTUPINFO startinfo;
    int nRet;

    /* Get the command line passed to the process. */
    szCmd = GetCommandLineA ();
    GetStartupInfo (&startinfo);

    /* Strip off the name of the application and any leading
    * whitespace. */
    if (szCmd) {

        while (ISSPACE (*szCmd)) {
            szCmd++;
        }

        /* On my system I always get the app name enclosed
        * in quotes... */
        if (*szCmd == '\"') {
            do {
                szCmd++;
            } while (*szCmd != '\"' && *szCmd != '\0');

            if (*szCmd == '\"') {
                szCmd++;
            }
        } else {
        /* If no quotes then assume first token is program
        * name. */
            while (!ISSPACE (*szCmd) && *szCmd != '\0') {
                szCmd++;
            }
        }

        while (ISSPACE (*szCmd)) {
            szCmd++;
        }
    }

    nRet = WinMain (GetModuleHandle (NULL), NULL, szCmd,
                    (startinfo.dwFlags & STARTF_USESHOWWINDOW) ?
                     startinfo.wShowWindow : SW_SHOWDEFAULT);

    /*
    * Perform exit processing for the C library. This means
    * flushing output and calling 'atexit' registered functions.
    */
    _cexit ();

    ExitProcess (nRet);

    return 0;

}