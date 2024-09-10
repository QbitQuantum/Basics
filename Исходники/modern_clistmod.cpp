HRESULT  CluiLoadModule()
{
	CreateServiceFunction(MS_CLUI_GETCAPS,CLUIGetCapsService);

	InitDisplayNameCache();
	hookSystemShutdown_CListMod  = ModernHookEvent(ME_SYSTEM_SHUTDOWN,CListMod_ContactListShutdownProc);
	hookOptInitialise_CList      = ModernHookEvent(ME_OPT_INITIALISE,CListOptInit);
	hookOptInitialise_Skin       = ModernHookEvent(ME_OPT_INITIALISE,SkinOptInit);

	CreateServiceFunction("ModernSkinSel/Active", SvcActiveSkin);
	CreateServiceFunction("ModernSkinSel/Preview", SvcPreviewSkin);
	CreateServiceFunction("ModernSkinSel/Apply", SvcApplySkin);
	
	hookContactAdded_CListSettings = ModernHookEvent(ME_DB_CONTACT_ADDED,ContactAdded);	
	CreateServiceFunction(MS_CLIST_TRAYICONPROCESSMESSAGE,cli_TrayIconProcessMessage);
	CreateServiceFunction(MS_CLIST_PAUSEAUTOHIDE,TrayIconPauseAutoHide);
	CreateServiceFunction(MS_CLIST_CONTACTCHANGEGROUP,ContactChangeGroup);
	CreateServiceFunction(MS_CLIST_TOGGLEHIDEOFFLINE,ToggleHideOffline);

	CreateServiceFunction(MS_CLIST_TOGGLEGROUPS,ToggleGroups);
	CreateServiceFunction(MS_CLIST_TOGGLESOUNDS,ToggleSounds);
	CreateServiceFunction(MS_CLIST_SETUSEGROUPS,SetUseGroups);


	CreateServiceFunction(MS_CLIST_GETCONTACTICON,GetContactIcon);

	MySetProcessWorkingSetSize=(BOOL (WINAPI*)(HANDLE,SIZE_T,SIZE_T))GetProcAddress(GetModuleHandle(TEXT("kernel32")),"SetProcessWorkingSetSize");
	hCListImages = ImageList_Create(16, 16, ILC_MASK|ILC_COLOR32, 32, 0);
	InitCustomMenus();
	InitTray();
	{
		HINSTANCE hUser = GetModuleHandleA("USER32");
		MyMonitorFromPoint  = ( pfnMyMonitorFromPoint )GetProcAddress( hUser,"MonitorFromPoint" );
		MyMonitorFromWindow = ( pfnMyMonitorFromWindow )GetProcAddress( hUser, "MonitorFromWindow" );
		#if defined( _UNICODE )
			MyGetMonitorInfo = ( pfnMyGetMonitorInfo )GetProcAddress( hUser, "GetMonitorInfoW");
		#else
			MyGetMonitorInfo = ( pfnMyGetMonitorInfo )GetProcAddress( hUser, "GetMonitorInfoA");
		#endif
	}
	CLUI::InitClui();
	
	return S_OK;
}