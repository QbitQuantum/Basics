INT_PTR CSetPgIntegr::PageDlgProc(HWND hDlg, UINT messg, WPARAM wParam, LPARAM lParam)
{
	static bool bSkipCbSel = FALSE;
	INT_PTR iRc = 0;

	switch (messg)
	{
	case WM_NOTIFY:
		{
			LPNMHDR phdr = (LPNMHDR)lParam;

			if (phdr->code == TTN_GETDISPINFO)
			{
				return gpSetCls->ProcessTipHelp(hDlg, messg, wParam, lParam);
			}

			break;
		}
	case WM_INITDIALOG:
		{
			bSkipCbSel = true;

			PageDlgProc(hDlg, UM_RELOAD_HERE_LIST, UM_RELOAD_HERE_LIST, 0);

			//-- moved to "ComSpec" page
			//PageDlgProc(hDlg, UM_RELOAD_AUTORUN, UM_RELOAD_AUTORUN, 0);

			// Возвращает NULL, если строка пустая
			wchar_t* pszCurInside = GetDlgItemTextPtr(hDlg, cbInsideName);
			_ASSERTE((pszCurInside==NULL) || (*pszCurInside!=0));
			wchar_t* pszCurHere   = GetDlgItemTextPtr(hDlg, cbHereName);
			_ASSERTE((pszCurHere==NULL) || (*pszCurHere!=0));

			wchar_t szIcon[MAX_PATH+32];
			_wsprintf(szIcon, SKIPLEN(countof(szIcon)) L"%s,0", gpConEmu->ms_ConEmuExe);

			if (pszCurInside)
			{
				bSkipCbSel = false;
				PageDlgProc(hDlg, WM_COMMAND, MAKELONG(cbInsideName,CBN_SELCHANGE), 0);
				bSkipCbSel = true;
			}
			else
			{
				SetDlgItemText(hDlg, cbInsideName, L"ConEmu Inside");
				SetDlgItemText(hDlg, tInsideConfig, L"shell");
				SetDlgItemText(hDlg, tInsideShell, CONEMU_HERE_POSH);
				//SetDlgItemText(hDlg, tInsideIcon, szIcon);
				SetDlgItemText(hDlg, tInsideIcon, L"powershell.exe");
				checkDlgButton(hDlg, cbInsideSyncDir, gpConEmu->mp_Inside && gpConEmu->mp_Inside->mb_InsideSynchronizeCurDir);
				SetDlgItemText(hDlg, tInsideSyncDir, L""); // Auto
			}

			if (pszCurHere)
			{
				bSkipCbSel = false;
				PageDlgProc(hDlg, WM_COMMAND, MAKELONG(cbHereName,CBN_SELCHANGE), 0);
				bSkipCbSel = true;
			}
			else
			{
				SetDlgItemText(hDlg, cbHereName, L"ConEmu Here");
				SetDlgItemText(hDlg, tHereConfig, L"");
				SetDlgItemText(hDlg, tHereShell, CONEMU_HERE_CMD);
				SetDlgItemText(hDlg, tHereIcon, szIcon);
			}

			bSkipCbSel = false;

			SafeFree(pszCurInside);
			SafeFree(pszCurHere);

		}
		break; // WM_INITDIALOG

	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			{
				WORD CB = LOWORD(wParam);

				switch (CB)
				{
				case cbInsideSyncDir:
					if (gpConEmu->mp_Inside)
					{
						gpConEmu->mp_Inside->mb_InsideSynchronizeCurDir = isChecked(hDlg, CB);
					}
					break;
				case bInsideRegister:
				case bInsideUnregister:
					ShellIntegration(hDlg, ShellIntgr_Inside, CB==bInsideRegister);
					PageDlgProc(hDlg, UM_RELOAD_HERE_LIST, UM_RELOAD_HERE_LIST, 0);
					if (CB==bInsideUnregister)
						PageDlgProc(hDlg, WM_COMMAND, MAKELONG(cbInsideName,CBN_SELCHANGE), 0);
					break;
				case bHereRegister:
				case bHereUnregister:
					ShellIntegration(hDlg, ShellIntgr_Here, CB==bHereRegister);
					PageDlgProc(hDlg, UM_RELOAD_HERE_LIST, UM_RELOAD_HERE_LIST, 0);
					if (CB==bHereUnregister)
						PageDlgProc(hDlg, WM_COMMAND, MAKELONG(cbHereName,CBN_SELCHANGE), 0);
					break;
				}
			}
			break; // BN_CLICKED
		case EN_CHANGE:
			{
				WORD EB = LOWORD(wParam);
				switch (EB)
				{
				case tInsideSyncDir:
					if (gpConEmu->mp_Inside)
					{
						SafeFree(gpConEmu->mp_Inside->ms_InsideSynchronizeCurDir);
						gpConEmu->mp_Inside->ms_InsideSynchronizeCurDir = GetDlgItemTextPtr(hDlg, tInsideSyncDir);
					}
					break;
				}
			}
			break; // EN_CHANGE
		case CBN_SELCHANGE:
			{
				WORD CB = LOWORD(wParam);
				switch (CB)
				{
				case cbInsideName:
				case cbHereName:
					if (!bSkipCbSel)
					{
						wchar_t *pszCfg = NULL, *pszIco = NULL, *pszFull = NULL, *pszDirSync = NULL;
						LPCWSTR pszCmd = NULL;
						INT_PTR iSel = SendDlgItemMessage(hDlg, CB, CB_GETCURSEL, 0,0);
						if (iSel >= 0)
						{
							INT_PTR iLen = SendDlgItemMessage(hDlg, CB, CB_GETLBTEXTLEN, iSel, 0);
							size_t cchMax = iLen+128;
							wchar_t* pszName = (wchar_t*)calloc(cchMax,sizeof(*pszName));
							if ((iLen > 0) && pszName)
							{
								_wcscpy_c(pszName, cchMax, L"Directory\\shell\\");
								SendDlgItemMessage(hDlg, CB, CB_GETLBTEXT, iSel, (LPARAM)(pszName+_tcslen(pszName)));

								HKEY hkShell = NULL;
								if (0 == RegOpenKeyEx(HKEY_CLASSES_ROOT, pszName, 0, KEY_READ, &hkShell))
								{
									DWORD nType;
									DWORD nSize = MAX_PATH*2*sizeof(wchar_t);
									pszIco = (wchar_t*)calloc(nSize+2,1);
									if (0 != RegQueryValueEx(hkShell, L"Icon", NULL, &nType, (LPBYTE)pszIco, &nSize) || nType != REG_SZ)
										SafeFree(pszIco);
									HKEY hkCmd = NULL;
									if (0 == RegOpenKeyEx(hkShell, L"command", 0, KEY_READ, &hkCmd))
									{
										DWORD nSize = MAX_PATH*8*sizeof(wchar_t);
										pszFull = (wchar_t*)calloc(nSize+2,1);
										if (0 != RegQueryValueEx(hkCmd, NULL, NULL, &nType, (LPBYTE)pszFull, &nSize) || nType != REG_SZ)
										{
											SafeFree(pszIco);
										}
										else
										{
											LPCWSTR psz = pszFull;
											LPCWSTR pszPrev = pszFull;
											CEStr szArg;
											while (0 == NextArg(&psz, szArg, &pszPrev))
											{
												if (*szArg != L'/')
													continue;

												if ((lstrcmpi(szArg, L"/inside") == 0)
													|| (lstrcmpi(szArg, L"/here") == 0)
													)
												{
													// Nop
												}
												else if (lstrcmpni(szArg, L"/inside=", 8) == 0)
												{
													pszDirSync = lstrdup(szArg+8); // may be empty!
												}
												else if (lstrcmpi(szArg, L"/config") == 0)
												{
													if (0 != NextArg(&psz, szArg))
														break;
													pszCfg = lstrdup(szArg);
												}
												else if (lstrcmpi(szArg, L"/dir") == 0)
												{
													if (0 != NextArg(&psz, szArg))
														break;
													_ASSERTE(lstrcmpi(szArg, L"%1")==0);
												}
												else //if (lstrcmpi(szArg, L"/cmd") == 0)
												{
													if (lstrcmpi(szArg, L"/cmd") == 0)
														pszCmd = psz;
													else
														pszCmd = pszPrev;
													break;
												}
											}
										}
										RegCloseKey(hkCmd);
									}
									RegCloseKey(hkShell);
								}
							}
							SafeFree(pszName);
						}

						SetDlgItemText(hDlg, (CB==cbInsideName) ? tInsideConfig : tHereConfig,
							pszCfg ? pszCfg : L"");
						SetDlgItemText(hDlg, (CB==cbInsideName) ? tInsideShell : tHereShell,
							pszCmd ? pszCmd : L"");
						SetDlgItemText(hDlg, (CB==cbInsideName) ? tInsideIcon : tHereIcon,
							pszIco ? pszIco : L"");

						if (CB==cbInsideName)
						{
							SetDlgItemText(hDlg, tInsideSyncDir, pszDirSync ? pszDirSync : L"");
							checkDlgButton(hDlg, cbInsideSyncDir, (pszDirSync && *pszDirSync) ? BST_CHECKED : BST_UNCHECKED);
						}

						SafeFree(pszCfg);
						SafeFree(pszFull);
						SafeFree(pszIco);
						SafeFree(pszDirSync);
					}
					break;
				}
			}
			break; // CBN_SELCHANGE
		} // switch (HIWORD(wParam))
		break; // WM_COMMAND

	case UM_RELOAD_HERE_LIST:
		if (wParam == UM_RELOAD_HERE_LIST)
		{
			HKEY hkDir = NULL;
			size_t cchCmdMax = 65535;
			wchar_t* pszCmd = (wchar_t*)calloc(cchCmdMax,sizeof(*pszCmd));
			if (!pszCmd)
				break;

			// Возвращает NULL, если строка пустая
			wchar_t* pszCurInside = GetDlgItemTextPtr(hDlg, cbInsideName);
			_ASSERTE((pszCurInside==NULL) || (*pszCurInside!=0));
			wchar_t* pszCurHere   = GetDlgItemTextPtr(hDlg, cbHereName);
			_ASSERTE((pszCurHere==NULL) || (*pszCurHere!=0));

			bool lbOldSkip = bSkipCbSel; bSkipCbSel = true;

			SendDlgItemMessage(hDlg, cbInsideName, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(hDlg, cbHereName, CB_RESETCONTENT, 0, 0);

			if (0 == RegOpenKeyEx(HKEY_CLASSES_ROOT, L"Directory\\shell", 0, KEY_READ, &hkDir))
			{
				for (DWORD i = 0; i < 512; i++)
				{
					wchar_t szName[MAX_PATH+32] = {};
					DWORD cchMax = countof(szName) - 32;
					if (0 != RegEnumKeyEx(hkDir, i, szName, &cchMax, NULL, NULL, NULL, NULL))
						break;
					wchar_t* pszSlash = szName + _tcslen(szName);
					wcscat_c(szName, L"\\command");
					HKEY hkCmd = NULL;
					if (0 == RegOpenKeyEx(hkDir, szName, 0, KEY_READ, &hkCmd))
					{
						DWORD cbMax = (cchCmdMax-2) * sizeof(*pszCmd);
						if (0 == RegQueryValueEx(hkCmd, NULL, NULL, NULL, (LPBYTE)pszCmd, &cbMax))
						{
							pszCmd[cbMax>>1] = 0;
							*pszSlash = 0;
							LPCWSTR pszInside = StrStrI(pszCmd, L"/inside");
							LPCWSTR pszConEmu = StrStrI(pszCmd, L"conemu");
							if (pszConEmu)
							{
								SendDlgItemMessage(hDlg,
									pszInside ? cbInsideName : cbHereName,
									CB_ADDSTRING, 0, (LPARAM)szName);
								if ((pszInside ? pszCurInside : pszCurHere) == NULL)
								{
									if (pszInside)
										pszCurInside = lstrdup(szName);
									else
										pszCurHere = lstrdup(szName);
								}
							}
						}
						RegCloseKey(hkCmd);
					}
				}
				RegCloseKey(hkDir);
			}