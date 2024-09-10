int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	Q_UNUSED( hPrevInstance );
	Q_UNUSED( nShowCmd );
#if defined(_DEBUG)
	/*	AllocConsole();
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = 500;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
		int hConHandle;
		long lStdHandle;
		FILE *fp;
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "w" );
		*stdout = *fp;
		setvbuf( stdout, NULL, _IONBF, 0 );
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "w" );
		*stderr = *fp;
		setvbuf( stderr, NULL, _IONBF, 0 );
		QString consoleTitle = QString("%1 %2 %3 - Debug Console").arg(productString()).arg(productBeta()).arg(productVersion());
		SetConsoleTitle(consoleTitle.latin1());*/
#endif

	INITCOMMONCONTROLSEX initex;
	initex.dwICC = ICC_WIN95_CLASSES;
	initex.dwSize = sizeof( INITCOMMONCONTROLSEX );
	InitCommonControlsEx( &initex );
#pragma comment(lib, "comctl32.lib") // needed for InitCommonControlsEx call
	appInstance = hInstance;
	guiThread = GetCurrentThreadId();

	// Try to load riched20.dll
	HMODULE hRiched = LoadLibrary( "riched20.dll" );

	if ( !hRiched )
	{
		MessageBox( 0, "The riched20.dll library could not be found on your system.\nPlease install Microsoft Internet Explorer 4.0 or later.", "Missing DLL", MB_OK | MB_ICONERROR );
		return 1;
	}

	hbSeparator = CreateSolidBrush( RGB( 0xAF, 0xAF, 0xAF ) );
	hbBackground = CreateSolidBrush( RGB( 0, 64, 38 ) );
	iconGreen = ( HICON ) LoadImage( appInstance, MAKEINTRESOURCE( IDI_ICONGREEN ), IMAGE_ICON, 16, 16, 0 );
	iconRed = ( HICON ) LoadImage( appInstance, MAKEINTRESOURCE( IDI_ICONRED ), IMAGE_ICON, 16, 16, 0 );

	// Create the WindowClass
	WNDCLASSEX wpClass;
	ZeroMemory( &wpClass, sizeof( WNDCLASSEX ) );
	wpClass.cbSize = sizeof( WNDCLASSEX );
	wpClass.hInstance = hInstance;
	wpClass.lpfnWndProc = wpWindowProc;
	wpClass.hCursor = LoadCursor( NULL, MAKEINTRESOURCE( IDC_ARROW ) );
	wpClass.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );
	wpClass.hbrBackground = hbBackground;
	wpClass.lpszClassName = WOLFPACK_CLASS;
	wpClass.hIconSm = iconRed;
	wpClass.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;

	if ( !RegisterClassEx( &wpClass ) )
	{
		MessageBox( 0, "Couldn't register Window Class.", "Window Class", MB_OK | MB_ICONERROR );
		return 1;
	}

	// Create the Window itself
	hmMainMenu = LoadMenu( appInstance, MAKEINTRESOURCE( IDR_MAINMENU ) );
	mainWindow = CreateWindow( WOLFPACK_CLASS, "Wolfpack", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, hmMainMenu, hInstance, NULL );

	if ( mainWindow == 0 )
	{
		MessageBox( 0, QString( "Couldn't create the window: " + getErrorString() ).latin1(), "Wolfpack", MB_OK | MB_ICONERROR );
		return 1;
	}

	ShowWindow( mainWindow, SW_NORMAL );

	// Create the System Tray Icon
	ZeroMemory( &icondata, sizeof( icondata ) );
	icondata.cbSize = sizeof( icondata );
	icondata.hWnd = mainWindow;
	icondata.uID = 0;
	icondata.uFlags = NIF_MESSAGE | NIF_ICON;
	icondata.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );
	icondata.uCallbackMessage = WM_TRAY_NOTIFY;

#if !defined(TTS_BALLOON)
# define TTS_BALLOON			 0x40
#endif

	// This is "ported" from MFC
	tooltip = CreateWindowEx( WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | TTS_BALLOON, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, mainWindow, NULL, hInstance, NULL );

	if ( tooltip )
	{
		TOOLINFO info;
		info.cbSize = sizeof( info );
		info.uFlags = TTF_TRANSPARENT | TTF_CENTERTIP;
		info.hwnd = mainWindow;
		info.uId = 0;
		info.hinst = 0;
		info.lpszText = LPSTR_TEXTCALLBACK;
		GetClientRect( mainWindow, &info.rect );
		SendMessage( tooltip, TTM_ADDTOOL, 0, ( LPARAM ) & info );
	}
	Shell_NotifyIconA( NIM_ADD, ( PNOTIFYICONDATAA ) & icondata );

	cServerThread serverThread( lpCmdLine );
	serverThread.start();

	MSG msg;

	while ( GetMessage( &msg, 0, 0, 0 ) > 0 )
	{
		if ( msg.message == WM_CHAR && msg.hwnd == inputWindow && msg.wParam == '\r' )
		{
			if ( Server::instance()->getState() == RUNNING )
			{
				char command[512] =
				{
				0,
				};
				GetWindowText( inputWindow, command, 512 );
				SetWindowText( inputWindow, "" );

				// We are in a different Thread. Remember that.
				Console::instance()->queueCommand( command );
			}

			continue;
		}
		else if ( msg.message == WM_TIMER )
		{
			char message[512];

			unsigned int seconds, minutes, hours, days;
			days = Server::instance()->time() / 86400000;
			hours = ( Server::instance()->time() % 86400000 ) / 3600000;
			minutes = ( ( Server::instance()->time() % 86400000 ) % 3600000 ) / 60000;
			seconds = ( ( ( Server::instance()->time() % 86400000 ) % 3600000 ) % 60000 ) / 1000;

			sprintf( message, "Uptime: %u:%02u:%02u:%02u", days, hours, minutes, seconds );
			SetWindowText( lblUptime, message );

			// Update the icon
			static unsigned int lastState = 0xFFFFFFFF;

			if ( lastState != Server::instance()->getState() )
			{
				if ( Server::instance()->getState() == RUNNING )
				{
					SendMessage( mainWindow, WM_SETICON, ICON_SMALL, ( WPARAM ) iconGreen );
					SendMessage( statusIcon, STM_SETIMAGE, IMAGE_ICON, ( LPARAM ) iconGreen );
				}
				else
				{
					SendMessage( mainWindow, WM_SETICON, ICON_SMALL, ( WPARAM ) iconRed );
					SendMessage( statusIcon, STM_SETIMAGE, IMAGE_ICON, ( LPARAM ) iconRed );
				}
			}
			lastState = Server::instance()->getState();
		}

		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	Shell_NotifyIconA( NIM_DELETE, ( PNOTIFYICONDATAA ) & icondata );

	Server::instance()->cancel();

	serverThread.wait();

	return serverThread.returnValue();
}