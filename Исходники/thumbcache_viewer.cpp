int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	unsigned char fail_type = 0;

	// Initialize GDI+.
	Gdiplus::GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );

	// Blocks our reading thread and various GUI operations.
	InitializeCriticalSection( &pe_cs );

	// Get the default message system font.
	NONCLIENTMETRICS ncm = { NULL };
	ncm.cbSize = sizeof( NONCLIENTMETRICS );
	SystemParametersInfo( SPI_GETNONCLIENTMETRICS, sizeof( NONCLIENTMETRICS ), &ncm, 0 );

	// Set our global font to the LOGFONT value obtained from the system.
	hFont = CreateFontIndirect( &ncm.lfMessageFont );

	// Get the row height for our listview control.
	TEXTMETRIC tm;
	HDC hDC = GetDC( NULL );
	HFONT ohf = ( HFONT )SelectObject( hDC, hFont );
	GetTextMetricsW( hDC, &tm );
	SelectObject( hDC, ohf );	// Reset old font.
	ReleaseDC( NULL, hDC );

	row_height = tm.tmHeight + tm.tmExternalLeading + 5;

	int icon_height = GetSystemMetrics( SM_CYSMICON ) + 2;
	if ( row_height < icon_height )
	{
		row_height = icon_height;
	}

	// Get the system icon for each of the three file types.
	SHFILEINFOA shfi = { NULL }; 
	SHGetFileInfoA( ".bmp", FILE_ATTRIBUTE_NORMAL, &shfi, sizeof( shfi ), SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES );
	hIcon_bmp = shfi.hIcon;
	SHGetFileInfoA( ".png", FILE_ATTRIBUTE_NORMAL, &shfi, sizeof( shfi ), SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES );
	hIcon_png = shfi.hIcon;
	SHGetFileInfoA( ".jpg", FILE_ATTRIBUTE_NORMAL, &shfi, sizeof( shfi ), SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES );
	hIcon_jpg = shfi.hIcon;

	// Initialize our window class.
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof( WNDCLASSEX );
	wcex.style          = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc    = MainWndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON ) );
	wcex.hCursor        = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground  = ( HBRUSH )( COLOR_WINDOW );
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = L"thumbcache";
	wcex.hIconSm        = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_APPLICATION ) );

	if ( !RegisterClassEx( &wcex ) )
	{
		fail_type = 1;
		goto CLEANUP;
	}

	wcex.lpfnWndProc    = ImageWndProc;
	wcex.lpszClassName  = L"image";

	if ( !RegisterClassEx( &wcex ) )
	{
		fail_type = 1;
		goto CLEANUP;
	}

	wcex.lpfnWndProc    = ScanWndProc;
	wcex.lpszClassName  = L"scan";

	if ( !RegisterClassEx( &wcex ) )
	{
		fail_type = 1;
		goto CLEANUP;
	}

	wcex.lpfnWndProc    = InfoWndProc;
	wcex.lpszClassName  = L"info";

	if ( !RegisterClassEx( &wcex ) )
	{
		fail_type = 1;
		goto CLEANUP;
	}

	wcex.lpfnWndProc    = PropertyWndProc;
	wcex.lpszClassName  = L"property";

	if ( !RegisterClassEx( &wcex ) )
	{
		fail_type = 1;
		goto CLEANUP;
	}

	g_hWnd_main = CreateWindow( L"thumbcache", PROGRAM_CAPTION, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, ( ( GetSystemMetrics( SM_CXSCREEN ) - MIN_WIDTH ) / 2 ), ( ( GetSystemMetrics( SM_CYSCREEN ) - MIN_HEIGHT ) / 2 ), MIN_WIDTH, MIN_HEIGHT, NULL, NULL, NULL, NULL );

	if ( !g_hWnd_main )
	{
		fail_type = 2;
		goto CLEANUP;
	}

	g_hWnd_image = CreateWindow( L"image", PROGRAM_CAPTION, WS_OVERLAPPEDWINDOW, ( ( GetSystemMetrics( SM_CXSCREEN ) - MIN_WIDTH ) / 2 ), ( ( GetSystemMetrics( SM_CYSCREEN ) - MIN_HEIGHT ) / 2 ), MIN_HEIGHT, MIN_HEIGHT, NULL, NULL, NULL, NULL );

	if ( !g_hWnd_image )
	{
		fail_type = 2;
		goto CLEANUP;
	}

	g_hWnd_scan = CreateWindow( L"scan", L"Map File Paths to Cache Entry Hashes", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_CLIPCHILDREN, ( ( GetSystemMetrics( SM_CXSCREEN ) - MIN_WIDTH ) / 2 ), ( ( GetSystemMetrics( SM_CYSCREEN ) - ( MIN_HEIGHT - 115 ) ) / 2 ), MIN_WIDTH, ( MIN_HEIGHT - 115 ), g_hWnd_main, NULL, NULL, NULL );

	if ( !g_hWnd_scan )
	{
		fail_type = 2;
		goto CLEANUP;
	}

	g_hWnd_info = CreateWindow( L"info", L"Extended Information", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, ( ( GetSystemMetrics( SM_CXSCREEN ) - MIN_WIDTH ) / 2 ), ( ( GetSystemMetrics( SM_CYSCREEN ) - MIN_WIDTH ) / 2 ), MIN_WIDTH, MIN_WIDTH, NULL, NULL, NULL, NULL );

	if ( !g_hWnd_info )
	{
		fail_type = 2;
		goto CLEANUP;
	}

	g_hWnd_property = CreateWindow( L"property", L"Property Value", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, ( ( GetSystemMetrics( SM_CXSCREEN ) - MIN_HEIGHT ) / 2 ), ( ( GetSystemMetrics( SM_CYSCREEN ) - MIN_HEIGHT ) / 2 ), MIN_HEIGHT, MIN_HEIGHT, NULL, NULL, NULL, NULL );

	if ( !g_hWnd_property )
	{
		fail_type = 2;
		goto CLEANUP;
	}

	// See if we have any command-line parameters
	if ( lpCmdLine != NULL && lpCmdLine[ 0 ] != NULL )
	{
		// Count the number of parameters and split them into an array.
		int argCount = 0;
		LPWSTR *szArgList = CommandLineToArgvW( GetCommandLine(), &argCount );
		if ( szArgList != NULL )
		{
			// The first parameter is the path to the executable. Ignore it.
			if ( argCount > 1 )
			{
				// Allocate enough space to hold each parameter. They should all be full paths.
				pathinfo *pi = ( pathinfo * )malloc( sizeof( pathinfo ) );
				pi->type = 0;
				pi->offset = 0;
				pi->output_path = NULL;
				pi->filepath = ( wchar_t * )malloc( sizeof( wchar_t ) * ( ( MAX_PATH * ( argCount - 1 ) ) + 1 ) );
				wmemset( pi->filepath, 0, ( ( MAX_PATH * ( argCount - 1 ) ) + 1 ) );

				cmd_line = 1;	// Open the database(s) from the command-line.

				int filepath_offset = 0;
				for ( int i = 1; i < argCount; ++i )
				{
					int filepath_length = wcslen( szArgList[ i ] );

					// See if it's an output parameter.
					if ( filepath_length > 1 && szArgList[ i ][ 0 ] == L'-' && ( szArgList[ i ][ 1 ] == L'o' || szArgList[ i ][ 1 ] == L'O' ) )
					{
						// See if the next parameter exists. We'll assume it's the output directory.
						if ( i + 1 < argCount )
						{
							if ( pi->output_path != NULL )
							{
								free( pi->output_path );
							}

							pi->output_path = _wcsdup( szArgList[ ++i ] );
							pi->type = 0;

							cmd_line = 2;	// Save the database(s) from the command-line. Do not display the main window or any prompts.
						}
					}
					else if ( filepath_length > 1 && szArgList[ i ][ 0 ] == L'-' && ( szArgList[ i ][ 1 ] == L'c' || szArgList[ i ][ 1 ] == L'C' ) )
					{
						// See if the next parameter exists. We'll assume it's the output directory.
						if ( i + 1 < argCount )
						{
							if ( pi->output_path != NULL )
							{
								free( pi->output_path );
							}

							pi->output_path = _wcsdup( szArgList[ ++i ] );
							pi->type = 1;

							cmd_line = 2;	// Save the database(s) from the command-line. Do not display the main window or any prompts.
						}
					}
					else if ( filepath_length > 1 && szArgList[ i ][ 0 ] == L'-' && ( szArgList[ i ][ 1 ] == L'z' || szArgList[ i ][ 1 ] == L'Z' ) )
					{
						hide_blank_entries = true;

						// Put a check next to the menu item. g_hMenu is created in g_hWnd_main.
						CheckMenuItem( g_hMenu, MENU_HIDE_BLANK, MF_CHECKED );
					}
					else	// Copy the paths into the NULL separated filepath.
					{
						// If the user typed a relative path, get the full path.
						wchar_t full_path[ MAX_PATH ] = { 0 };
						DWORD full_path_length = min( GetFullPathName( szArgList[ i ], MAX_PATH, full_path, NULL ), MAX_PATH );

						wmemcpy_s( pi->filepath + filepath_offset, ( ( MAX_PATH * ( argCount - 1 ) ) + 1 ) - filepath_offset, full_path, full_path_length + 1 );
						filepath_offset += ( full_path_length + 1 );
					}
				}

				// Only read the database if there's a file to open.
				if ( pi->filepath[ 0 ] != NULL )
				{
					// filepath will be freed in the thread.
					CloseHandle( ( HANDLE )_beginthreadex( NULL, 0, &read_thumbcache, ( void * )pi, 0, NULL ) );
				}
				else
				{
					// Cleanup our parameters structure and exit the program.
					free( pi->output_path );
					free( pi->filepath );
					free( pi );

					cmd_line = -1;

					SendMessage( g_hWnd_main, WM_DESTROY_ALT, 0, 0 );
				}
			}

			// Free the parameter list.
			LocalFree( szArgList );
		}
	}

	if ( cmd_line == 0 || cmd_line == 1 )
	{
		ShowWindow( g_hWnd_main, SW_SHOW );
	}

	// Main message loop:
	MSG msg;
	while ( GetMessage( &msg, NULL, 0, 0 ) > 0 )
	{
		if ( g_hWnd_active == NULL || !IsDialogMessage( g_hWnd_active, &msg ) )	// Checks tab stops.
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

CLEANUP:

	// Destroy our icons.
	DestroyIcon( hIcon_jpg );
	DestroyIcon( hIcon_png );
	DestroyIcon( hIcon_bmp );

	// Delete our font.
	DeleteObject( hFont );

	// Delete our critical section.
	DeleteCriticalSection( &pe_cs );

	// Shutdown GDI+
	Gdiplus::GdiplusShutdown( gdiplusToken );

	// Unload the modules if they were initialized.
	UnInitializeMsSrch();
	UnInitializeMsSCB();

	if ( fail_type == 1 )
	{
		MessageBoxA( NULL, "Call to RegisterClassEx failed!", PROGRAM_CAPTION_A, MB_ICONWARNING );
	}
	else if ( fail_type == 2 )
	{
		MessageBoxA( NULL, "Call to CreateWindow failed!", PROGRAM_CAPTION_A, MB_ICONWARNING );
	}

	return ( int )msg.wParam;
}