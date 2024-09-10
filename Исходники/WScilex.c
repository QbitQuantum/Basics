/*--------------------------------------------------------------------------*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    int iExitCode = 0;
    HINSTANCE hinstLib = NULL;
    BOOL fFreeResult = FALSE, fRunTimeLinkSuccess = FALSE;

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

    hinstLib = LoadLibrary(TEXT(SCILAB_LIBRARY));
    if (hinstLib != NULL)
    {
        MYPROC1 Windows_Main = NULL;

        /* launch main */
        Windows_Main = (MYPROC1) GetProcAddress(hinstLib, MAIN_FUNCTION);
        if (NULL != Windows_Main)
        {

#ifndef _DEBUG
            /* catch system errors msgbox (release mode only) */
            /* http://msdn.microsoft.com/en-us/library/ms680621(VS.85).aspx */
            UINT LastErrorMode = SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX );
            _try
            {
#endif
                fRunTimeLinkSuccess = TRUE;
                /* launch main */
                iExitCode = (Windows_Main)(hInstance, hPrevInstance, szCmdLine, iCmdShow);

#ifndef _DEBUG
            }
            _except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
#endif
        }