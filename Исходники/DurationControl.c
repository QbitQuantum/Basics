VOID WINAPI 
InitPGPDurationControl (VOID) 
{
	WNDCLASS  wc;
	
	InitCommonControls ();

	// register new window class
	wc.style = CS_DBLCLKS | CS_GLOBALCLASS | CS_PARENTDC; // Class style(s).
	wc.lpfnWndProc = (WNDPROC) sDurationMsgProc; 
	wc.cbClsExtra = 0;	                        // No per-class extra data.
	wc.cbWndExtra = sizeof (DCWndData*);		// pointer to extra data 
												//		structure
	wc.hInstance = 0;	
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1); // Background color
	wc.lpszMenuName = NULL;						// No menu
	wc.lpszClassName = WC_PGPDURATION;			// Name used in CreateWindow
	RegisterClass (&wc);

}