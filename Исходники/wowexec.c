int PASCAL WinMain(HANDLE hInstance,
                   HANDLE hPrevInstance, LPSTR lpszCmdLine, int iCmd)

{
    int i;
    MSG msg;
    LPSTR pch,pch1;
    WORD    ret;
    WOWINFO wowinfo;
    char aszWOWDEB[CCHMAX];
    LPSTR pchWOWDEB;
    HANDLE hMMDriver;


    char        szBuffer[150];
    BOOL        bFinished;
    int         iStart;
    int         iEnd;


    hAppInstance = hInstance ;

    // Only Want One WOWExec
    if (hPrevInstance != NULL) {
        return(FALSE);
    }

    if (!InitializeApp(lpszCmdLine)) {
        OutputDebugString("WOWEXEC: InitializeApp failure!\n");
        return 0;
    }

/*
 * Look for a drivers= line in the [boot] section of SYSTEM.INI
 * If present it is the 16 bit MultiMedia interface, so load it
 */

#ifdef OLD_MMSYSTEM_LOAD
    if (GetPrivateProfileString((LPSTR)"boot", (LPSTR)"drivers",(LPSTR)"", aszMMDriver, sizeof(aszMMDriver), (LPSTR)"SYSTEM.INI")) {
/*
 * We have now discovered an app that rewrites the "drivers" entry with
 * multiple drivers - so the existing load method fails. As a temporary fix
 * while we decide what the "proper" fix is I will always load MMSYSTEM and
 * ONLY MMSYSTEM.
 *
 *       aszMMDriver[sizeof(aszMMDriver)-1] = '\0';
 *       hMMDriver = LoadLibrary((LPSTR)aszMMDriver);
 * #ifdef DEBUG
 *       if (hMMDriver < 32) {
 *           OutputDebugString("WOWEXEC: Load of MultiMedia driver failed\n");
 *       }
 * #endif
 */
        LoadLibrary("MMSYSTEM.DLL");
    }
#else
    /* Load DDL's from DRIVERS section in system.ini
     */
    GetPrivateProfileString( (LPSTR)"boot",      /* [Boot] section */
                            (LPSTR)"drivers",   /* Drivers= */
                            (LPSTR)"",          /* Default if no match */
                            szBuffer,    /* Return buffer */
                            sizeof(szBuffer),
                            (LPSTR)"system.ini" );

    if (!*szBuffer) {
        goto Done;
    }

    bFinished = FALSE;
    iStart    = 0;

    while (!bFinished) {
        iEnd = iStart;

        while (szBuffer[iEnd] && (szBuffer[iEnd] != ' ') &&
               (szBuffer[iEnd] != ',')) {
            iEnd++;
        }

        if (szBuffer[iEnd] == NULL) {
            bFinished = TRUE;
        }
        else {
            szBuffer[iEnd] = NULL;
        }

        /* Load and enable the driver.
         */
        OpenDriver( &(szBuffer[iStart]), NULL, NULL );
        iStart = iEnd + 1;
    }

Done:

#endif

/*
 * Look for a debug= line in the [boot] section of SYSTEM.INI
 * If present it is the 16 bit MultiMedia interface, so load it
 */

    if ( WOWQueryDebug() & 0x0001 ) {
        pchWOWDEB = "WOWDEB.EXE";
    } else {
        pchWOWDEB = "";
    }

    GetPrivateProfileString((LPSTR)"boot", (LPSTR)"debug",pchWOWDEB, aszWOWDEB, sizeof(aszWOWDEB), (LPSTR)"SYSTEM.INI");
    aszWOWDEB[sizeof(aszWOWDEB)-1] = '\0';

    if ( lstrlen(pchWOWDEB) != 0 ) {
        WinExec((LPSTR)aszWOWDEB,SW_SHOW);
    }

#if 0
/*  Preload winspool.exe.   Apps will keep loading and freeing it
 *  which is slow.   We might as well load it now so the reference
 *  count is 1 so it will never be loaded or freed
 */
    //
    // Disabled load of winspool.exe to save 8k.  Size vs. speed,
    // which one do we care about?  Right now, size!
    //
    LoadLibrary("WINSPOOL.EXE");
#endif

    // Always load SHELL.DLL, FileMaker Pro and Lotus Install require it.

    LoadLibrary("SHELL.DLL");

    //
    // Start any apps pending in basesrv queue
    //

    while (StartRequestedApp() && gfSharedWOW) {
        /* null stmt */ ;
    }


    while (1)  {
        if (!WowWaitForMsgAndEvent(ghwndMain) &&
            PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) &&
            msg.message != WM_WOWEXECHEARTBEAT )
           {
            if (msg.message != WM_QUIT) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return 1;
}