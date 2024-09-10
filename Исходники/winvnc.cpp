DWORD WINAPI imp_desktop_thread(LPVOID lpParam)
{
	vncServer *server = (vncServer *)lpParam;
	HDESK desktop;
	//vnclog.Print(LL_INTERR, VNCLOG("SelectDesktop \n"));
	//vnclog.Print(LL_INTERR, VNCLOG("OpenInputdesktop2 NULL\n"));
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

	if (!GetUserObjectInformation(desktop, UOI_NAME, &new_name, 256, &dummy))
	{
		vnclog.Print(LL_INTERR, VNCLOG("!GetUserObjectInformation \n"));
	}

	vnclog.Print(LL_INTERR, VNCLOG("SelectHDESK to %s (%x) from %x\n"), new_name, desktop, old_desktop);

	if (!SetThreadDesktop(desktop))
	{
		vnclog.Print(LL_INTERR, VNCLOG("SelectHDESK:!SetThreadDesktop \n"));
	}

//	ImpersonateCurrentUser_();

	char m_username[UNLEN+1];
	HWINSTA station = GetProcessWindowStation();
	if (station != NULL)
	{
		DWORD usersize;
		GetUserObjectInformation(station, UOI_USER_SID, NULL, 0, &usersize);
		DWORD  dwErrorCode = GetLastError();
		SetLastError(0);
		if (usersize != 0)
		{
			DWORD length = sizeof(m_username);
			if (GetUserName(m_username, &length) == 0)
			{
				UINT error = GetLastError();
				if (error != ERROR_NOT_LOGGED_ON)
				{
					vnclog.Print(LL_INTERR, VNCLOG("getusername error %d\n"), GetLastError());
					SetThreadDesktop(old_desktop);
                	CloseDesktop(desktop);
					Sleep(500);
					return FALSE;
				}
			}
		}
	}
    vnclog.Print(LL_INTERR, VNCLOG("Username %s \n"),m_username);

	// Create tray icon and menu
	vncMenu *menu = new vncMenu(server);
	if (menu == NULL)
	{
		vnclog.Print(LL_INTERR, VNCLOG("failed to create tray menu\n"));
		PostQuitMessage(0);
	}

	// This is a good spot to handle the old PostAdd messages
	if (PostAddAutoConnectClient_bool)
		vncService::PostAddAutoConnectClient( pszId_char );
	if (PostAddAutoConnectClient_bool_null)
		vncService::PostAddAutoConnectClient( NULL );

	if (PostAddConnectClient_bool)
		vncService::PostAddConnectClient( pszId_char );
	if (PostAddConnectClient_bool_null)
		vncService::PostAddConnectClient( NULL );

	if (PostAddNewClient_bool)
	{
		PostAddNewClient_bool=false;
		vnclog.Print(LL_INTERR, VNCLOG("PostAddNewClient IIIII\n"));
		vncService::PostAddNewClient(address_vcard, port_int);
	}
	//adzm 2009-06-20
	if (PostAddNewRepeaterClient_bool)
	{
		PostAddNewRepeaterClient_bool=false;
		vnclog.Print(LL_INTERR, VNCLOG("PostAddNewRepeaterClient II\n"));
		vncService::PostAddNewRepeaterClient();
	}
	bool Runonce=false;
	MSG msg;
	while (GetMessage(&msg,0,0,0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (fShutdownOrdered && !Runonce)
		{
			Runonce=true;
			if (menu) menu->Shutdown(true);
		}

		if (hShutdownEvent)
		{
			// vnclog.Print(LL_INTERR, VNCLOG("****************** SDTimer tic\n"));
			DWORD result = WaitForSingleObject(hShutdownEvent, 1);
			if (WAIT_OBJECT_0 == result)
			{
				ResetEvent(hShutdownEvent);
				fShutdownOrdered = true;
				vnclog.Print(LL_INTERR, VNCLOG("****************** WaitForSingleObject - Shutdown server\n"));
			}
		}
	}

	// sf@2007 - Close all (vncMenu,tray icon, connections...)

	if (menu != NULL)
		delete menu;

	//vnclog.Print(LL_INTERR, VNCLOG("GetMessage stop \n"));
	SetThreadDesktop(old_desktop);
	CloseDesktop(desktop);
//	RevertToSelf();
	return 0;
}