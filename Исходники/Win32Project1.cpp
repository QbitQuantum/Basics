//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_MAXIMIZEBOX| WS_MINIMIZEBOX| WS_SYSMENU,
      0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   INITCOMMONCONTROLSEX InitCtrlEx;

   InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
   InitCtrlEx.dwICC = ICC_BAR_CLASSES;
   InitCommonControlsEx(&InitCtrlEx);

   TBBUTTON tbrButtons[10];

   tbrButtons[0].iBitmap = 0;
   tbrButtons[0].idCommand = ID_FILE_OPEN;
   tbrButtons[0].fsState = TBSTATE_ENABLED;
   tbrButtons[0].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[0].dwData = 0L;
   tbrButtons[0].iBitmap = 0;
   tbrButtons[0].iString = 0;

   tbrButtons[1].iBitmap = 1;
   tbrButtons[1].idCommand = ID_FILE_SAVE;
   tbrButtons[1].fsState = TBSTATE_ENABLED;
   tbrButtons[1].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[1].dwData = 0L;
   tbrButtons[1].iString = 0;

   tbrButtons[2].iBitmap = 0;
   tbrButtons[2].idCommand =0;
   tbrButtons[2].fsState = TBSTATE_ENABLED;
   tbrButtons[2].fsStyle = TBSTYLE_SEP;
   tbrButtons[2].dwData = 0L;
   tbrButtons[2].iString = 0;

   tbrButtons[3].iBitmap = 2;
   tbrButtons[3].idCommand = ID_FORMAT_COLOR;
   tbrButtons[3].fsState = TBSTATE_ENABLED;
   tbrButtons[3].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[3].dwData = 0L;
   tbrButtons[3].iString = 0;

   tbrButtons[4].iBitmap = 3;
   tbrButtons[4].idCommand = ID_SHAPE_SQUARE;
   tbrButtons[4].fsState = TBSTATE_ENABLED;
   tbrButtons[4].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[4].dwData = 0L;
   tbrButtons[4].iString = 0;

   tbrButtons[5].iBitmap = 4;
   tbrButtons[5].idCommand = ID_SHAPE_ROUND;
   tbrButtons[5].fsState = TBSTATE_ENABLED;
   tbrButtons[5].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[5].dwData = 0L;
   tbrButtons[5].iString = 0;

   tbrButtons[6].iBitmap = 5;
   tbrButtons[6].idCommand = ID_LINE_STRAIGHTLINE;
   tbrButtons[6].fsState = TBSTATE_ENABLED;
   tbrButtons[6].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[6].dwData = 0L;
   tbrButtons[6].iString = 0;

   tbrButtons[7].iBitmap = 6;
   tbrButtons[7].idCommand = ID_SHAPE_ELLIPSE;
   tbrButtons[7].fsState = TBSTATE_ENABLED;
   tbrButtons[7].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[7].dwData = 0L;
   tbrButtons[7].iString = 0;

   tbrButtons[8].iBitmap = 7;
   tbrButtons[8].idCommand = ID_SHAPE_RECTANGLE;
   tbrButtons[8].fsState = TBSTATE_ENABLED;
   tbrButtons[8].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[8].dwData = 0L;
   tbrButtons[8].iString = 0;

   tbrButtons[9].iBitmap = 8;
   tbrButtons[9].idCommand = ID_LINE_FREESTYLE;
   tbrButtons[9].fsState = TBSTATE_ENABLED;
   tbrButtons[9].fsStyle = TBSTYLE_BUTTON;
   tbrButtons[9].dwData = 0L;
   tbrButtons[9].iString = 0;

   HWND hWndToolbar;
   hWndToolbar = CreateToolbarEx(hWnd,
	   WS_VISIBLE | WS_CHILD | WS_BORDER,
	   IDB_BITMAP1,
	   NUMBUTTONS,
	   hInst,
	   IDB_BITMAP1,
	   tbrButtons,
	   NUMBUTTONS,
	   16, 16, 16, 16,
	   sizeof(TBBUTTON));

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}