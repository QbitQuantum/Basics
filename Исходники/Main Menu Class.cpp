bool CMainMenu::ProcessMessage(HWND hWnd, DWORD /*FromAccelerator*/, DWORD MenuID)
{
	switch (MenuID) {
	case ID_FILE_OPEN_ROM: 
		{
			stdstr File = g_BaseSystem->ChooseFileToOpen(hWnd);
			if (File.length() > 0) {
				g_BaseSystem->RunFileImage(File.c_str());
			}
		}
		break;
	case ID_FILE_ROM_INFO:
		{
			g_BaseSystem->DisplayRomInfo(hWnd);
		}
		break;
	case ID_FILE_STARTEMULATION:
		_Gui->SaveWindowLoc();
		//Before we go and create the new system, ensure the previous one has been closed
		CN64System::CloseSystem();
		//Ok now g_BaseSystem should definitely be clean for initialization
		g_BaseSystem = new CN64System(g_Plugins, false);
		//Now we have created again, we can start up emulation
		g_BaseSystem->StartEmulation(true);
		break;
	case ID_FILE_ENDEMULATION: 
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_FILE_ENDEMULATION");
		CN64System::CloseSystem();
		_Gui->SaveWindowLoc();
		break;
	case ID_FILE_ROMDIRECTORY:   
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_FILE_ROMDIRECTORY 1");
		_Gui->SelectRomDir(); 
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_FILE_ROMDIRECTORY 2");
		_Gui->RefreshMenu();
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_FILE_ROMDIRECTORY 3");
		break;
	case ID_FILE_REFRESHROMLIST: _Gui->RefreshRomBrowser(); break;
	case ID_FILE_EXIT:           DestroyWindow((HWND)hWnd); break;
	case ID_SYSTEM_RESET_SOFT:
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_RESET_SOFT"); 
		g_BaseSystem->ExternalEvent(SysEvent_ResetCPU_Soft); 
		break;
	case ID_SYSTEM_RESET_HARD:
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_RESET_HARD"); 
		g_BaseSystem->ExternalEvent(SysEvent_ResetCPU_Hard); 
		break;
	case ID_SYSTEM_PAUSE:        
		_Gui->SaveWindowLoc();
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_PAUSE");
		if (g_Settings->LoadBool(GameRunning_CPU_Paused))
		{
			g_BaseSystem->ExternalEvent(SysEvent_ResumeCPU_FromMenu); 
		} else {
			g_BaseSystem->ExternalEvent(SysEvent_PauseCPU_FromMenu); 
		}
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_PAUSE 1");
		break;
	case ID_SYSTEM_BITMAP:
		{
			stdstr Dir(g_Settings->LoadString(Directory_SnapShot));
			WriteTraceF(TraceGfxPlugin,__FUNCTION__ ": CaptureScreen(%s): Starting",Dir.c_str());
			g_Plugins->Gfx()->CaptureScreen(Dir.c_str());
			WriteTrace(TraceGfxPlugin,__FUNCTION__ ": CaptureScreen: Done");
		}
		break;
	case ID_SYSTEM_LIMITFPS:
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_LIMITFPS");
		g_Settings->SaveBool(GameRunning_LimitFPS,!g_Settings->LoadBool(GameRunning_LimitFPS));
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_LIMITFPS 1");
		break;
	case ID_SYSTEM_SAVE:
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_SAVE"); 
		g_BaseSystem->ExternalEvent(SysEvent_SaveMachineState); 
		break;
	case ID_SYSTEM_SAVEAS:
		{
			char drive[_MAX_DRIVE] ,dir[_MAX_DIR], fname[_MAX_FNAME],ext[_MAX_EXT];
			char Directory[255], SaveFile[255];
			OPENFILENAME openfilename;

			memset(&SaveFile, 0, sizeof(SaveFile));
			memset(&openfilename, 0, sizeof(openfilename));

			g_Settings->LoadString(Directory_LastSave, Directory,sizeof(Directory));

			openfilename.lStructSize  = sizeof( openfilename );
			openfilename.hwndOwner    = (HWND)hWnd;
			openfilename.lpstrFilter  = "PJ64 Saves (*.zip, *.pj)\0*.pj?;*.pj;*.zip;";
			openfilename.lpstrFile    = SaveFile;
			openfilename.lpstrInitialDir    = Directory;
			openfilename.nMaxFile     = MAX_PATH;
			openfilename.Flags        = OFN_HIDEREADONLY;

			g_BaseSystem->ExternalEvent(SysEvent_PauseCPU_SaveGame);
			if (GetSaveFileName (&openfilename)) 
			{

				_splitpath( SaveFile, drive, dir, fname, ext );
				if (_stricmp(ext, ".pj") == 0 || _stricmp(ext, ".zip") == 0) 
				{
					_makepath( SaveFile, drive, dir, fname, NULL );
					_splitpath( SaveFile, drive, dir, fname, ext );
					if (_stricmp(ext, ".pj") == 0) 
					{
						_makepath( SaveFile, drive, dir, fname, NULL );
					}
				}
				g_Settings->SaveString(GameRunning_InstantSaveFile, SaveFile);

				char SaveDir[MAX_PATH];
				_makepath( SaveDir, drive, dir, NULL, NULL );
				g_Settings->SaveString(Directory_LastSave,SaveDir);
				g_BaseSystem->ExternalEvent(SysEvent_SaveMachineState);
			}
			g_BaseSystem->ExternalEvent(SysEvent_ResumeCPU_SaveGame);
		}
		break;
	case ID_SYSTEM_RESTORE:   WriteTrace(TraceDebug,__FUNCTION__ ": ID_SYSTEM_RESTORE");   g_BaseSystem->ExternalEvent(SysEvent_LoadMachineState); break;
	case ID_SYSTEM_LOAD:
		{
			char Directory[255], SaveFile[255];
			OPENFILENAME openfilename;

			memset(&SaveFile, 0, sizeof(SaveFile));
			memset(&openfilename, 0, sizeof(openfilename));

			g_Settings->LoadString(Directory_LastSave, Directory,sizeof(Directory));

			openfilename.lStructSize  = sizeof( openfilename );
			openfilename.hwndOwner    = (HWND)hWnd;
			openfilename.lpstrFilter  = "PJ64 Saves (*.zip, *.pj)\0*.pj?;*.pj;*.zip;";
			openfilename.lpstrFile    = SaveFile;
			openfilename.lpstrInitialDir    = Directory;
			openfilename.nMaxFile     = MAX_PATH;
			openfilename.Flags        = OFN_HIDEREADONLY;

			g_BaseSystem->ExternalEvent(SysEvent_PauseCPU_LoadGame);
			if (GetOpenFileName (&openfilename)) {
				g_Settings->SaveString(GameRunning_InstantSaveFile,SaveFile);
				char SaveDir[MAX_PATH], drive[_MAX_DRIVE] ,dir[_MAX_DIR], fname[_MAX_FNAME],ext[_MAX_EXT];
				_splitpath( SaveFile, drive, dir, fname, ext );
				_makepath( SaveDir, drive, dir, NULL, NULL );
				g_Settings->SaveString(Directory_LastSave,SaveDir);
				g_System->LoadState();
			}
			g_BaseSystem->ExternalEvent(SysEvent_ResumeCPU_LoadGame);
		}
		break;
	case ID_SYSTEM_CHEAT:
		{
			g_BaseSystem->SelectCheats(hWnd);
		}
		break;
	case ID_SYSTEM_GSBUTTON:
		g_BaseSystem->ExternalEvent(SysEvent_GSButtonPressed);
		break;
	case ID_OPTIONS_DISPLAY_FR:
		g_Settings->SaveBool(UserInterface_DisplayFrameRate,!g_Settings->LoadBool(UserInterface_DisplayFrameRate));
		break;
	case ID_OPTIONS_CHANGE_FR:
		switch (g_Settings->LoadDword(UserInterface_FrameDisplayType))
		{
		case FR_VIs:
			g_Settings->SaveDword(UserInterface_FrameDisplayType,FR_DLs);
			break;
		case FR_DLs:
			g_Settings->SaveDword(UserInterface_FrameDisplayType,FR_PERCENT);
			break;
		default:
			g_Settings->SaveDword(UserInterface_FrameDisplayType,FR_VIs);
		}
		break;
	case ID_OPTIONS_INCREASE_SPEED:
		g_BaseSystem->IncreaseSpeed();
		break;
	case ID_OPTIONS_DECREASE_SPEED:
		g_BaseSystem->DecreaeSpeed();
		break;
	case ID_OPTIONS_FULLSCREEN:
		g_BaseSystem->ExternalEvent(SysEvent_ChangingFullScreen);		
		break;
	case ID_OPTIONS_FULLSCREEN2:  
		if (g_Settings->LoadBool(UserInterface_InFullScreen))
		{
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN a");
			_Gui->MakeWindowOnTop(false);
			Notify().SetGfxPlugin(NULL);
			WriteTrace(TraceGfxPlugin,__FUNCTION__ ": ChangeWindow: Starting");
			g_Plugins->Gfx()->ChangeWindow(); 
			WriteTrace(TraceGfxPlugin,__FUNCTION__ ": ChangeWindow: Done");
			ShowCursor(true);
			_Gui->ShowStatusBar(true);
			_Gui->MakeWindowOnTop(g_Settings->LoadBool(UserInterface_AlwaysOnTop));
			g_Settings->SaveBool(UserInterface_InFullScreen,(DWORD)false);
		} else {
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN b");
			ShowCursor(false);
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN b 1");
			_Gui->ShowStatusBar(false);
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN b 2");
			try {
				WriteTrace(TraceGfxPlugin,__FUNCTION__ ": ChangeWindow: Starting");
				g_Plugins->Gfx()->ChangeWindow(); 
				WriteTrace(TraceGfxPlugin,__FUNCTION__ ": ChangeWindow: Done");
			} 
			catch (...)
			{
				WriteTrace(TraceError,__FUNCTION__ ": Exception when going to full screen");
				char Message[600];
				sprintf(Message,"Exception caught\nFile: %s\nLine: %d",__FILE__,__LINE__);
				MessageBox(NULL,Message,"Exception",MB_OK);
			}
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN b 4");
			_Gui->MakeWindowOnTop(false);
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN b 5");
			Notify().SetGfxPlugin(g_Plugins->Gfx());
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN b 3");
			g_Settings->SaveBool(UserInterface_InFullScreen,true);
			WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN b 6");
		}
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_FULLSCREEN 1");
		break;
	case ID_OPTIONS_ALWAYSONTOP:
		if (g_Settings->LoadDword(UserInterface_AlwaysOnTop)) {
			g_Settings->SaveBool(UserInterface_AlwaysOnTop,false);
			_Gui->MakeWindowOnTop(false);
		} else {
			g_Settings->SaveBool(UserInterface_AlwaysOnTop,true);
			_Gui->MakeWindowOnTop(g_Settings->LoadBool(GameRunning_CPU_Running));
		}
		break;
	case ID_OPTIONS_CONFIG_RSP:  WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_CONFIG_RSP"); g_Plugins->ConfigPlugin((DWORD)hWnd,PLUGIN_TYPE_RSP); break;
	case ID_OPTIONS_CONFIG_GFX:  WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_CONFIG_GFX"); g_Plugins->ConfigPlugin((DWORD)hWnd,PLUGIN_TYPE_GFX); break;
	case ID_OPTIONS_CONFIG_AUDIO:WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_CONFIG_AUDIO"); g_Plugins->ConfigPlugin((DWORD)hWnd,PLUGIN_TYPE_AUDIO); break;
	case ID_OPTIONS_CONFIG_CONT: WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_CONFIG_CONT"); g_Plugins->ConfigPlugin((DWORD)hWnd,PLUGIN_TYPE_CONTROLLER); break;
	case ID_OPTIONS_CPU_USAGE:
		WriteTrace(TraceDebug,__FUNCTION__ ": ID_OPTIONS_CPU_USAGE");
		if (g_Settings->LoadBool(UserInterface_ShowCPUPer)) 
		{
			g_Settings->SaveBool(UserInterface_ShowCPUPer,false);
			g_Notify->DisplayMessage(0,L"");
		} else {
			g_Settings->SaveBool(UserInterface_ShowCPUPer,true);
		}
		break;
	case ID_OPTIONS_SETTINGS:
		{
			CSettingConfig SettingConfig;
			SettingConfig.Display(hWnd);
		}
		break;
	case ID_PROFILE_PROFILE:
		g_Settings->SaveBool(Debugger_ProfileCode,!g_Settings->LoadBool(Debugger_ProfileCode));
		g_BaseSystem->ExternalEvent(SysEvent_Profile_StartStop);
		break;
	case ID_PROFILE_RESETCOUNTER: g_BaseSystem->ExternalEvent(SysEvent_Profile_ResetLogs); break;
	case ID_PROFILE_GENERATELOG: g_BaseSystem->ExternalEvent(SysEvent_Profile_GenerateLogs); break;
	case ID_DEBUG_SHOW_TLB_MISSES: 
		g_Settings->SaveBool(Debugger_ShowTLBMisses,!g_Settings->LoadBool(Debugger_ShowTLBMisses));
		break;
	case ID_DEBUG_SHOW_UNHANDLED_MEM: 
		g_Settings->SaveBool(Debugger_ShowUnhandledMemory,!g_Settings->LoadBool(Debugger_ShowUnhandledMemory));
		break;
	case ID_DEBUG_SHOW_PIF_ERRORS: 
		g_Settings->SaveBool(Debugger_ShowPifErrors,!g_Settings->LoadBool(Debugger_ShowPifErrors));
		break;
	case ID_DEBUG_SHOW_DLIST_COUNT:
		g_Notify->DisplayMessage(0,L"");
		g_Settings->SaveBool(Debugger_ShowDListAListCount,!g_Settings->LoadBool(Debugger_ShowDListAListCount));
		break;
	case ID_DEBUG_SHOW_RECOMP_MEM_SIZE:
		g_Notify->DisplayMessage(0,L"");
		g_Settings->SaveBool(Debugger_ShowRecompMemSize,!g_Settings->LoadBool(Debugger_ShowRecompMemSize));
		break;
	case ID_DEBUG_SHOW_DIV_BY_ZERO:
		g_Settings->SaveBool(Debugger_ShowDivByZero,!g_Settings->LoadBool(Debugger_ShowDivByZero));
		break;
	case ID_DEBUG_GENERATE_LOG_FILES:
		g_Settings->SaveBool(Debugger_GenerateLogFiles,!g_Settings->LoadBool(Debugger_GenerateLogFiles));
		break;
	case ID_DEBUG_DISABLE_GAMEFIX:
		g_Settings->SaveBool(Debugger_DisableGameFixes,!g_Settings->LoadBool(Debugger_DisableGameFixes));
		break;
	case ID_DEBUGGER_APPLOG_ERRORS:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceError) != 0)
			{
				LogLevel &= ~TraceError;
			} else {
				LogLevel |= TraceError;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_SETTINGS:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceSettings) != 0)
			{
				LogLevel &= ~TraceSettings;
			} else {

				LogLevel |= TraceSettings;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_RECOMPILER:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceRecompiler) != 0)
			{
				LogLevel &= ~TraceRecompiler;
			} else {

				LogLevel |= TraceRecompiler;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_RSP:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceRSP) != 0)
			{
				LogLevel &= ~TraceRSP;
			} else {

				LogLevel |= TraceRSP;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_TLB:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceTLB) != 0)
			{
				LogLevel &= ~TraceTLB;
			} else {

				LogLevel |= TraceTLB;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_GFX_PLUGIN:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceGfxPlugin) != 0)
			{
				LogLevel &= ~TraceGfxPlugin;
			} else {

				LogLevel |= TraceGfxPlugin;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_DEBUG:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceDebug) != 0)
			{
				LogLevel &= ~TraceDebug;
			} else {

				LogLevel |= TraceDebug;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_AUDIO_EMU:
		{
			DWORD LogLevel = g_Settings->LoadDword(Debugger_AppLogLevel);
			if ((LogLevel & TraceAudio) != 0)
			{
				LogLevel &= ~TraceAudio;
			} else {

				LogLevel |= TraceAudio;
			}
			g_Settings->SaveDword(Debugger_AppLogLevel, LogLevel );
		}
		break;
	case ID_DEBUGGER_APPLOG_FLUSH:
		g_Settings->SaveBool(Debugger_AppLogFlush,!g_Settings->LoadBool(Debugger_AppLogFlush));
		break;
	case ID_DEBUGGER_LOGOPTIONS: _Gui->EnterLogOptions(); break;
	case ID_DEBUGGER_GENERATELOG:
		g_Settings->SaveBool(Debugger_GenerateDebugLog,!g_Settings->LoadBool(Debugger_GenerateDebugLog));
		break;
	case ID_DEBUGGER_DUMPMEMORY: 
		g_BaseSystem->Debug_ShowMemoryDump();
		break;
	case ID_DEBUGGER_SEARCHMEMORY: g_BaseSystem->Debug_ShowMemorySearch(); break;
	case ID_DEBUGGER_MEMORY: g_BaseSystem->Debug_ShowMemoryWindow(); break;
	case ID_DEBUGGER_TLBENTRIES: g_BaseSystem->Debug_ShowTLBWindow(); break;
	case ID_DEBUGGER_INTERRUPT_SP: g_BaseSystem->ExternalEvent(SysEvent_Interrupt_SP); break;
	case ID_DEBUGGER_INTERRUPT_SI: g_BaseSystem->ExternalEvent(SysEvent_Interrupt_SI); break;
	case ID_DEBUGGER_INTERRUPT_AI: g_BaseSystem->ExternalEvent(SysEvent_Interrupt_AI); break;
	case ID_DEBUGGER_INTERRUPT_VI: g_BaseSystem->ExternalEvent(SysEvent_Interrupt_VI); break;
	case ID_DEBUGGER_INTERRUPT_PI: g_BaseSystem->ExternalEvent(SysEvent_Interrupt_PI); break;
	case ID_DEBUGGER_INTERRUPT_DP: g_BaseSystem->ExternalEvent(SysEvent_Interrupt_DP); break;
	case ID_CURRENT_SAVE_DEFAULT: 
		Notify().DisplayMessage(3,L"Save Slot (%s) selected",GetSaveSlotString(MenuID - ID_CURRENT_SAVE_DEFAULT).c_str());
		g_Settings->SaveDword(Game_CurrentSaveState,(DWORD)(MenuID - ID_CURRENT_SAVE_DEFAULT)); 
		break;
	case ID_CURRENT_SAVE_1: 
	case ID_CURRENT_SAVE_2: 
	case ID_CURRENT_SAVE_3: 
	case ID_CURRENT_SAVE_4: 
	case ID_CURRENT_SAVE_5: 
	case ID_CURRENT_SAVE_6: 
	case ID_CURRENT_SAVE_7: 
	case ID_CURRENT_SAVE_8: 
	case ID_CURRENT_SAVE_9: 
	case ID_CURRENT_SAVE_10: 
		Notify().DisplayMessage(3,L"Save Slot (%s) selected",GetSaveSlotString((MenuID - ID_CURRENT_SAVE_1) + 1).c_str());
		g_Settings->SaveDword(Game_CurrentSaveState,(DWORD)((MenuID - ID_CURRENT_SAVE_1) + 1)); 
		break;
	case ID_HELP_SUPPORTFORUM: ShellExecute(NULL, "open", "http://forum.pj64-emu.com/", NULL, NULL, SW_SHOWMAXIMIZED); break;
	case ID_HELP_HOMEPAGE: ShellExecute(NULL, "open", "http://www.pj64-emu.com", NULL, NULL, SW_SHOWMAXIMIZED); break;
	case ID_HELP_ABOUT: _Gui->AboutBox(); break;
	case ID_HELP_ABOUTSETTINGFILES: _Gui->AboutIniBox(); break;
	default: 
		if (MenuID >= ID_RECENT_ROM_START && MenuID < ID_RECENT_ROM_END) {
			stdstr FileName;
			if (g_Settings->LoadStringIndex(File_RecentGameFileIndex,MenuID - ID_RECENT_ROM_START,FileName) && 
				FileName.length() > 0) 
			{
				g_BaseSystem->RunFileImage(FileName.c_str());
			}
		}
		if (MenuID >= ID_RECENT_DIR_START && MenuID < ID_RECENT_DIR_END) {
			int Offset = MenuID - ID_RECENT_DIR_START;
			stdstr Dir = g_Settings->LoadStringIndex(Directory_RecentGameDirIndex,Offset);
			if (Dir.length() > 0) {
				g_Settings->SaveString(Directory_Game,Dir.c_str());
				g_Notify->AddRecentDir(Dir.c_str());
				_Gui->RefreshMenu();
				if (_Gui->RomBrowserVisible()) {
					_Gui->RefreshRomBrowser();
				}
			}
		}
		if (MenuID >= ID_LANG_START && MenuID < ID_LANG_END) {
			MENUITEMINFOW menuinfo;
			wchar_t String[300];

			menuinfo.cbSize = sizeof(MENUITEMINFO);
			menuinfo.fMask = MIIM_TYPE;
			menuinfo.fType = MFT_STRING;
			menuinfo.dwTypeData = String;
			menuinfo.cch = sizeof(String);
			GetMenuItemInfoW((HMENU)m_MenuHandle,MenuID,FALSE,&menuinfo);
			
			//See if the language has changed, if not do nothing
			//Set the language
			g_Lang->SetLanguage(String);
			_Gui->ResetRomBrowserColomuns();
			break;
		}
		return false;
	}
	return true;
}