/*------------------------------------------------------------------------
Procedure:     WinMain ID:1
Purpose:       Entry point for windows programs.
Input:
Output:
Errors:
------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG msg;
	HANDLE hAccelTable;
	char consoleTitle[512];
	HWND hwndConsole;

	CurrentEditBuffer = (EditBuffer*)SafeMalloc(sizeof(EditBuffer));
	CurrentEditBuffer->LineCount = 0;
	CurrentEditBuffer->Lines = NULL;

	//setup the history index pointer
	historyEntry = NULL;

	// Setup the hInst global
	hInst = hInstance;
	// Do the setup
	if (!Setup(&hAccelTable))
		return 0;
	// Need to set up a console so that we can send ctrl-break signal
	// to inferior Caml
	AllocConsole();
	GetConsoleTitle(consoleTitle,sizeof(consoleTitle));
	hwndConsole = FindWindow(NULL,consoleTitle);
	ShowWindow(hwndConsole,SW_HIDE);
	// Create main window and exit if this fails
	if ((hwndMain = CreateinriaWndClassWnd()) == (HWND)0)
		return 0;
	// Create the status bar
	CreateSBar(hwndMain,"Ready",2);
	// Show the window
	ShowWindow(hwndMain,SW_SHOW);
	// Create the session window
	hwndSession = MDICmdFileNew("Session transcript",0);
	// Get the path to ocaml.exe
	GetOcamlPath();
	// Start the interpreter
	StartOcaml();
	// Show the session window
	ShowWindow(hwndSession, SW_SHOW);
	// Maximize it
	SendMessage(hwndMDIClient, WM_MDIMAXIMIZE, (WPARAM) hwndSession, 0);

	PostMessage(hwndMain,WM_USER+1000,0,0);
	while (GetMessage(&msg,NULL,0,0)) {
		if (!TranslateMDISysAccel(hwndMDIClient, &msg))
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
				TranslateMessage(&msg);  // Translates virtual key codes
				DispatchMessage(&msg);   // Dispatches message to window
			}
	}
	WriteToPipe("#quit;;\r\n\032");
	KillTimer((HWND) 0, TimerId);
	return msg.wParam;
}