	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		int wmId, wmEvent;
		std::string fn;

		switch (message) 
		{
		case WM_CREATE:
			break;

		case WM_MOVE:
			SavePosition();
			ResizeDisplay();
			break;

		case WM_SIZE:
			SavePosition();
			ResizeDisplay();
			break;

		case WM_TIMER:
			// Hack: Take the opportunity to also show/hide the mouse cursor in fullscreen mode.
			switch (wParam)
			{
			case TIMER_CURSORUPDATE:
				CorrectCursor();
				return 0;
			case TIMER_CURSORMOVEUPDATE:
				hideCursor = true;
				KillTimer(hWnd, TIMER_CURSORMOVEUPDATE);
				return 0;
			}
			break;

		// For some reason, need to catch this here rather than in DisplayProc.
		case WM_MOUSEWHEEL:
			{
				int wheelDelta = (short)(wParam >> 16);
				KeyInput key;
				key.deviceId = DEVICE_ID_MOUSE;

				if (wheelDelta < 0) {
					key.keyCode = KEYCODE_EXT_MOUSEWHEEL_DOWN;
					wheelDelta = -wheelDelta;
				} else {
					key.keyCode = KEYCODE_EXT_MOUSEWHEEL_UP;
				}
				// There's no separate keyup event for mousewheel events, let's pass them both together.
				// This also means it really won't work great for key mapping :( Need to build a 1 frame delay or something.
				key.flags = KEY_DOWN | KEY_UP | KEY_HASWHEELDELTA | (wheelDelta << 16);
				NativeKey(key);
				break;
			}

		case WM_COMMAND:
			{
			if (!EmuThread_Ready())
				return DefWindowProc(hWnd, message, wParam, lParam);
			I18NCategory *g = GetI18NCategory("Graphics");

			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_FILE_LOAD:
				BrowseAndBoot("");
				break;

			case ID_FILE_LOAD_MEMSTICK:
				{
					std::string memStickDir, flash0dir;
					GetSysDirectories(memStickDir, flash0dir);
					memStickDir += "PSP\\GAME\\";
					BrowseAndBoot(memStickDir);
				}
				break;

			case ID_FILE_REFRESHGAMELIST:
				break;

			case ID_FILE_MEMSTICK:
				{
					std::string memStickDir, flash0dir;
					GetSysDirectories(memStickDir, flash0dir);
					ShellExecuteA(NULL, "open", memStickDir.c_str(), 0, 0, SW_SHOW);
				}
				break;

			case ID_TOGGLE_PAUSE:
				if (globalUIState == UISTATE_PAUSEMENU)
				{
					NativeMessageReceived("run", "");
					if (disasmWindow[0])
						SendMessage(disasmWindow[0]->GetDlgHandle(), WM_COMMAND, IDC_GO, 0);
				}
				else if (Core_IsStepping()) //It is paused, then continue to run
				{
					if (disasmWindow[0])
						SendMessage(disasmWindow[0]->GetDlgHandle(), WM_COMMAND, IDC_GO, 0);
					else
						Core_EnableStepping(false);
				} else {
					if (disasmWindow[0])
						SendMessage(disasmWindow[0]->GetDlgHandle(), WM_COMMAND, IDC_STOP, 0);
					else
						Core_EnableStepping(true);
				}
				break;

			case ID_EMULATION_STOP:
				if (memoryWindow[0]) {
					SendMessage(memoryWindow[0]->GetDlgHandle(), WM_CLOSE, 0, 0);
				}
				if (disasmWindow[0]) {
					SendMessage(disasmWindow[0]->GetDlgHandle(), WM_CLOSE, 0, 0);
				}
				if (Core_IsStepping()) {
					Core_EnableStepping(false);
				}
				NativeMessageReceived("stop", "");
				SetPlaying(0);
				Update();
				break;

			case ID_EMULATION_RESET:
				if (globalUIState == UISTATE_PAUSEMENU)
					NativeMessageReceived("run", "");
				NativeMessageReceived("reset", "");
				break;

			case ID_EMULATION_SPEEDLIMIT:
				g_Config.bSpeedLimit = !g_Config.bSpeedLimit;
				break;

			case ID_FILE_LOADSTATEFILE:
				if (W32Util::BrowseForFileName(true, hWnd, "Load state",0,"Save States (*.ppst)\0*.ppst\0All files\0*.*\0\0","ppst",fn))
				{
					SetCursor(LoadCursor(0, IDC_WAIT));
					SaveState::Load(fn, SaveStateActionFinished);
				}
				break;

			case ID_FILE_SAVESTATEFILE:
				if (W32Util::BrowseForFileName(false, hWnd, "Save state",0,"Save States (*.ppst)\0*.ppst\0All files\0*.*\0\0","ppst",fn))
				{
					SetCursor(LoadCursor(0, IDC_WAIT));
					SaveState::Save(fn, SaveStateActionFinished);
				}
				break;

			// TODO: Improve UI for multiple slots
			case ID_FILE_SAVESTATE_NEXT_SLOT:
			{
				currentSavestateSlot = (currentSavestateSlot + 1)%5;
				char msg[30];
				sprintf(msg, "Using save state slot %d.", currentSavestateSlot + 1);
				osm.Show(msg);
				break;
			}

			case ID_FILE_QUICKLOADSTATE:
				SetCursor(LoadCursor(0, IDC_WAIT));
				SaveState::LoadSlot(currentSavestateSlot, SaveStateActionFinished);
				break;

			case ID_FILE_QUICKSAVESTATE:
				SetCursor(LoadCursor(0, IDC_WAIT));
				SaveState::SaveSlot(currentSavestateSlot, SaveStateActionFinished);
				break;

			case ID_OPTIONS_SCREEN1X:
				SetZoom(1);
				break;
			case ID_OPTIONS_SCREEN2X:
				SetZoom(2);
				break;
			case ID_OPTIONS_SCREEN3X:
				SetZoom(3);
				break;
			case ID_OPTIONS_SCREEN4X:
				SetZoom(4);
				break;

			case ID_OPTIONS_MIPMAP:
				g_Config.bMipMap = !g_Config.bMipMap;
				break;

			case ID_OPTIONS_VSYNC:
				g_Config.iVSyncInterval = !g_Config.iVSyncInterval;
				break;

			case ID_TEXTURESCALING_OFF:
				setTexScalingLevel(1);
				break;
			case ID_TEXTURESCALING_2X:
				setTexScalingLevel(2);
				break;
			case ID_TEXTURESCALING_3X:
				setTexScalingLevel(3);
				break;
			case ID_TEXTURESCALING_4X:
				setTexScalingLevel(4);
				break;
			case ID_TEXTURESCALING_5X:
				setTexScalingLevel(5);
				break;

			case ID_TEXTURESCALING_XBRZ:
				setTexScalingType(TextureScaler::XBRZ);
				break;
			case ID_TEXTURESCALING_HYBRID:
				setTexScalingType(TextureScaler::HYBRID);
				break;
			case ID_TEXTURESCALING_BICUBIC:
				setTexScalingType(TextureScaler::BICUBIC);
				break;
			case ID_TEXTURESCALING_HYBRID_BICUBIC:
				setTexScalingType(TextureScaler::HYBRID_BICUBIC);
				break;

			case ID_TEXTURESCALING_DEPOSTERIZE:
				g_Config.bTexDeposterize = !g_Config.bTexDeposterize;
				if(gpu) gpu->ClearCacheNextFrame();
				break;

			case ID_OPTIONS_BUFFEREDRENDERING:
				g_Config.bBufferedRendering = !g_Config.bBufferedRendering;
				osm.ShowOnOff(g->T("Buffered Rendering"), g_Config.bBufferedRendering);
				if (gpu)
					gpu->Resized();  // easy way to force a clear...
				break;

			case ID_OPTIONS_READFBOTOMEMORY:
				g_Config.bFramebuffersToMem = !g_Config.bFramebuffersToMem;
				osm.ShowOnOff(g->T("Read Framebuffers To Memory"), g_Config.bFramebuffersToMem);
				if (gpu)
					gpu->Resized();  // easy way to force a clear...
				break;

			case ID_OPTIONS_SHOWDEBUGSTATISTICS:
				g_Config.bShowDebugStats = !g_Config.bShowDebugStats;
				break;

			case ID_OPTIONS_HARDWARETRANSFORM:
				g_Config.bHardwareTransform = !g_Config.bHardwareTransform;
				osm.ShowOnOff(g->T("Hardware Transform"), g_Config.bHardwareTransform);
				break;

			case ID_OPTIONS_STRETCHDISPLAY:
				g_Config.bStretchToDisplay = !g_Config.bStretchToDisplay;
				if (gpu)
					gpu->Resized();  // easy way to force a clear...
				break;

			case ID_OPTIONS_FRAMESKIP:
				g_Config.iFrameSkip = g_Config.iFrameSkip == 0 ? 1 : 0;
				osm.ShowOnOff(g->T("Frame Skipping"), g_Config.iFrameSkip != 0);
				break;

			case ID_FILE_EXIT:
				DestroyWindow(hWnd);
				break;

			case ID_CPU_DYNAREC:
				g_Config.bJit = true;
				osm.ShowOnOff(g->T("Dynarec", "Dynarec (JIT)"), g_Config.bJit);
				break;	

			case ID_CPU_INTERPRETER:
				g_Config.bJit = false;
				break;

			case ID_EMULATION_RUNONLOAD:
				g_Config.bAutoRun = !g_Config.bAutoRun;
				break;

			case ID_DEBUG_DUMPNEXTFRAME:
				if (gpu)
					gpu->DumpNextFrame();
				break;

			case ID_DEBUG_LOADMAPFILE:
				if (W32Util::BrowseForFileName(true, hWnd, "Load .MAP",0,"Maps\0*.map\0All files\0*.*\0\0","map",fn)) {
					symbolMap.LoadSymbolMap(fn.c_str());
//					HLE_PatchFunctions();
					if (disasmWindow[0])
						disasmWindow[0]->NotifyMapLoaded();
					if (memoryWindow[0])
						memoryWindow[0]->NotifyMapLoaded();
				}
				break;
			case ID_DEBUG_SAVEMAPFILE:
				if (W32Util::BrowseForFileName(false, hWnd, "Save .MAP",0,"Maps\0*.map\0All files\0*.*\0\0","map",fn))
					symbolMap.SaveSymbolMap(fn.c_str());
				break;
		
			case ID_DEBUG_RESETSYMBOLTABLE:
				symbolMap.ResetSymbolMap();
				for (int i=0; i<numCPUs; i++)
					if (disasmWindow[i])
						disasmWindow[i]->NotifyMapLoaded();
				for (int i=0; i<numCPUs; i++)
					if (memoryWindow[i])
						memoryWindow[i]->NotifyMapLoaded();
				break;
			case ID_DEBUG_DISASSEMBLY:
				if (disasmWindow[0])
					disasmWindow[0]->Show(true);
				break;
			case ID_DEBUG_MEMORYVIEW:
				if (memoryWindow[0])
					memoryWindow[0]->Show(true);
				break;
			case ID_DEBUG_LOG:
				LogManager::GetInstance()->GetConsoleListener()->Show(LogManager::GetInstance()->GetConsoleListener()->Hidden());
				break;

			case ID_OPTIONS_IGNOREILLEGALREADS:
				g_Config.bIgnoreBadMemAccess = !g_Config.bIgnoreBadMemAccess;
				break;

			case ID_OPTIONS_FULLSCREEN:
				g_Config.bFullScreen = !g_Config.bFullScreen ;
				if(g_bFullScreen) {
					_ViewNormal(hWnd); 
				} else {
					_ViewFullScreen(hWnd);
				}
				break;

			case ID_OPTIONS_VERTEXCACHE:
				g_Config.bVertexCache = !g_Config.bVertexCache;
				break;
			case ID_OPTIONS_SHOWFPS:
				g_Config.iShowFPSCounter = !g_Config.iShowFPSCounter;
				break;
			case ID_OPTIONS_DISPLAYRAWFRAMEBUFFER:
				g_Config.bDisplayFramebuffer = !g_Config.bDisplayFramebuffer;
				break;
			case ID_OPTIONS_FASTMEMORY:
				g_Config.bFastMemory = !g_Config.bFastMemory;
				break;
			case ID_OPTIONS_USEVBO:
				g_Config.bUseVBO = !g_Config.bUseVBO;
				break;
			case ID_OPTIONS_TEXTUREFILTERING_AUTO:
				setTexFiltering(0);
				break;
			case ID_OPTIONS_NEARESTFILTERING:
				setTexFiltering(2) ;
				break;
			case ID_OPTIONS_LINEARFILTERING:
				setTexFiltering(3) ;
				break;
			case ID_OPTIONS_LINEARFILTERING_CG:
				setTexFiltering(4) ;
				break;
			case ID_OPTIONS_TOPMOST:
				g_Config.bTopMost = !g_Config.bTopMost;
				W32Util::MakeTopMost(hWnd, g_Config.bTopMost);
				break;

			case ID_OPTIONS_SIMPLE2XSSAA:
				g_Config.SSAntiAliasing = !g_Config.SSAntiAliasing;
				ResizeDisplay(true);
				break;
			case ID_OPTIONS_CONTROLS:
				MessageBox(hWnd, "Control mapping has been moved to the in-window Settings menu.\n", "Sorry", 0);
				break;

			case ID_EMULATION_SOUND:
				g_Config.bEnableSound = !g_Config.bEnableSound;
				break;

			case ID_HELP_OPENWEBSITE:
				ShellExecute(NULL, "open", "http://www.ppsspp.org/", NULL, NULL, SW_SHOWNORMAL);
				break;

			case ID_HELP_OPENFORUM:
				ShellExecute(NULL, "open", "http://forums.ppsspp.org/", NULL, NULL, SW_SHOWNORMAL);
				break;

			case ID_HELP_ABOUT:
				DialogManager::EnableAll(FALSE);
				DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				DialogManager::EnableAll(TRUE);
				break;
			case ID_DEBUG_TAKESCREENSHOT:
				g_TakeScreenshot = true;
				break;

			default:
				MessageBox(hwndMain,"Unimplemented","Sorry",0);
				break;
			}
			}
			break;

		case WM_INPUT:
			{
				UINT dwSize;
				GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
				if (!rawInputBuffer) {
					rawInputBuffer = malloc(dwSize);
					rawInputBufferSize = dwSize;
				}
				if (dwSize > rawInputBufferSize) {
					rawInputBuffer = realloc(rawInputBuffer, dwSize);
				}
				GetRawInputData((HRAWINPUT)lParam, RID_INPUT, rawInputBuffer, &dwSize, sizeof(RAWINPUTHEADER));
				RAWINPUT* raw = (RAWINPUT*)rawInputBuffer;

				if (raw->header.dwType == RIM_TYPEKEYBOARD) {
					KeyInput key;
					key.deviceId = DEVICE_ID_KEYBOARD;
					if (raw->data.keyboard.Message == WM_KEYDOWN || raw->data.keyboard.Message == WM_SYSKEYDOWN) {
						key.flags = KEY_DOWN;
						key.keyCode = windowsTransTable[GetTrueVKey(raw->data.keyboard)];
						if (key.keyCode) {
							NativeKey(key);
						}
					} else if (raw->data.keyboard.Message == WM_KEYUP) {
						key.flags = KEY_UP;
						key.keyCode = windowsTransTable[GetTrueVKey(raw->data.keyboard)];
						if (key.keyCode) {
							NativeKey(key);	
						}
					}
				}
			}
			return 0;

		case WM_DROPFILES:
			{
				if (!EmuThread_Ready())
					return DefWindowProc(hWnd, message, wParam, lParam);

				HDROP hdrop = (HDROP)wParam;
				int count = DragQueryFile(hdrop,0xFFFFFFFF,0,0);
				if (count != 1)
				{
					MessageBox(hwndMain,"You can only load one file at a time","Error",MB_ICONINFORMATION);
				}
				else
				{
					TCHAR filename[512];
					DragQueryFile(hdrop,0,filename,512);
					TCHAR *type = filename+_tcslen(filename)-3;

					SendMessage(hWnd, WM_COMMAND, ID_EMULATION_STOP, 0);
					// Ugly, need to wait for the stop message to process in the EmuThread.
					Sleep(20);
					
					MainWindow::SetPlaying(filename);
					MainWindow::Update();

					NativeMessageReceived("boot", filename);
				}
			}
			break;

		case WM_CLOSE:
			/*
			if (g_Config.bConfirmOnQuit && __KernelIsRunning())
				if (IDYES != MessageBox(hwndMain, "A game is in progress. Are you sure you want to exit?",
					"Are you sure?", MB_YESNO | MB_ICONQUESTION))
					return 0;
			//*/
			EmuThread_Stop();

			return DefWindowProc(hWnd,message,wParam,lParam);

		case WM_DESTROY:
			KillTimer(hWnd, TIMER_CURSORUPDATE);
			KillTimer(hWnd, TIMER_CURSORMOVEUPDATE);
			PostQuitMessage(0);
			break;

		case WM_USER+1:
			if (disasmWindow[0])
				SendMessage(disasmWindow[0]->GetDlgHandle(), WM_CLOSE, 0, 0);
			if (memoryWindow[0])
				SendMessage(memoryWindow[0]->GetDlgHandle(), WM_CLOSE, 0, 0);

			disasmWindow[0] = new CDisasm(MainWindow::GetHInstance(), MainWindow::GetHWND(), currentDebugMIPS);
			DialogManager::AddDlg(disasmWindow[0]);
			disasmWindow[0]->Show(g_Config.bShowDebuggerOnLoad);
			if (g_Config.bFullScreen)
				_ViewFullScreen(hWnd);
			memoryWindow[0] = new CMemoryDlg(MainWindow::GetHInstance(), MainWindow::GetHWND(), currentDebugMIPS);
			DialogManager::AddDlg(memoryWindow[0]);
			if (disasmWindow[0])
				disasmWindow[0]->NotifyMapLoaded();
			if (memoryWindow[0])
				memoryWindow[0]->NotifyMapLoaded();

			SetForegroundWindow(hwndMain);
			break;


		case WM_MENUSELECT:
			// Unfortunately, accelerate keys (hotkeys) shares the same enabled/disabled states
			// with corresponding menu items.
			UpdateMenus();
			break;

		// Turn off the screensaver.
		// Note that if there's a screensaver password, this simple method
		// doesn't work on Vista or higher.
		case WM_SYSCOMMAND:
			{
				switch (wParam)
				{
				case SC_SCREENSAVE:  
					return 0;
				case SC_MONITORPOWER:
					return 0;      
				}
				return DefWindowProc(hWnd, message, wParam, lParam);
			}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}