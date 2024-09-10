// Process window messages
LRESULT CALLBACK vncMenu::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// This is a static method, so we don't know which instantiation we're 
	// dealing with. We use Allen Hadden's ([email protected]) suggestion 
	// from a newsgroup to get the pseudo-this.
     vncMenu *_this = helper::SafeGetWindowUserData<vncMenu>(hwnd);
	//	Beep(100,10);
	//	vnclog.Print(LL_INTINFO, VNCLOG("iMsg 0x%x \n"),iMsg);

	 if (iMsg==WM_TASKBARCREATED)
	 {
		 if (_this->m_server->RunningFromExternalService())
			{
				Sleep(1000);
				vnclog.Print(LL_INTINFO,
				VNCLOG("WM_TASKBARCREATED \n"));
				// User has changed!
				strcpy(_this->m_username, newuser);
				vnclog.Print(LL_INTINFO,
				VNCLOG("############## Kill vncMenu thread\n"));
				// Order impersonation thread killing
				KillTimer(hwnd,1);
				PostQuitMessage(0);
			}
	 }

	switch (iMsg)
	{

	// Every five seconds, a timer message causes the icon to update
	case WM_TIMER:
		// sf@2007 - Can't get the WTS_CONSOLE_CONNECT message work properly for now..
		// So use a hack instead
        // jdp reread some ini settings
        _this->m_properties.ReloadDynamicSettings();

		// G_1111==true --> reconnect
		if (G_1111==true)
		{
			if (_this->IsIconSet==true)
			{
				vnclog.Print(LL_INTERR, VNCLOG("Add client reconnect from timer\n"));
				G_1111=false;
				PostMessage(hwnd,MENU_ADD_CLIENT_MSG,1111,1111);
			}
		}


		vnclog.Print(LL_INTERR, VNCLOG("########### vncMenu::TIMER TrayIcon 5s hack\n"));

		if (_this->m_server->RunningFromExternalService())
			{
				strcpy(newuser,"");
				if (vncService::CurrentUser((char *) &newuser, sizeof(newuser)))
				{
					// Check whether the user name has changed!
					if (_stricmp(newuser, _this->m_username) != 0 || _this->IconFaultCounter>2)
					{
						Sleep(1000);
						vnclog.Print(LL_INTINFO,
						VNCLOG("user name has changed\n"));
						// User has changed!
						strcpy(_this->m_username, newuser);
						vnclog.Print(LL_INTINFO,
						VNCLOG("############## Kill vncMenu thread\n"));
						// Order impersonation thread killing
						PostQuitMessage(0);
						break;
					}
				}
			}

		// *** HACK for running servicified
		if (vncService::RunningAsService())
			{
				vnclog.Print(LL_INTERR, VNCLOG("########### vncMenu::TIMER TrayIcon 5s hack call - Runningasservice\n"));
				// Attempt to add the icon if it's not already there
				_this->AddTrayIcon();
				// Trigger a check of the current user
				PostMessage(hwnd, WM_USERCHANGED, 0, 0);
			}
		// Update the icon
		_this->FlashTrayIcon(_this->m_server->AuthClientCount() != 0);
		break;

		// DEAL WITH NOTIFICATIONS FROM THE SERVER:
	case WM_SRV_CLIENT_AUTHENTICATED:
	case WM_SRV_CLIENT_DISCONNECT:
		// Adjust the icon accordingly
		_this->FlashTrayIcon(_this->m_server->AuthClientCount() != 0);

		if (_this->m_server->AuthClientCount() != 0) {
			if (_this->m_server->RemoveWallpaperEnabled())
				KillWallpaper();
			if (_this->m_server->RemoveAeroEnabled()) // Moved, redundant if //PGM @ Advantig
				DisableAero(); // Moved, redundant if //PGM @ Advantig
		} else {
			if (_this->m_server->RemoveAeroEnabled()) // Moved, redundant if //PGM @ Advantig
				ResetAero(); // Moved, redundant if //PGM @ Advantig
			if (_this->m_server->RemoveWallpaperEnabled()) { // Added { //PGM @ Advantig
				Sleep(2000); // Added 2 second delay to help wallpaper restore //PGM @ Advantig
				RestoreWallpaper();
			} //PGM @ Advantig
		}
//PGM @ Advantig		if (_this->m_server->AuthClientCount() != 0) {
//PGM @ Advantig			if (_this->m_server->RemoveAeroEnabled())
//PGM @ Advantig				DisableAero();
//PGM @ Advantig		} else {
//PGM @ Advantig			if (_this->m_server->RemoveAeroEnabled())
//PGM @ Advantig				ResetAero();
//PGM @ Advantig		}
		return 0;

		// STANDARD MESSAGE HANDLING
	case WM_CREATE:
		WM_TASKBARCREATED = RegisterWindowMessage("TaskbarCreated");
		return 0;

	case WM_COMMAND:
		// User has clicked an item on the tray menu
		switch (LOWORD(wParam))
		{
		case ID_DEFAULT_PROPERTIES:
			// Show the default properties dialog, unless it is already displayed
			vnclog.Print(LL_INTINFO, VNCLOG("show default properties requested\n"));
			_this->m_properties.ShowAdmin(TRUE, FALSE);
			_this->FlashTrayIcon(_this->m_server->AuthClientCount() != 0);
			break;
		
		case ID_PROPERTIES:
			// Show the properties dialog, unless it is already displayed
			vnclog.Print(LL_INTINFO, VNCLOG("show user properties requested\n"));
			_this->m_propertiesPoll.Show(TRUE, TRUE);
			_this->FlashTrayIcon(_this->m_server->AuthClientCount() != 0);
			break;

        case ID_ADMIN_PROPERTIES:
			// Show the properties dialog, unless it is already displayed
			vnclog.Print(LL_INTINFO, VNCLOG("show user properties requested\n"));
			_this->m_properties.ShowAdmin(TRUE, TRUE);
			_this->FlashTrayIcon(_this->m_server->AuthClientCount() != 0);
			break;
		
		case ID_OUTGOING_CONN:
			// Connect out to a listening VNC viewer
			{
				vncConnDialog *newconn = new vncConnDialog(_this->m_server);
				if (newconn)
				{
					newconn->DoDialog();
					// delete newconn; // NO ! Already done in vncConnDialog.
				}
			}
			break;

		case ID_KILLCLIENTS:
			// Disconnect all currently connected clients
			vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() ID_KILLCLIENTS \n"));
			_this->m_server->KillAuthClients();
			break;

		// sf@2002
		case ID_LISTCLIENTS:
			_this->m_ListDlg.Display();
			break;

		case ID_ABOUT:
			// Show the About box
			_this->m_about.Show(TRUE);
			break;

		case ID_VISITUSONLINE_HOMEPAGE:
			{
						HANDLE hProcess,hPToken;
						DWORD id=GetExplorerLogonPid();
						if (id!=0) 
						{
							hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
							if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
													|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
													|TOKEN_READ|TOKEN_WRITE,&hPToken)) break;

							char dir[MAX_PATH];
							char exe_file_name[MAX_PATH];
							GetModuleFileName(0, exe_file_name, MAX_PATH);
							strcpy(dir, exe_file_name);
							strcat(dir, " -openhomepage");
				
							{
								STARTUPINFO          StartUPInfo;
								PROCESS_INFORMATION  ProcessInfo;
								ZeroMemory(&StartUPInfo,sizeof(STARTUPINFO));
								ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
								StartUPInfo.wShowWindow = SW_SHOW;
								StartUPInfo.lpDesktop = "Winsta0\\Default";
								StartUPInfo.cb = sizeof(STARTUPINFO);
						
								CreateProcessAsUser(hPToken,NULL,dir,NULL,NULL,FALSE,DETACHED_PROCESS,NULL,NULL,&StartUPInfo,&ProcessInfo);
								DWORD error=GetLastError();
                                if (ProcessInfo.hThread) CloseHandle(ProcessInfo.hThread);
                                if (ProcessInfo.hProcess) CloseHandle(ProcessInfo.hProcess);
								//if (error==1314)
								//	{
								//		Open_homepage();
								//	}

							}
						}
			}
			break;

		case ID_VISITUSONLINE_FORUM:
			{
						HANDLE hProcess,hPToken;
						DWORD id=GetExplorerLogonPid();
						if (id!=0) 
						{
							hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
							if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
													|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
													|TOKEN_READ|TOKEN_WRITE,&hPToken)) break;

							char dir[MAX_PATH];
							char exe_file_name[MAX_PATH];
							GetModuleFileName(0, exe_file_name, MAX_PATH);
							strcpy(dir, exe_file_name);
							strcat(dir, " -openforum");
				
							{
								STARTUPINFO          StartUPInfo;
								PROCESS_INFORMATION  ProcessInfo;
								ZeroMemory(&StartUPInfo,sizeof(STARTUPINFO));
								ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
								StartUPInfo.wShowWindow = SW_SHOW;
								StartUPInfo.lpDesktop = "Winsta0\\Default";
								StartUPInfo.cb = sizeof(STARTUPINFO);
						
								CreateProcessAsUser(hPToken,NULL,dir,NULL,NULL,FALSE,DETACHED_PROCESS,NULL,NULL,&StartUPInfo,&ProcessInfo);
								DWORD error=GetLastError();
                                if (ProcessInfo.hThread) CloseHandle(ProcessInfo.hThread);
                                if (ProcessInfo.hProcess) CloseHandle(ProcessInfo.hProcess);
								//if (error==1314)
								//	{
								//		Open_forum();
								//	}

							}
						}
			}
			break;

		case ID_CLOSE:
			// User selected Close from the tray menu
			fShutdownOrdered=TRUE;
			Sleep(1000);
			vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() ID_CLOSE \n"));
			_this->m_server->KillAuthClients();
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case ID_UNINSTALL_SERVICE:
			{
			HANDLE hProcess,hPToken;
			DWORD id=GetExplorerLogonPid();
				if (id!=0) 
				{
					hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
					if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
											|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
											|TOKEN_READ|TOKEN_WRITE,&hPToken)) break;

					char dir[MAX_PATH];
					char exe_file_name[MAX_PATH];
					GetModuleFileName(0, exe_file_name, MAX_PATH);
					strcpy(dir, exe_file_name);
					strcat(dir, " -uninstallhelper");
		
					{
					STARTUPINFO          StartUPInfo;
					PROCESS_INFORMATION  ProcessInfo;
					HANDLE Token=NULL;
					HANDLE process=NULL;
					ZeroMemory(&StartUPInfo,sizeof(STARTUPINFO));
					ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
					StartUPInfo.wShowWindow = SW_SHOW;
					StartUPInfo.lpDesktop = "Winsta0\\Default";
					StartUPInfo.cb = sizeof(STARTUPINFO);
			
					CreateProcessAsUser(hPToken,NULL,dir,NULL,NULL,FALSE,DETACHED_PROCESS,NULL,NULL,&StartUPInfo,&ProcessInfo);
					DWORD errorcode=GetLastError();
					if (process) CloseHandle(process);
					if (Token) CloseHandle(Token);
					if (errorcode==1314)
					{
						Set_uninstall_service_as_admin();
					}

					}
					fShutdownOrdered=TRUE;
					vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() ID_CLOSE \n"));
					_this->m_server->KillAuthClients();					
					PostMessage(hwnd, WM_CLOSE, 0, 0);
				}
			}
			break;
		case ID_RUNASSERVICE:
			{
			HANDLE hProcess,hPToken;
			DWORD id=GetExplorerLogonPid();
				if (id!=0) 
				{
					hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
					if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
											|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
											|TOKEN_READ|TOKEN_WRITE,&hPToken)) break;

					char dir[MAX_PATH];
					char exe_file_name[MAX_PATH];
					GetModuleFileName(0, exe_file_name, MAX_PATH);
					strcpy(dir, exe_file_name);
					strcat(dir, " -installhelper");
		

					STARTUPINFO          StartUPInfo;
					PROCESS_INFORMATION  ProcessInfo;
					HANDLE Token=NULL;
					HANDLE process=NULL;
					ZeroMemory(&StartUPInfo,sizeof(STARTUPINFO));
					ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
					StartUPInfo.wShowWindow = SW_SHOW;
					StartUPInfo.lpDesktop = "Winsta0\\Default";
					StartUPInfo.cb = sizeof(STARTUPINFO);
			
					CreateProcessAsUser(hPToken,NULL,dir,NULL,NULL,FALSE,DETACHED_PROCESS,NULL,NULL,&StartUPInfo,&ProcessInfo);
					DWORD error=GetLastError();
					if (process) CloseHandle(process);
					if (Token) CloseHandle(Token);
					if (error==1314)
					{
						Set_install_service_as_admin();
					}
				}
			fShutdownOrdered=TRUE;
			Sleep(1000);
			vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() ID_CLOSE \n"));
			_this->m_server->KillAuthClients();
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			}
			break;
		case ID_CLOSE_SERVICE:
			{
			HANDLE hProcess,hPToken;
			DWORD id=GetExplorerLogonPid();
				if (id!=0) 
				{
					hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
					if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
											|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
											|TOKEN_READ|TOKEN_WRITE,&hPToken))
					{
						CloseHandle(hProcess);
						break;
					}

					char dir[MAX_PATH];
					char exe_file_name[MAX_PATH];
					GetModuleFileName(0, exe_file_name, MAX_PATH);
					strcpy(dir, exe_file_name);
					strcat(dir, " -stopservicehelper");
		

					STARTUPINFO          StartUPInfo;
					PROCESS_INFORMATION  ProcessInfo;
					HANDLE Token=NULL;
					HANDLE process=NULL;
					ZeroMemory(&StartUPInfo,sizeof(STARTUPINFO));
					ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
					StartUPInfo.wShowWindow = SW_SHOW;
					StartUPInfo.lpDesktop = "Winsta0\\Default";
					StartUPInfo.cb = sizeof(STARTUPINFO);
			
					CreateProcessAsUser(hPToken,NULL,dir,NULL,NULL,FALSE,DETACHED_PROCESS,NULL,NULL,&StartUPInfo,&ProcessInfo);
					DWORD error=GetLastError();
					if (process) CloseHandle(process);
					if (Token) CloseHandle(Token);
					if (hProcess) CloseHandle(hProcess);
					if (error==1314)
					{
						Set_stop_service_as_admin();
					}
				}
			}
			break;
		case ID_START_SERVICE:
			{
			HANDLE hProcess,hPToken;
			DWORD id=GetExplorerLogonPid();
				if (id!=0) 
				{
					hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
					if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
											|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
											|TOKEN_READ|TOKEN_WRITE,&hPToken))
					{
						CloseHandle(hProcess);
						break;
					}

					char dir[MAX_PATH];
					char exe_file_name[MAX_PATH];
					GetModuleFileName(0, exe_file_name, MAX_PATH);
					strcpy(dir, exe_file_name);
					strcat(dir, " -startservicehelper");
		

					STARTUPINFO          StartUPInfo;
					PROCESS_INFORMATION  ProcessInfo;
					HANDLE Token=NULL;
					HANDLE process=NULL;
					ZeroMemory(&StartUPInfo,sizeof(STARTUPINFO));
					ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
					StartUPInfo.wShowWindow = SW_SHOW;
					StartUPInfo.lpDesktop = "Winsta0\\Default";
					StartUPInfo.cb = sizeof(STARTUPINFO);
			
					CreateProcessAsUser(hPToken,NULL,dir,NULL,NULL,FALSE,DETACHED_PROCESS,NULL,NULL,&StartUPInfo,&ProcessInfo);
					DWORD error=GetLastError();
					if (hPToken) CloseHandle(hPToken);
					if (process) CloseHandle(process);
					if (Token) CloseHandle(Token);
					if (hProcess) CloseHandle(hProcess);
					if (error==1314)
					{
						Set_start_service_as_admin();
					}
					fShutdownOrdered=TRUE;
					Sleep(1000);
					vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() ID_CLOSE \n"));
					_this->m_server->KillAuthClients();
					PostMessage(hwnd, WM_CLOSE, 0, 0);
				}
			}
			break;

		}
		return 0;

	case WM_TRAYNOTIFY:
		// User has clicked on the tray icon or the menu
		{
			// Get the submenu to use as a pop-up menu
			HMENU submenu = GetSubMenu(_this->m_hmenu, 0);

			// What event are we responding to, RMB click?
			if (lParam==WM_RBUTTONUP)
			{
				if (submenu == NULL)
				{ 
					vnclog.Print(LL_INTERR, VNCLOG("no submenu available\n"));
					return 0;
				}

				// Make the first menu item the default (bold font)
				SetMenuDefaultItem(submenu, 0, TRUE);
				
				// Get the current cursor position, to display the menu at
				POINT mouse;
				GetCursorPos(&mouse);

				// There's a "bug"
				// (Microsoft calls it a feature) in Windows 95 that requires calling
				// SetForegroundWindow. To find out more, search for Q135788 in MSDN.
				//
				SetForegroundWindow(_this->m_nid.hWnd);

				// Display the menu at the desired position
				TrackPopupMenu(submenu,
						0, mouse.x, mouse.y, 0,
						_this->m_nid.hWnd, NULL);

                PostMessage(hwnd, WM_NULL, 0, 0);

				return 0;
			}
			
			// Or was there a LMB double click?
			if (lParam==WM_LBUTTONDBLCLK)
			{
				// double click: execute first menu item
				SendMessage(_this->m_nid.hWnd,
							WM_COMMAND, 
							GetMenuItemID(submenu, 0),
							0);
			}

			return 0;
		}
		
	case WM_CLOSE:
		
		// Only accept WM_CLOSE if the logged on user has AllowShutdown set
		if (!_this->m_properties.AllowShutdown())
		{
			return 0;
		}
		// tnatsni Wallpaper fix
		if (_this->m_server->RemoveWallpaperEnabled())
			RestoreWallpaper();
		if (_this->m_server->RemoveAeroEnabled())
			ResetAero();

		vnclog.Print(LL_INTERR, VNCLOG("vncMenu WM_CLOSE call - All cleanup done\n"));
		Sleep(2000);
		DestroyWindow(hwnd);
		break;
		
	case WM_DESTROY:
		// The user wants WinVNC to quit cleanly...
		vnclog.Print(LL_INTINFO, VNCLOG("quitting from WM_DESTROY\n"));
		PostQuitMessage(0);
		return 0;
		
	case WM_QUERYENDSESSION:
		{
			//shutdown or reboot
			if((lParam & ENDSESSION_LOGOFF) != ENDSESSION_LOGOFF)
			{
				fShutdownOrdered=TRUE;
				Sleep(1000);
				vnclog.Print(LL_INTERR, VNCLOG("SHUTDOWN OS detected\n"));
				vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() ID_CLOSE \n"));
				_this->m_server->KillAuthClients();				
				PostMessage(hwnd, WM_CLOSE, 0, 0);
				break;
			}


			DWORD SessionID;
			SessionID=GetCurrentSessionID();
			vnclog.Print(LL_INTERR, VNCLOG("Session ID %i\n"),SessionID);
			if (SessionID!=0)
			{
				fShutdownOrdered=TRUE;
				Sleep(1000);
				vnclog.Print(LL_INTERR, VNCLOG("WM_QUERYENDSESSION session!=0\n"));
				vnclog.Print(LL_INTINFO, VNCLOG("KillAuthClients() ID_CLOSE \n"));
				_this->m_server->KillAuthClients();				
				PostMessage(hwnd, WM_CLOSE, 0, 0);
			}
		}	
		break;
		
	case WM_ENDSESSION:
		vnclog.Print(LL_INTERR, VNCLOG("WM_ENDSESSION\n"));
		break;

	case WM_USERCHANGED:
		// The current user may have changed.
		{
			strcpy(newuser,"");

			if (vncService::CurrentUser((char *) &newuser, sizeof(newuser)))
			{
				vnclog.Print(LL_INTINFO,
					VNCLOG("############### Usernames change: old=\"%s\", new=\"%s\"\n"),
					_this->m_username, newuser);

				// Check whether the user name has changed!
				if (_stricmp(newuser, _this->m_username) != 0)
				{
					vnclog.Print(LL_INTINFO,
						VNCLOG("user name has changed\n"));

					// User has changed!
					strcpy(_this->m_username, newuser);

					// Redraw the tray icon and set it's state
					_this->DelTrayIcon();
					_this->AddTrayIcon();
					_this->FlashTrayIcon(_this->m_server->AuthClientCount() != 0);
					// We should load in the prefs for the new user
					if (_this->m_properties.m_fUseRegistry)
					{
						_this->m_properties.Load(TRUE);
						_this->m_propertiesPoll.Load(TRUE);
					}
					else
					{
						_this->m_properties.LoadFromIniFile();
						_this->m_propertiesPoll.LoadFromIniFile();
					}
				}
			}
		}
		return 0;

	// [v1.0.2-jp1 fix] Don't show IME toolbar on right click menu.
	case WM_INITMENU:
	case WM_INITMENUPOPUP:
		SendMessage(ImmGetDefaultIMEWnd(hwnd), WM_IME_CONTROL, IMC_CLOSESTATUSWINDOW, 0);
		return 0;

	default:
		// Deal with any of our custom message types		
		// wa@2005 -- added support for the AutoReconnectId
		// removed the previous code that used 999,999
		if ( iMsg == MENU_AUTO_RECONNECT_MSG )
		{
			char szId[MAX_PATH] = {0};
			UINT ret = 0;
			if ( lParam != NULL )
			{
				ret = GlobalGetAtomName( (ATOM)lParam, szId, sizeof( szId ) );
				GlobalDeleteAtom( (ATOM)lParam );
			}
			
			_this->m_server->AutoReconnect(true);
			
			if ( ret > 0 )
				_this->m_server->AutoReconnectId(szId);
			
			return 0;
		}
		if ( iMsg == MENU_REPEATER_ID_MSG )
 		{
			char szId[MAX_PATH] = {0};
			UINT ret = 0;
			if ( lParam != NULL )
			{
				ret = GlobalGetAtomName( (ATOM)lParam, szId, sizeof( szId ) );
				GlobalDeleteAtom( (ATOM)lParam );
			}
			_this->m_server->IdReconnect(true);
			
			if ( ret > 0 )
				_this->m_server->AutoReconnectId(szId);
			
			return 0;
		}


		if (iMsg == MENU_ADD_CLIENT_MSG)
		{
			/*
			// sf@2005 - FTNoUserImpersonation
			// Dirty trick to avoid to add a new MSG... no time
			if (lParam == 998)
			{
				_this->m_server->FTUserImpersonation(false);
				return 0;
			}
			*/

			// Add Client message.  This message includes an IP address
			// of a listening client, to which we should connect.

			//adzm 2009-06-20 - Check for special add repeater client message
			if (wParam == 0xFFFFFFFF && lParam == 0xFFFFFFFF) {
				vncConnDialog *newconn = new vncConnDialog(_this->m_server);
				if (newconn)
				{
					if (IDOK != newconn->DoDialog()) {
						if (SPECIAL_SC_PROMPT && _this->m_server->AuthClientCount() == 0 && _this->m_server->UnauthClientCount() == 0) {
							PostMessage(hwnd, WM_COMMAND, ID_CLOSE, 0);
						}
					}
				}
				return 0;
			}

			// If there is no IP address then show the connection dialog
			if (!lParam) {
				vncConnDialog *newconn = new vncConnDialog(_this->m_server);
				if (newconn)
				{
					newconn->DoDialog();
					// winvnc -connect fixed
					//CHECH memeory leak
					//			delete newconn;
				}
				return 0;
			}

			unsigned short nport = 0;
			char *nameDup = 0;
			char szAdrName[64];
			char szId[MAX_PATH] = {0};
			// sf@2003 - Values are already converted
			if ((_this->m_server->AutoReconnect()|| _this->m_server->IdReconnect() )&& strlen(_this->m_server->AutoReconnectAdr()) > 0)
			{
				nport = _this->m_server->AutoReconnectPort();
				strcpy(szAdrName, _this->m_server->AutoReconnectAdr());
			}
			else
			{
				// Get the IP address stringified
				struct in_addr address;
				address.S_un.S_addr = lParam;
				char *name = inet_ntoa(address);
				if (name == 0)
					return 0;
				nameDup = _strdup(name);
				if (nameDup == 0)
					return 0;
				strcpy(szAdrName, nameDup);
				// Free the duplicate name
				if (nameDup != 0) free(nameDup);

				// Get the port number
				nport = (unsigned short)wParam;
				if (nport == 0)
					nport = INCOMING_PORT_OFFSET;
				
			}

			// wa@2005 -- added support for the AutoReconnectId
			// (but it's not required)
			bool bId = ( strlen(_this->m_server->AutoReconnectId() ) > 0);
			if ( bId )
				strcpy( szId, _this->m_server->AutoReconnectId() );
			
			// sf@2003
			// Stores the client adr/ports the first time we try to connect
			// This way we can call this message again later to reconnect with the same values
			if ((_this->m_server->AutoReconnect() || _this->m_server->IdReconnect())&& strlen(_this->m_server->AutoReconnectAdr()) == 0)
			{
				_this->m_server->AutoReconnectAdr(szAdrName);
				_this->m_server->AutoReconnectPort(nport);
			}

			// Attempt to create a new socket
			VSocket *tmpsock;
			tmpsock = new VSocket;
			if (tmpsock) {

				// Connect out to the specified host on the VNCviewer listen port
				tmpsock->Create();
				if (tmpsock->Connect(szAdrName, nport)) {
					if ( bId )
					{
						// wa@2005 -- added support for the AutoReconnectId
						// Set the ID for this client -- code taken from vncconndialog.cpp (ln:142)
						tmpsock->Send(szId,250);
						tmpsock->SetTimeout(0);
						
						// adzm 2009-07-05 - repeater IDs
						// Add the new client to this server
						// adzm 2009-08-02
						_this->m_server->AddClient(tmpsock, TRUE, TRUE, 0, NULL, szId, szAdrName, nport);
					} else {
						// Add the new client to this server
						// adzm 2009-08-02
						_this->m_server->AddClient(tmpsock, TRUE, TRUE, 0, NULL, NULL, szAdrName, nport);
					}
				} else {
					delete tmpsock;
					_this->m_server->AutoConnectRetry();
				}
			}
		
			return 0;
		}

		// Process FileTransfer asynchronous Send Packet Message
		if (iMsg == FileTransferSendPacketMessage) 
		{
		  vncClient* pClient = (vncClient*) wParam;
		  if (_this->m_server->IsClient(pClient)) pClient->SendFileChunk();
		}

		// adzm 2009-07-05 - Tray icon balloon tips
		if (iMsg == MENU_TRAYICON_BALLOON_MSG) {
			omni_mutex_lock sync(_this->m_mutexTrayIcon);

			// adzm 2009-07-05 - Tray icon balloon tips
			if (_this->m_BalloonInfo) {		
				free(_this->m_BalloonInfo);
				_this->m_BalloonInfo = NULL;
			}
			if (_this->m_BalloonTitle) {
				free(_this->m_BalloonTitle);
				_this->m_BalloonTitle = NULL;
			}

			char* szInfo = (char*)wParam;
			char* szTitle = (char*)lParam;
			
			if (szInfo && (strlen(szInfo) > 0) ) {
				_this->m_BalloonInfo = _strdup(szInfo);
			}
			if (szTitle && (strlen(szTitle) > 0) ) {
				_this->m_BalloonTitle = _strdup(szTitle);
			}

			if (szInfo) {
				free(szInfo);
			}
			if (szTitle) {
				free(szTitle);
			}

			if (_this->IsIconSet) {
				_this->SendTrayMsg(NIM_MODIFY, _this->m_nid.hIcon == _this->m_winvnc_icon ? FALSE : TRUE);
			}
		}
	}

	// Message not recognised
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}