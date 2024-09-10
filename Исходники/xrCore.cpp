void xrCore::_initialize	(LPCSTR _ApplicationName, LogCallback cb, BOOL init_fs, LPCSTR fs_fname)
{
	strcpy_s					(ApplicationName,_ApplicationName);
	if (0==init_counter) {
#ifdef XRCORE_STATIC	
		_clear87	();
		_control87	( _PC_53,   MCW_PC );
		_control87	( _RC_CHOP, MCW_RC );
		_control87	( _RC_NEAR, MCW_RC );
		_control87	( _MCW_EM,  MCW_EM );
#endif
		// Init COM so we can use CoCreateInstance
//		HRESULT co_res = 
			CoInitializeEx (NULL, COINIT_MULTITHREADED);

		strcpy_s			(Params,sizeof(Params),GetCommandLine());
		_strlwr_s			(Params,sizeof(Params));

		string_path		fn,dr,di;

		// application path
        GetModuleFileName(GetModuleHandle(MODULE_NAME),fn,sizeof(fn));
        _splitpath		(fn,dr,di,0,0);
        strconcat		(sizeof(ApplicationPath),ApplicationPath,dr,di);
#ifndef _EDITOR
		strcpy_s		(g_application_path,sizeof(g_application_path),ApplicationPath);
#endif

		// working path
        if( strstr(Params,"-wf") )
        {
            string_path				c_name;
            sscanf					(strstr(Core.Params,"-wf ")+4,"%[^ ] ",c_name);
            SetCurrentDirectory     (c_name);

        }
		GetCurrentDirectory(sizeof(WorkingPath),WorkingPath);
		// User/Comp Name
		DWORD	sz_user		= sizeof(UserName);
		GetUserName			(UserName,&sz_user);

		DWORD	sz_comp		= sizeof(CompName);
		GetComputerName		(CompName,&sz_comp);

		// Mathematics & PSI detection
		CPU::Detect			();
		
		Memory._initialize	(strstr(Params,"-mem_debug") ? TRUE : FALSE);
		
		DUMP_PHASE;

		InitLog				();
		_initialize_cpu		();

#ifdef DEBUG
	#ifndef DEDICATED_SERVER
		Debug._initialize	(FALSE);
	#else
		Debug._initialize	(TRUE);
	#endif
#endif
		rtc_initialize		();

		xr_FS				= xr_new<CLocatorAPI>	();

		xr_EFS				= xr_new<EFS_Utils>		();
//.		R_ASSERT			(co_res==S_OK);
	}
	if (init_fs){
		u32 flags			= 0;
		if (0!=strstr(Params,"-build"))	 flags |= CLocatorAPI::flBuildCopy;
		if (0!=strstr(Params,"-ebuild")) flags |= CLocatorAPI::flBuildCopy|CLocatorAPI::flEBuildCopy;
#ifdef DEBUG
		if (strstr(Params,"-cache"))  flags |= CLocatorAPI::flCacheFiles;
		else flags &= ~CLocatorAPI::flCacheFiles;
#endif // DEBUG
#ifdef _EDITOR // for EDITORS - no cache
		flags 				&=~ CLocatorAPI::flCacheFiles;
#endif // _EDITOR
		flags |= CLocatorAPI::flScanAppRoot;

#ifndef	_EDITOR
	#ifndef ELocatorAPIH
		if (0!=strstr(Params,"-file_activity"))	 flags |= CLocatorAPI::flDumpFileActivity;
	#endif
#endif
		FS._initialize		(flags,0,fs_fname);
		Msg					("'%s' build %d, %s\n","xrCore",build_id, build_date);
		EFS._initialize		();
#ifdef DEBUG
    #ifndef	_EDITOR
		Msg					("CRT heap 0x%08x",_get_heap_handle());
		Msg					("Process heap 0x%08x",GetProcessHeap());
    #endif
#endif // DEBUG
	}
	
	SetLogCB				(cb);

	LPAPI_VERSION ver = ImagehlpApiVersion();
	if ( NULL == GetProcAddress ( GetModuleHandle("dbghelp.dll"), "EnumerateLoadedModulesEx") )
	{
		string256 msg;		
		DWORD dwVer[2];
		WORD *v4 = (WORD*) &dwVer;
		CSymbolEngine SE;
		SE.GetInMemoryFileVersion("dbghelp.dll", dwVer[0], dwVer[1]);

		sprintf_s(msg, 256, "”старевший файл dbghelp.dll (%d.%d.%d.%d), его рекомендуетс¤ удалить.", 
								v4[1], v4[0], v4[3], v4[2]);
		MessageBox(NULL, msg, "DebugHlp Warning", MB_OK);
	}

	init_counter++;
}