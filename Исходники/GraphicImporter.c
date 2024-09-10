/*
	WinMain
*/
int CALLBACK WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG    msg;
    HANDLE hAccel;

	// Store our module handle
    ghModule = GetModuleHandle(NULL);

	// Initialize QuickTime Media Layer
	InitializeQTML(0);

	// Initialize QuickTime
	EnterMovies();

	// Initialize the app
    if (!InitializeApp()) 
    {
        MessageBox(ghwndMain, "MDI: InitializeApp failure!", "Error", MB_OK);
        return 0;
    }

	// Load our accelerator keys
    if (!(hAccel = LoadAccelerators (ghModule, MAKEINTRESOURCE(ACCEL_ID))))
        MessageBox(ghwndMain, "MDI: Load Accel failure!", "Error", MB_OK);

	// Parse the command line for drag and drop
	ParseCmdLinePriv(NULL);

	// Loop for messages
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!TranslateAccelerator( ghwndMain, hAccel, &msg) &&
            !TranslateMDISysAccel(  ghwndClient, &msg)          ) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	// Deinitialize QuickTime
	ExitMovies();

	// Deinitialize QTML
	TerminateQTML();

    return TRUE;
}