int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// msg is used for windows to communicate with the window we create
	MSG msg;
	// no f*****g idea
	HACCEL hAccelTable;

	// sets global variables
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NSGAME, szWindowClass, MAX_LOADSTRING);

	// Each window is contained in a window object this function creates it and 
	// registers it with windows
	MyRegisterClass(hInstance);
	
	// Game object
	Game GAME;
	// Window handle
	HWND hWnd;

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow, hWnd ))
	{
		return FALSE;
	}
	
	// Some wizardry pokery
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NSGAME));

	PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );

	// Main message loop:
	while (msg.message!=WM_QUIT)
	{
		// Windows checks msg from system makes sure nothing is on fire etc, 
		// this only does stuff if our program is not running now
		if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// it hands the message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// Main game loop!!
			switch(game_state)
			{
				case GAME_INIT:
				{
					// Here we could load a config file to initialize the game a different way

					// Load engine, graphics, sound, input, world
					if(! GAME.initialise(hWnd,hInst) )
					{
						// error
					}
					else
					{
						game_state = GAME_MENU;
					}
					break;
				}
				case GAME_MENU:
				{
					if(! GAME.menu(hWnd) )
					{
						// error
					}
					else
					{
						game_state = GAME.getGameState();
					}
					break;

				}
			    case GAME_LOAD:
				{
					if(! GAME.load() )
					{
						// error
					}
					break;
				}
			    case GAME_RUN:
				{
					if(! GAME.run() )
					{
						// error
					}
					else
					{
						game_state = GAME.getGameState();
					}
					break;
				}
				case GAME_RESTART:
				{
					game_state = GAME.menu(hWnd);
					break;
				}
				case GAME_EXIT:
				{
					GAME.exit();
					msg.message=WM_DESTROY;
					SendMessage(hWnd,WM_DESTROY,NULL,NULL);
					break;
				}
				default: break;
			}
		}
	}

	return (int) msg.wParam;
}