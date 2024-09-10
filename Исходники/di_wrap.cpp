bool WrapperSystem::Init( HANDLE mod_hnd ) {

	char dinputDllName[ MAX_PATH ];

	// returns with system32 even on win64 32bit mode, but image loader solves it
	GetSystemDirectoryA( dinputDllName, MAX_PATH );

	button6ShutdownEvent.Clear( );
	button6ShutdownEvent.SetType( type_button_6 );
	button6ShutdownEvent.usButtonFlags = 0x800;
	button6ShutdownEvent.usButtonData = 0;
	button7ShutdownEvent.Clear( );
	button7ShutdownEvent.SetType( type_button_7 );
	button7ShutdownEvent.usButtonFlags = 0x800;
	button7ShutdownEvent.usButtonData = 0;

	memset( immediateBuffer, 0, sizeof( LONG ) * type_list_size );
	bufferedMode = false;

#ifdef DI_WRAPPER8
	strcat( dinputDllName, "\\dinput8.dll" );
#else
	strcat( dinputDllName, "\\dinput.dll" );
#endif

	dinputDll = LoadLibraryA( dinputDllName );

	// MSDN: If the function succeeds, the return value is greater than 31.
	if( dinputDll > ( HMODULE )31 ) {

#ifdef DI_WRAPPER8
		DirectInput8Create = ( DIRECTINPUT8CREATEPROC )GetProcAddress( dinputDll, "DirectInput8Create" );
		if( !DirectInput8Create ) {
#else
		DirectInputCreateA = ( DIRECTINPUTCREATEAPROC )GetProcAddress( dinputDll, "DirectInputCreateA" );
		if( !DirectInputCreateA ) {
#endif

			Shutdown( );
			return false;
		}

		wrapperModule = mod_hnd;
		return true;
	}

	return false;
}

void WrapperSystem::Shutdown( ) {

	for( WrapperList::iterator wrpItr = wrappers.begin( ); wrpItr != wrappers.end( ); wrpItr++ ) {

		delete *wrpItr;
	}

	bufferedMode = false;

	if( hookHandleGetMessage ) {
		
		UnhookWindowsHookEx( hookHandleGetMessage );
		hookHandleGetMessage = 0;
	}

	if( hookHandleCallWnd ) {
		
		UnhookWindowsHookEx( hookHandleCallWnd );
		hookHandleCallWnd = 0;
	}

	FreeLibrary( dinputDll );
}

void WrapperSystem::InitHID( HWND & h_wnd ) {

	RECT windowRect = { 0 };

	if( hidInitialized ) return;

	// jk2 sends a null hwnd, and RegisterRawInputDevices fails without it, so grab one with GetForegroundWindow
	if( !h_wnd ) {

		h_wnd = GetForegroundWindow( );
	}

	RAWINPUTDEVICE Rid;
	Rid.usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid.usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid.dwFlags = RIDEV_INPUTSINK;
	Rid.hwndTarget = h_wnd;

	if( !RegisterRawInputDevices( &Rid, 1, sizeof( RAWINPUTDEVICE ) ) ) return;

	// register our hook into the game main message loop
	if( !( hookHandleGetMessage = SetWindowsHookExA( WH_GETMESSAGE, WindowHookFuncGetMessage, ( HINSTANCE )wrapperModule, GetCurrentThreadId( ) ) ) ) return;
	if( !( hookHandleCallWnd = SetWindowsHookExA( WH_CALLWNDPROC, WindowHookFuncCallWnd, ( HINSTANCE )wrapperModule, GetCurrentThreadId( ) ) ) ) return;

	hidInitialized = true;
}