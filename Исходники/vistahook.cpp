DWORD WINAPI Cadthread(LPVOID lpParam)
{
	OSVERSIONINFO OSversion;	
	OSversion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&OSversion);


	HDESK desktop=NULL;
	desktop = OpenInputDesktop(0, FALSE,
								DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |
								DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |
								DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |
								DESKTOP_SWITCHDESKTOP | GENERIC_WRITE
								);


	
	if (desktop == NULL)
		vnclog.Print(LL_INTERR, VNCLOG("OpenInputdesktop Error \n"));
	else 
		vnclog.Print(LL_INTERR, VNCLOG("OpenInputdesktop OK\n"));

	HDESK old_desktop = GetThreadDesktop(GetCurrentThreadId());
	DWORD dummy;

	char new_name[256];
	if (desktop)
	{
	if (!GetUserObjectInformation(desktop, UOI_NAME, &new_name, 256, &dummy))
	{
		vnclog.Print(LL_INTERR, VNCLOG("!GetUserObjectInformation \n"));
	}

	vnclog.Print(LL_INTERR, VNCLOG("SelectHDESK to %s (%x) from %x\n"), new_name, desktop, old_desktop);

	if (!SetThreadDesktop(desktop))
	{
		vnclog.Print(LL_INTERR, VNCLOG("SelectHDESK:!SetThreadDesktop \n"));
	}
	}

	//////
	if(OSversion.dwMajorVersion>=6 && vncService::RunningAsService())
			{				
					if( vncService::RunningAsService() &&!IsSoftwareCadEnabled())
					{
						DWORD result=MessageBoxSecure(NULL,"UAC is Disable, make registry changes to allow cad","Warning",MB_YESNO);
						if (result==IDYES)
							{
								HANDLE hProcess=NULL,hPToken=NULL;
								DWORD id=GetExplorerLogonPid();
								if (id!=0) 
									{						
									hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
									if (!hProcess) goto error;
									if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
													|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
													| TOKEN_READ | TOKEN_WRITE, &hPToken))
									{
										CloseHandle(hProcess);
										goto error;
									}
									char dir[MAX_PATH];
									char exe_file_name[MAX_PATH];
									GetModuleFileName(0, exe_file_name, MAX_PATH);
									strcpy(dir, exe_file_name);
									strcat(dir, " -softwarecadhelper");
		
							
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
									if (ProcessInfo.hProcess) CloseHandle(ProcessInfo.hProcess);
									if (ProcessInfo.hThread) CloseHandle(ProcessInfo.hThread);
									if (errorcode == 1314) goto error;
									goto gotome;
									error:
											Enable_softwareCAD_elevated();							
									}
							}
					
					}
			}
	gotome:
       /////////////////////
	if(OSversion.dwMajorVersion==6)//&& OSversion.dwMinorVersion>=1) //win7  // test win7 +Vista
	{

		if (hShutdownEventcad==NULL ) hShutdownEventcad = OpenEvent(EVENT_MODIFY_STATE, FALSE, "Global\\SessionEventUltraCad");
		if (hShutdownEventcad!=NULL ) SetEvent(hShutdownEventcad);
		if (old_desktop) SetThreadDesktop(old_desktop);
		if (desktop) CloseDesktop(desktop);
		return 0;
	}

	 HKEY hKey; 
	 DWORD isLUAon = 0; 
     if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), 0, KEY_READ, &hKey) == ERROR_SUCCESS) 
              { 
              DWORD LUAbufSize = 4; 
              RegQueryValueEx(hKey, TEXT("EnableLUA"), NULL, NULL, (LPBYTE)&isLUAon, &LUAbufSize); 
              RegCloseKey(hKey); 
			  }
     if (isLUAon != 1 && OSversion.dwMajorVersion==6) 
	 {
		 if (hShutdownEventcad==NULL ) hShutdownEventcad = OpenEvent(EVENT_MODIFY_STATE, FALSE, "Global\\SessionEventUltraCad");
		 if (hShutdownEventcad!=NULL ) SetEvent(hShutdownEventcad);
		 if (old_desktop) SetThreadDesktop(old_desktop);
		 if (desktop) CloseDesktop(desktop);
		 return 0;
	 }

//Full path needed, sometimes it just default to system32
	char WORKDIR[MAX_PATH];
	char mycommand[MAX_PATH];
	if (GetModuleFileName(NULL, WORKDIR, MAX_PATH))
		{
		char* p = strrchr(WORKDIR, '\\');
		if (p == NULL) return 0;
		*p = '\0';
		}
	strcpy(mycommand,"");
	strcat(mycommand,WORKDIR);//set the directory
	strcat(mycommand,"\\");
	strcat(mycommand,"cad.exe");

	int nr=(LONG_PTR)ShellExecute(GetDesktopWindow(), "open", mycommand, "", 0, SW_SHOWNORMAL);
	if (nr<=32)
	{
		//error
		//
		if ( nr==SE_ERR_ACCESSDENIED )
			vncTimedMsgBox::Do(
									sz_ID_CADPERMISSION,
									sz_ID_ULTRAVNC_WARNING,
									MB_ICONINFORMATION | MB_OK
									);

		if ( nr==ERROR_PATH_NOT_FOUND || nr==ERROR_FILE_NOT_FOUND)
			vncTimedMsgBox::Do(
									sz_ID_CADERRORFILE,
									sz_ID_ULTRAVNC_WARNING,
									MB_ICONINFORMATION | MB_OK
									);

	}

	if (old_desktop) SetThreadDesktop(old_desktop);
	if (desktop) CloseDesktop(desktop);
	return 0;
}