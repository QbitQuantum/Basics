//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR lpCmdLine, int nShowCmd)
{
	wchar_t executableFullPath[MAX_PATH];
	GetModuleFileName( NULL, executableFullPath, MAX_PATH );

	wchar_t executableDrive[MAX_PATH];
	wchar_t executableDir[MAX_PATH];
	_wsplitpath_s(executableFullPath, executableDrive, MAX_PATH, executableDir, MAX_PATH, 0, 0, 0, 0);

	wchar_t currentDir[MAX_PATH] = { L'\0' };
	wcscat_s(currentDir, executableDrive);
	wcscat_s(currentDir, executableDir);
	wcscat_s(currentDir, L"..\\");

	BOOL result = SetCurrentDirectory(currentDir);
	ASSERT(result != FALSE, "Can't change current directory.");

	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// Set the callback functions
	DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
	DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
	DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
	DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
	DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
	DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
	DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
	DXUTSetCallbackMsgProc( MsgProc );
	DXUTSetCallbackFrameMove( OnFrameMove );

	// Initialize DXUT and create the desired Win32 window and Direct3D device for the application
	
	// Parse the command line and show msgboxes
	DXUTInit( true, true );
	
	// Handle the default hotkeys
	DXUTSetHotkeyHandling( true, true, true );
	
	// Show the cursor and clip it when in full screen
	DXUTSetCursorSettings( true, true ); 

	DXUTCreateWindow(L"GPU Pro 5 : 'Quaternions revisited'");
	DXUTCreateDevice(true, 1280, 720);

	// Start the render loop
	DXUTMainLoop();

	return DXUTGetExitCode();
}