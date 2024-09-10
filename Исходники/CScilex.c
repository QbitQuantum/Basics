/*--------------------------------------------------------------------------*/
int main (int argc, char **argv)
{
    #define MAXCMDTOKENS 128
    int iExitCode = 0;
    UINT LastErrorMode = 0;
    HINSTANCE hinstLib = NULL; 

    BOOL fFreeResult = FALSE, fRunTimeLinkSuccess = FALSE; 

    int argcbis = -1;
    LPSTR argvbis[MAXCMDTOKENS];
    int i = 0;
    int FindNW = 0;

    if (GetWindowsVersion() == OS_ERROR	)
    {
        MessageBox(NULL, TEXT(MSG_DETECT_UNKNOW), TEXT(MSG_WARNING), MB_ICONWARNING);
        return -1;
    }

    if (GetWindowsVersion() < OS_WIN32_WINDOWS_XP	)
    {
        MessageBox(NULL, TEXT(MSG_DETECT_XP_OR_MORE), TEXT(MSG_WARNING), MB_ICONWARNING);
        return -1;
    }

    /* http://msdn.microsoft.com/en-us/library/ms724482(VS.85).aspx */
    if (!IsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE))
    {
        MessageBox(NULL, TEXT(MSG_DETECT_SSE_OR_MORE), TEXT(MSG_WARNING), MB_ICONWARNING);
        return -1;
    }

    for (i = 0; i < argc; i++)
    {
        if (_stricmp(argv[i], ARG_NW) == 0) FindNW = 1;
        if (_stricmp(argv[i], ARG_NWNI) == 0 ) FindNW = 1;
        if (_stricmp(argv[i], ARG_NOGUI) == 0 ) FindNW = 1;
    }

    if ( FindNW == 0 )
    {
        /* -nw added as first argument and not last */
        char *nwparam = NULL;
        nwparam = (char*)MALLOC((strlen(ARG_NW) + 1) * sizeof(char));
        strcpy_s(nwparam,(strlen(ARG_NW) + 1), ARG_NW);

        argvbis[0] = argv[0];
        argvbis[1] = nwparam;

        for (i = 1; i<argc; i++)
        {
            argvbis[i+1] = argv[i];
        }
        argcbis = argc+1;
    }
    else
    {
        for (i = 0; i < argc; i++)
        {
            argvbis[i] = argv[i];
        }
        argcbis = argc;
    }

    /* Disable system errors msgbox */
    LastErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);

    hinstLib = LoadLibrary(TEXT(SCILAB_LIBRARY));

    /* re enable system errors msgbox */
    SetErrorMode(LastErrorMode);

    if (hinstLib != NULL)
    {
        MYPROC1 Console_Main = NULL;

        /* launch main */
        Console_Main = (MYPROC1) GetProcAddress(hinstLib, MAIN_FUNCTION);

        if (NULL != Console_Main)
        {
            fRunTimeLinkSuccess = TRUE;

#ifndef _DEBUG
            /* catch system errors msgbox (release mode only) */
            /* http://msdn.microsoft.com/en-us/library/ms680621(VS.85).aspx */
            LastErrorMode = SetErrorMode( SEM_FAILCRITICALERRORS|SEM_NOALIGNMENTFAULTEXCEPT|SEM_NOGPFAULTERRORBOX );
            _try
            {
#endif
                iExitCode = (Console_Main)(argcbis, argvbis);

#ifndef _DEBUG
            }
            _except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
#endif
        }