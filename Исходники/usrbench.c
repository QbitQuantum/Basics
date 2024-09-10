int PASCAL WinMain(
    HINSTANCE hinst,
    HINSTANCE hinstPrev,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MSG msg;
    int RemoveCursor = TRUE;

    ghinst = hinst;


    // if command line option exist

    if (lpCmdLine[0]) {
	LPSTR cmdArg;
	if ( cmdArg = strstr ( lpCmdLine, "-a"))     //automation switch
	    AutoRun = TRUE;
	if ( cmdArg = strstr ( lpCmdLine, "-m"))     //cursor stays
	    RemoveCursor = FALSE;
    }

    /*
     * If this is the first instance of the app. register window classes
     */

    if (hinstPrev == NULL)
        if (!InitializeApplication())
            return 0;

    /*
     * Create the frame and do other initialization
     */

    if (!InitializeInstance(nCmdShow))
        return 0;


    if (RemoveCursor)
	ShowCursor(0);

    /*
     * Enter main message loop
     */

    while (GetMessage(&msg, NULL, 0, 0)) {

	if (AutoRun) {
	    AutoTest();
	    break;
	}

        /*
         * If a keyboard message is for the MDI, let the MDI client
         * take care of it.  Otherwise, check to see if it's a normal
         * accelerator key (like F3 = find next).  Otherwise, just handle
         * the message as usual.
         */
        if (!TranslateMDISysAccel(ghwndMDIClient, &msg) &&
                !TranslateAccelerator(ghwndFrame, ghaccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    if (AutoRun)
	PostQuitMessage(0);


    return 0;
}