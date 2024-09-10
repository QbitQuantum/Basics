HRESULT InitInstance(HINSTANCE hInstance, LPSTR lpCmdLine, long nCmdShow, DWORD dwWidth, DWORD dwHeight)
{
	// grab the ini file name from the command line
	char buf[256] = ".\\";
	if( !lpCmdLine || !strlen(lpCmdLine) )
		strcat( buf, g_szDefaultIni );
	else
		strcat( buf, lpCmdLine );
	
	// load main .ini file and create keyboard control
	const char szGroupName[] = "MODELS";
	g_pKeyboardControl = new KeyboardControl( buf, szGroupName );
	g_iNumModels = g_pKeyboardControl->GetInt( szGroupName, "NumModels", 0 );
	if( g_iNumModels )
	{
		g_szMenuModelNames = new LPSTR[g_iNumModels];
		g_szModelFileNames = new LPSTR[g_iNumModels];
		char buffer[256],mName[256], fName[256];
		for(int i=1; i <= g_iNumModels; i++)
		{
			wsprintf(buffer,"Model%d",i);
			strcpy(mName, g_pKeyboardControl->GetString( buffer, "Name", "Robot" ) );
			strcpy( fName, ".\\" );
			strcat(fName, g_pKeyboardControl->GetString( buffer, "File", "Robot" ) );
			g_szMenuModelNames[i-1] = new char[strlen(mName)+1];
			g_szModelFileNames[i-1] = new char[strlen(fName)+1];
			strcpy(g_szMenuModelNames[i-1],mName);
			strcpy(g_szModelFileNames[i-1],fName);
		}

		// select the first in the list
		strcat( g_szHandFileName, g_szModelFileNames[0] );
	}

	delete g_pKeyboardControl;
	g_pKeyboardControl = NULL;

	// create window
  WNDCLASS wc;
  wc.style         = CS_HREDRAW | CS_VREDRAW; // Class style(s).
  wc.lpfnWndProc   = (WNDPROC)WndProc;        // Window Procedure
  wc.cbClsExtra    = 0;                       // No per-class extra data.
  wc.cbWndExtra    = 0;                       // No per-window extra data.
  wc.hInstance     = hInstance;               // Owner of this class
  wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAND_ICON)); // Icon name from .RC
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);// Cursor
  wc.hbrBackground = (HBRUSH)(BLACK_BRUSH); // Default color
  wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAIN_MENU); // menu name from .RC
  wc.lpszClassName = g_szClassName;            // Name to register as

  if(!RegisterClass(&wc))
		return ERR_INIT;

  // Create a main window for this application instance.
  // adjust the size of the window so that the client size is the requested size
  RECT rcRect;
  SetRect(&rcRect, 0,0,dwWidth, dwHeight);

  DWORD dwStyle = WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_SYSMENU;
  AdjustWindowRectEx(&rcRect, dwStyle, TRUE,0);

  dwWidth = rcRect.right - rcRect.left;
  dwHeight = rcRect.bottom - rcRect.top;

  // create a window of this new size
  g_hWnd = CreateWindowEx( 0, g_szClassName, g_szTitle, dwStyle, 0, 0,
		dwWidth, dwHeight, NULL, NULL, hInstance, NULL );

  // If window could not be created, return "failure"
  if (! g_hWnd)
  {
	  return(ERR_INIT);
  }

  // Make the window visible; update its client area; and return "success"
  ShowWindow (g_hWnd, SW_SHOW); // Show the window
  UpdateWindow(g_hWnd);

  g_hInstance = hInstance;
  g_hMenu = GetMenu(g_hWnd);

	if (g_hMenu)
	{
		if (g_iNumModels > 0)
		{
			HMENU hModelMenu = CreateMenu();
			for(int i=1; i <= g_iNumModels; i++)
			{
				AppendMenu(hModelMenu,MF_STRING,500+i,g_szMenuModelNames[i-1]);
			}
			AppendMenu(g_hMenu,MF_POPUP|MF_STRING,(unsigned int)hModelMenu,"Model");
			DrawMenuBar(g_hWnd);
		}
	}

  return S_OK;              // We succeeded...
}