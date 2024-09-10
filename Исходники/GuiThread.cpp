/*
 *	CGuiThread initialization: Load plugins, create windows & so on	
 */
BOOL CGuiThread::InitInstance()
{
	GUIThreadId = GetCurrentThreadId();

	HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE,FALSE,"Injection_load_dll_event");
	if(hEvent == 0)
	{
		// It is possible to load injection not with ILaunch. For example by
		// manually modifying client's import table
		OutputDebugString("Injection: DLL loaded not from ILaunch.");
	} else
		SetEvent(hEvent);

	// Initialize main window
	MainWindow = new CMainWindow();
	if(!MainWindow->Create())
	{
		char Buff[111];
		sprintf(Buff,"Error creating main window %08X",GetLastError());
		MessageBox(0,Buff,LoadString(IDS_ERROR),0);
	}

	// Enable error logging
	Log=new Logger;
/*
// DEBUG version always use verbose logging
#ifdef _DEBUG
	Log->set_verbose(true);
#else
	Log->set_verbose(false);
#endif
*/

	ReadRegistry();

//////////////////////////////////////////////////////////
//
//		 Here goes Injection initialization
//
//////////////////////////////////////////////////////////

	// Add predefined tabs
	MainTab = new CMainTab(MainWindow->GetTabCWnd());
	MainWindow->AddTab(MainTab->m_hWnd,"Main");

	DisplayTab = new CDisplayTab(MainWindow->GetTabCWnd());
	MainWindow->AddTab(DisplayTab->m_hWnd,"Display");

	ObjectsTab = new CObjectsTab(MainWindow->GetTabCWnd());
	MainWindow->AddTab(ObjectsTab->m_hWnd,"Objects");

	ObjectTypesTab = new CObjectTypesTab(MainWindow->GetTabCWnd());
	MainWindow->AddTab(ObjectTypesTab->m_hWnd,"Object Types");

	if(!HookClientWindowProc())
		error_printf("Unable to hook CreateWindow function!\n");

	if(!HookWinsockFunctions())
		error_printf("Unable to hook winsock.dll!\n");

	// Load plugins
	LoadPluginDLLs();

// This code was previously used to patch client using ignition.
// It is no longer necessary, but is left here as it may be needed
// in the future.
	if(!RemoveEncryptionFromClientWithPlugins())
	{
		trace_printf("All plugins refused to patch client\n");
	}

	// Find the encryption plugin in plugin list
	if(!InitEncryptionPlugin())
	{
		error_printf("Unable to load encryption plugin.");
		if(IDNO==MessageBox(0,LoadString(IDS_NOENCRYPTIONPLUGIN),LoadString(IDS_ERROR),
			MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2))
		{
			ExitProcess(1);
		}
	}

	// Make main window visible
	MainWindow->ShowWindow(SW_SHOW);

	// resume client execution
	SetEvent(hResumeClient);

	return TRUE;
}