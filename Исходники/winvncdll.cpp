int WINAPI WinMain_(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	// make vnc last service to stop
	SetProcessShutdownParameters(0x100,false);
	// handle dpi on aero
	HMODULE hUser32 = LoadLibrary(_T("user32.dll"));
	typedef BOOL (*SetProcessDPIAwareFunc)();
	SetProcessDPIAwareFunc setDPIAware = (SetProcessDPIAwareFunc)GetProcAddress(hUser32, "SetProcessDPIAware");
	if (setDPIAware) setDPIAware();
	FreeLibrary(hUser32);

#ifdef IPP
	InitIpp();
#endif
#ifdef CRASHRPT
	Install(NULL, _T("*****@*****.**"), _T(""));
#endif
	bool Injected_autoreconnect=false;
	SPECIAL_SC_EXIT=false;
	SPECIAL_SC_PROMPT=false;
	SetOSVersion();
	setbuf(stderr, 0);

	// [v1.0.2-jp1 fix] Load resouce from dll
	hInstResDLL = NULL;

	 //limit the vnclang.dll searchpath to avoid
	char szCurrentDir[MAX_PATH];
	char szCurrentDir_vnclangdll[MAX_PATH];
	if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
	{
		char* p = strrchr(szCurrentDir, '\\');
		*p = '\0';
	}
	strcpy (szCurrentDir_vnclangdll,szCurrentDir);
	strcat (szCurrentDir_vnclangdll,"\\");
	strcat (szCurrentDir_vnclangdll,"vnclang_server.dll");

	hInstResDLL = LoadLibrary(szCurrentDir_vnclangdll);

	if (hInstResDLL == NULL)
	{
		hInstResDLL = hInstance;
	}
//	RegisterLinkLabel(hInstResDLL);

    //Load all messages from ressource file
    Load_Localization(hInstResDLL) ;

	char WORKDIR[MAX_PATH];
	if (GetModuleFileName(NULL, WORKDIR, MAX_PATH))
		{
		char* p = strrchr(WORKDIR, '\\');
		if (p == NULL) return 0;
		*p = '\0';
		}
    char progname[MAX_PATH];
    strncpy(progname, WORKDIR, sizeof progname);
    progname[MAX_PATH - 1] = 0;
	//strcat(WORKDIR,"\\");
	//strcat(WORKDIR,"WinVNC.log");

	vnclog.SetFile();
//	vnclog.SetMode(2);
//	vnclog.SetLevel(10);

#ifdef _DEBUG
	{
		// Get current flag
		int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );

		// Turn on leak-checking bit
		tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

		// Set flag to the new value
		_CrtSetDbgFlag( tmpFlag );
	}
#endif

	// Save the application instance and main thread id
	hAppInstance = hInstance;
	mainthreadId = GetCurrentThreadId();

	// Initialise the VSocket system
	VSocketSystem socksys;
	if (!socksys.Initialised())
	{
		MessageBoxSecure(NULL, sz_ID_FAILED_INIT, szAppName, MB_OK);
		return 0;
	}
    // look up the current service name in the registry.
    GetServiceName(progname, service_name);

	// Make the command-line lowercase and parse it
	size_t i;
	for (i = 0; i < strlen(szCmdLine); i++)
	{
		szCmdLine[i] = tolower(szCmdLine[i]);
	}
	BOOL argfound = FALSE;
	for (i = 0; i < strlen(szCmdLine); i++)
	{
		if (szCmdLine[i] <= ' ')
			continue;
		argfound = TRUE;

		if (strncmp(&szCmdLine[i], winvncSettingshelper, strlen(winvncSettingshelper)) == 0)
		{
			Sleep(3000);
			char mycommand[MAX_PATH];
			i+=strlen(winvncSettingshelper);
			strcpy( mycommand, &(szCmdLine[i+1]));
			Set_settings_as_admin(mycommand);
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncStopserviceHelper, strlen(winvncStopserviceHelper)) == 0)
		{
			Sleep(3000);
			Set_stop_service_as_admin();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncKill, strlen(winvncKill)) == 0)
		{
			static HANDLE		hShutdownEventTmp;
			hShutdownEventTmp = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\SessionEventUltra");
			SetEvent(hShutdownEventTmp);
			CloseHandle(hShutdownEventTmp);

			//adzm 2010-02-10 - Finds the appropriate VNC window for any process. Sends this message to all of them!
			HWND hservwnd = NULL;
			do {
				if (hservwnd!=NULL)
				{
					PostMessage(hservwnd, WM_COMMAND, 40002, 0);
					PostMessage(hservwnd, WM_CLOSE, 0, 0);
				}
				hservwnd = FindWinVNCWindow(false);
			} while (hservwnd!=NULL);
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncopenhomepage, strlen(winvncopenhomepage)) == 0)
		{
			Open_homepage();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncopenforum, strlen(winvncopenforum)) == 0)
		{
			Open_forum();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncStartserviceHelper, strlen(winvncStartserviceHelper)) == 0)
		{
			Sleep(3000);
			Set_start_service_as_admin();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncInstallServiceHelper, strlen(winvncInstallServiceHelper)) == 0)
			{
				//Sleeps are realy needed, else runas fails...
				Sleep(3000);
				Set_install_service_as_admin();
				return 0;
			}
		if (strncmp(&szCmdLine[i], winvncUnInstallServiceHelper, strlen(winvncUnInstallServiceHelper)) == 0)
			{
				Sleep(3000);
				Set_uninstall_service_as_admin();
				return 0;
			}
		if (strncmp(&szCmdLine[i], winvncSoftwarecadHelper, strlen(winvncSoftwarecadHelper)) == 0)
			{
				Sleep(3000);
				Enable_softwareCAD_elevated();
				return 0;
			}
		if (strncmp(&szCmdLine[i], winvncdelSoftwarecadHelper, strlen(winvncdelSoftwarecadHelper)) == 0)
			{
				Sleep(3000);
				delete_softwareCAD_elevated();
				return 0;
			}
		if (strncmp(&szCmdLine[i], winvncRebootSafeHelper, strlen(winvncRebootSafeHelper)) == 0)
			{
				Sleep(3000);
				Reboot_in_safemode_elevated();
				return 0;
			}

		if (strncmp(&szCmdLine[i], winvncRebootForceHelper, strlen(winvncRebootForceHelper)) == 0)
			{
				Sleep(3000);
				Reboot_with_force_reboot_elevated();
				return 0;
			}

		if (strncmp(&szCmdLine[i], winvncSecurityEditorHelper, strlen(winvncSecurityEditorHelper)) == 0)
			{
				Sleep(3000);
				winvncSecurityEditorHelper_as_admin();
				return 0;
			}
		if (strncmp(&szCmdLine[i], winvncSecurityEditor, strlen(winvncSecurityEditor)) == 0)
			{
			    typedef void (*vncEditSecurityFn) (HWND hwnd, HINSTANCE hInstance);
				vncEditSecurityFn vncEditSecurity = 0;
				char szCurrentDir[MAX_PATH];
					if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH)) {
						char* p = strrchr(szCurrentDir, '\\');
						*p = '\0';
						strcat (szCurrentDir,"\\authSSP.dll");
					}
					HMODULE hModule = LoadLibrary(szCurrentDir);
					if (hModule) {
						vncEditSecurity = (vncEditSecurityFn) GetProcAddress(hModule, "vncEditSecurity");
						HRESULT hr = CoInitialize(NULL);
						vncEditSecurity(NULL, hAppInstance);
						CoUninitialize();
						FreeLibrary(hModule);
					}
				return 0;
			}

		if (strncmp(&szCmdLine[i], winvncSettings, strlen(winvncSettings)) == 0)
		{
			char mycommand[MAX_PATH];
			i+=strlen(winvncSettings);
			strcpy( mycommand, &(szCmdLine[i+1]));
			Real_settings(mycommand);
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncSoftwarecad, strlen(winvncSoftwarecad)) == 0)
		{
			Enable_softwareCAD();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncdelSoftwarecad, strlen(winvncdelSoftwarecad)) == 0)
		{
			delete_softwareCAD();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncRebootSafe, strlen(winvncRebootSafe)) == 0)
		{
			Reboot_in_safemode();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncRebootForce, strlen(winvncRebootForce)) == 0)
		{
			Reboot_with_force_reboot();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncStopservice, strlen(winvncStopservice)) == 0)
		{
			Real_stop_service();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncStartservice, strlen(winvncStartservice)) == 0)
		{
			Real_start_service();
			return 0;
		}

		if (strncmp(&szCmdLine[i], winvncInstallService, strlen(winvncInstallService)) == 0)
			{
                // rest of command line service name, if provided.
                char *pServiceName = &szCmdLine[i];
                // skip over command switch, find next whitepace
                while (*pServiceName && !isspace(*(unsigned char*)pServiceName))
                    ++pServiceName;

                // skip past whitespace to service name
                while (*pServiceName && isspace(*(unsigned char*)pServiceName))
                    ++pServiceName;

                // strip off any quotes
                if (*pServiceName && *pServiceName == '\"')
                    ++pServiceName;

                if (*pServiceName)
                {
                    // look for trailing quote, if found, terminate the string there.
                    char *pQuote = pServiceName;
                    pQuote = strrchr(pServiceName, '\"');
                    if (pQuote)
                        *pQuote = 0;
                }
                // if a service name is supplied, and it differs except in case from
                // the default, use the supplied service name instead
                if (*pServiceName && (_strcmpi(pServiceName, service_name) != 0))
                {
                    strncpy(service_name, pServiceName, 256);
                    service_name[255] = 0;
                }
				install_service();
				Sleep(2000);
				char command[MAX_PATH + 32]; // 29 January 2008 jdp
                _snprintf(command, sizeof command, "net start \"%s\"", service_name);
				WinExec(command,SW_HIDE);
				return 0;
			}
		if (strncmp(&szCmdLine[i], winvncUnInstallService, strlen(winvncUnInstallService)) == 0)
			{
				char command[MAX_PATH + 32]; // 29 January 2008 jdp
                // rest of command line service name, if provided.
                char *pServiceName = &szCmdLine[i];
                // skip over command switch, find next whitepace
                while (*pServiceName && !isspace(*(unsigned char*)pServiceName))
                    ++pServiceName;

                // skip past whitespace to service name
                while (*pServiceName && isspace(*(unsigned char*)pServiceName))
                    ++pServiceName;

                // strip off any quotes
                if (*pServiceName && *pServiceName == '\"')
                    ++pServiceName;

                if (*pServiceName)
                {
                    // look for trailing quote, if found, terminate the string there.
                    char *pQuote = pServiceName;
                    pQuote = strrchr(pServiceName, '\"');
                    if (pQuote)
                        *pQuote = 0;
                }

                if (*pServiceName && (_strcmpi(pServiceName, service_name) != 0))
                {
                    strncpy(service_name, pServiceName, 256);
                    service_name[255] = 0;
                }
                _snprintf(command, sizeof command, "net stop \"%s\"", service_name);
				WinExec(command,SW_HIDE);
				uninstall_service();
				return 0;
			}

		if (strncmp(&szCmdLine[i], winvncRunService, strlen(winvncRunService)) == 0)
		{
			//Run as service
			if (!Myinit(hInstance)) return 0;
			fRunningFromExternalService = true;
			vncService::RunningFromExternalService(true);
			return WinVNCAppMain();
		}

		if (strncmp(&szCmdLine[i], winvncStartService, strlen(winvncStartService)) == 0)
		{
		start_service(szCmdLine);
		return 0;
		}

		if (strncmp(&szCmdLine[i], winvncRunAsUserApp, strlen(winvncRunAsUserApp)) == 0)
		{
			// WinVNC is being run as a user-level program
			if (!Myinit(hInstance)) return 0;
			return WinVNCAppMain();
		}

		if (strncmp(&szCmdLine[i], winvncSCexit, strlen(winvncSCexit)) == 0)
		{
			SPECIAL_SC_EXIT=true;
			i+=strlen(winvncSCexit);
			continue;
		}

		if (strncmp(&szCmdLine[i], winvncSCprompt, strlen(winvncSCprompt)) == 0)
		{
			SPECIAL_SC_PROMPT=true;
			i+=strlen(winvncSCprompt);
			continue;
		}

		if (strncmp(&szCmdLine[i], winvncmulti, strlen(winvncmulti)) == 0)
		{
			multi=true;
			i+=strlen(winvncmulti);
			continue;
		}

		if (strncmp(&szCmdLine[i], winvnchttp, strlen(winvnchttp)) == 0)
		{
			G_HTTP=true;
			i+=strlen(winvnchttp);
			continue;
		}

		if (strncmp(&szCmdLine[i], winvncStopReconnect, strlen(winvncStopReconnect)) == 0)
		{
			i+=strlen(winvncStopReconnect);
			vncService::PostAddStopConnectClientAll();
			continue;
		}

		if (strncmp(&szCmdLine[i], winvncAutoReconnect, strlen(winvncAutoReconnect)) == 0)
		{
			// Note that this "autoreconnect" param MUST be BEFORE the "connect" one
			// on the command line !
			// wa@2005 -- added support for the AutoReconnectId
			i+=strlen(winvncAutoReconnect);
			Injected_autoreconnect=true;
			int start, end;
			char* pszId = NULL;
			start = i;
			// skip any spaces and grab the parameter
			while (szCmdLine[start] <= ' ' && szCmdLine[start] != 0) start++;

			if ( strncmp( &szCmdLine[start], winvncAutoReconnectId, strlen(winvncAutoReconnectId) ) == 0 )
			{
				end = start;
				while (szCmdLine[end] > ' ') end++;

				pszId = new char[ end - start + 1 ];
				if (pszId != 0)
				{
					strncpy( pszId, &(szCmdLine[start]), end - start );
					pszId[ end - start ] = 0;
					pszId = _strupr( pszId );
				}
//multiple spaces between autoreconnect and id
				i = end;
			}// end of condition we found the ID: parameter

			// NOTE:  id must be NULL or the ID:???? (pointer will get deleted when message is processed)
			// We can not contact a runnning service, permissions, so we must store the settings
			// and process until the vncmenu has been started

			if (!vncService::PostAddAutoConnectClient( pszId ))
			{
				PostAddAutoConnectClient_bool=true;
				if (pszId==NULL)
				{
					PostAddAutoConnectClient_bool_null=true;
					PostAddAutoConnectClient_bool=false;
				}
				else
				{
					strcpy(pszId_char,pszId);
					//memory leak fix
					delete [] pszId;
				}
			}
			continue;
		}

		if ( strncmp( &szCmdLine[i], winvncReconnectId, strlen(winvncReconnectId) ) == 0 )
			{
				i+=strlen("-");
				int start, end;
				char* pszId = NULL;
				start = i;
				end = start;
				while (szCmdLine[end] > ' ') end++;

				pszId = new char[ end - start + 1 ];
				if (pszId != 0)
				{
					strncpy( pszId, &(szCmdLine[start]), end - start );
					pszId[ end - start ] = 0;
					pszId = _strupr( pszId );
				}
				i = end;
			if (!vncService::PostAddConnectClient( pszId ))
			{
				PostAddConnectClient_bool=true;
				if (pszId==NULL)
				{
					PostAddConnectClient_bool_null=true;
					PostAddConnectClient_bool=false;
				}
				else
				{
					strcpy(pszId_char,pszId);
					//memory leak fix
					delete [] pszId;
				}
				}
			continue;
		}

		if (strncmp(&szCmdLine[i], winvncConnect, strlen(winvncConnect)) == 0)
		{
			if (!Injected_autoreconnect)
			{
				vncService::PostAddStopConnectClient();
			}
			// Add a new client to an existing copy of winvnc
			i+=strlen(winvncConnect);

			// First, we have to parse the command line to get the filename to use
			int start, end;
			start=i;
			while (szCmdLine[start] <= ' ' && szCmdLine[start] != 0) start++;
			end = start;
			while (szCmdLine[end] > ' ') end++;

			// Was there a hostname (and optionally a port number) given?
			if (end-start > 0)
			{
				char *name = new char[end-start+1];
				if (name != 0) {
					strncpy(name, &(szCmdLine[start]), end-start);
					name[end-start] = 0;

					int port = INCOMING_PORT_OFFSET;
					char *portp = strchr(name, ':');
					if (portp) {
						*portp++ = '\0';
						if (*portp == ':') {
							port = atoi(++portp);	// Port number after "::"
						} else {
							port = atoi(portp);	// Display number after ":"
						}
					}
					vnclog.Print(LL_STATE, VNCLOG("test... %s %d\n"),name,port);
					strcpy_s(dnsname,name);
					VCard32 address = VSocket::Resolve(name);
					delete [] name;
					if (address != 0) {
						// Post the IP address to the server
						// We can not contact a runnning service, permissions, so we must store the settings
						// and process until the vncmenu has been started
						vnclog.Print(LL_INTERR, VNCLOG("PostAddNewClient III \n"));
						if (!vncService::PostAddNewClientInit(address, port))
						{
						PostAddNewClient_bool=true;
						port_int=port;
						address_vcard=address;
						}
					}
					else
					{
						//ask for host,port
						PostAddNewClient_bool=true;
						port_int=0;
						address_vcard=0;
						Sleep(2000);
						//Beep(200,1000);
						return 0;
					}
				}
				i=end;
				continue;
			}
			else
			{
				// Tell the server to show the Add New Client dialog
				// We can not contact a runnning service, permissions, so we must store the settings
				// and process until the vncmenu has been started
				vnclog.Print(LL_INTERR, VNCLOG("PostAddNewClient IIII\n"));
				if (!vncService::PostAddNewClient(0, 0))
				{
				PostAddNewClient_bool=true;
				port_int=0;
				address_vcard=0;
				}
			}
			continue;
		}

		//adzm 2009-06-20
		if (strncmp(&szCmdLine[i], winvncRepeater, strlen(winvncRepeater)) == 0)
		{
			// set the default repeater host
			i+=strlen(winvncRepeater);

			// First, we have to parse the command line to get the host to use
			int start, end;
			start=i;
			while (szCmdLine[start] <= ' ' && szCmdLine[start] != 0) start++;
			end = start;
			while (szCmdLine[end] > ' ') end++;

			// Was there a hostname (and optionally a port number) given?
			if (end-start > 0)
			{
				if (g_szRepeaterHost) {
					delete[] g_szRepeaterHost;
					g_szRepeaterHost = NULL;
				}
				g_szRepeaterHost = new char[end-start+1];
				if (g_szRepeaterHost != 0) {
					strncpy(g_szRepeaterHost, &(szCmdLine[start]), end-start);
					g_szRepeaterHost[end-start] = 0;

					// We can not contact a runnning service, permissions, so we must store the settings
					// and process until the vncmenu has been started
					vnclog.Print(LL_INTERR, VNCLOG("PostAddNewRepeaterClient I\n"));
					if (!vncService::PostAddNewRepeaterClient())
					{
						PostAddNewRepeaterClient_bool=true;
						port_int=0;
						address_vcard=0;
					}
				}
				i=end;
				continue;
			}
			else
			{
				/*
				// Tell the server to show the Add New Client dialog
				// We can not contact a runnning service, permissions, so we must store the settings
				// and process until the vncmenu has been started
				vnclog.Print(LL_INTERR, VNCLOG("PostAddNewClient IIII\n"));
				if (!vncService::PostAddNewClient(0, 0))
				{
				PostAddNewClient_bool=true;
				port_int=0;
				address_vcard=0;
				}
				*/
			}
			continue;
		}

		// Either the user gave the -help option or there is something odd on the cmd-line!

		// Show the usage dialog
		MessageBoxSecure(NULL, winvncUsageText, sz_ID_WINVNC_USAGE, MB_OK | MB_ICONINFORMATION);
		break;
	};

	// If no arguments were given then just run
	if (!argfound)
	{
		if (!Myinit(hInstance)) return 0;
		return WinVNCAppMain();
	}

	return 0;
}