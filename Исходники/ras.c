int ConnectRas(int Dialup, int UseThis, int Notify, char *Name)
{
	RASDIALDLG DlgParam;
	RASCONN *RasConn;
	int i;
	int Num;
	int Sts;
	int DoDial;
	RASDIALPARAMS Param;
	BOOL Flg;
	OSVERSIONINFO VerInfo;

	Sts = SUCCESS;
	if(Dialup == YES)
	{
		if(m_hDll != NULL)
		{
			/* 現在の接続を確認 */
			DoDial = 1;
			if((Num = GetCurConnections(&RasConn)) != -1)
			{
				if(Num > 0)
				{
					DoDial = 0;
					if(UseThis == YES)
					{
						DoDial = 2;
						for(i = 0; i < Num; i++)
						{
							if(_mbscmp(RasConn[i].szEntryName, Name) == 0)
								DoDial = 0;
						}

						if(DoDial == 2)
						{
							if((Notify == NO) ||
							   (DialogBox(GetFtpInst(), MAKEINTRESOURCE(rasreconnect_dlg), GetMainHwnd(), ExeEscDialogProc) == YES))
							{
								DoDisconnect(RasConn, Num);
							}
							else
								DoDial = 0;
						}
					}
				}
				free(RasConn);
			}

			if(DoDial != 0)
			{
				/* 接続する */
				SetTaskMsg(MSGJPN221);
				Sts = FAIL;

				Num = 0;
				VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
				if(GetVersionEx(&VerInfo) == TRUE)
				{
					if(VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
						Num = 1;
				}

				if(Num == 1)
				{
					if(m_hDll2 != NULL)
					{
						/* Windows NT */
						DlgParam.dwSize = sizeof(RASDIALDLG);
						DlgParam.hwndOwner = GetMainHwnd();
						DlgParam.dwFlags = 0;
						DlgParam.dwSubEntry = 0;
						DlgParam.reserved = 0;
						DlgParam.reserved2 = 0;
						if((*m_RasDialDlg)(NULL, Name, NULL, &DlgParam) != 0)
							Sts = SUCCESS;
					}
					else
						SetTaskMsg(MSGJPN222);
				}
				else
				{
					/* Windows 95,98 */
					Param.dwSize = sizeof(RASDIALPARAMS);
					strcpy(Param.szEntryName, Name);
					Flg = TRUE;
					Sts = (*m_RasGetEntryDialParams)(NULL, &Param, &Flg);
					strcpy(Param.szPhoneNumber, "");

					if(((strlen(Param.szUserName) != 0) && (strlen(Param.szPassword) != 0)) ||
					   (DialogBoxParam(GetFtpInst(), MAKEINTRESOURCE(dial_password_dlg), GetMainHwnd(), (DLGPROC)DialPassCallBackProc, (LPARAM)&Param) == YES))
					{
						if(DialogBoxParam(GetFtpInst(), MAKEINTRESOURCE(dial_dlg), GetMainHwnd(), (DLGPROC)DialCallBackProc, (LPARAM)&Param) == YES)
							Sts = SUCCESS;
					}
				}
			}
		}
	}
	return(Sts);
}