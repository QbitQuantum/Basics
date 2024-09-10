static INT_PTR CALLBACK CheckOptionsFastProc(HWND hDlg, UINT messg, WPARAM wParam, LPARAM lParam)
{
	switch (messg)
	{
	case WM_SETHOTKEY:
		gnWndSetHotkey = wParam;
		break;

	case WM_INITDIALOG:
		{
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hClassIcon);
			SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hClassIconSm);

			LRESULT lbRc = FALSE;
			if (lParam)
			{
				SetWindowText(hDlg, (LPCWSTR)lParam);
			}
			else
			{
				wchar_t szTitle[512];
				wcscpy_c(szTitle, gpConEmu->GetDefaultTitle());
				wcscat_c(szTitle, L" fast configuration");
				SetWindowText(hDlg, szTitle);
			}


			// lbStorageLocation
			SettingsStorage Storage = {}; bool ReadOnly = false;
			gpSet->GetSettingsType(Storage, ReadOnly);
			wchar_t* pszSettingsPlaces[] = {
				lstrdup(L"HKEY_CURRENT_USER\\Software\\ConEmu"),
				ExpandEnvStr(L"%APPDATA%\\ConEmu.xml"),
				ExpandEnvStr(L"%ConEmuBaseDir%\\ConEmu.xml"),
				ExpandEnvStr(L"%ConEmuDir%\\ConEmu.xml"),
				NULL
			};
			int iAllowed = 0;
			if (lstrcmp(Storage.szType, CONEMU_CONFIGTYPE_XML) == 0)
			{
				iAllowed = 1; // Реестр уже низя
				if (Storage.pszFile)
				{
					if (lstrcmpi(Storage.pszFile, pszSettingsPlaces[1]) == 0)
						iAllowed = 1; // OK, перебить может любой другой xml
					else if (lstrcmpi(Storage.pszFile, pszSettingsPlaces[2]) == 0)
						iAllowed = 2; // "Перебить" может только %APPDATA%
					else if (lstrcmpi(Storage.pszFile, pszSettingsPlaces[3]) == 0)
						iAllowed = 3; // Приоритетнее настроек нет
					else
					{
						// Этот xml мог быть указан в "/LoadCfgFile ..."
						SafeFree(pszSettingsPlaces[3]);
						pszSettingsPlaces[3] = lstrdup(Storage.pszFile);
						iAllowed = 3; // Приоритетнее настроек нет
					}
				}
			}
			while (pszSettingsPlaces[iAllowed])
			{
				SendDlgItemMessage(hDlg, lbStorageLocation, CB_ADDSTRING, 0, (LPARAM)pszSettingsPlaces[iAllowed]);
				iAllowed++;
			}
			SendDlgItemMessage(hDlg, lbStorageLocation, CB_SETCURSEL, 0, 0);
			for (int i = 0; pszSettingsPlaces[i]; i++)
			{
				SafeFree(pszSettingsPlaces[i]);
			}


			// continue
			CheckDlgButton(hDlg, cbSingleInstance, gpSetCls->IsSingleInstanceArg());

			CheckDlgButton(hDlg, cbUseKeyboardHooksFast, gpSet->isKeyboardHooks(true));

			

			// Debug purposes only. ConEmu.exe switch "/nokeyhooks"
			#ifdef _DEBUG
			EnableWindow(GetDlgItem(hDlg, cbUseKeyboardHooksFast), !gpConEmu->DisableKeybHooks);
			#endif

			CheckDlgButton(hDlg, cbInjectConEmuHkFast, gpSet->isUseInjects);

			if (!gpConEmu->isUpdateAllowed())
			{
				EnableWindow(GetDlgItem(hDlg, cbEnableAutoUpdateFast), FALSE);
				EnableWindow(GetDlgItem(hDlg, rbAutoUpdateStableFast), FALSE);
				EnableWindow(GetDlgItem(hDlg, rbAutoUpdatePreviewFast), FALSE);
				EnableWindow(GetDlgItem(hDlg, rbAutoUpdateDeveloperFast), FALSE);
				EnableWindow(GetDlgItem(hDlg, stEnableAutoUpdateFast), FALSE);
			}
			else
			{
				if (gpSet->UpdSet.isUpdateUseBuilds != 0)
					CheckDlgButton(hDlg, cbEnableAutoUpdateFast, gpSet->UpdSet.isUpdateCheckOnStartup|gpSet->UpdSet.isUpdateCheckHourly);
				CheckRadioButton(hDlg, rbAutoUpdateStableFast, rbAutoUpdateDeveloperFast,
					(gpSet->UpdSet.isUpdateUseBuilds == 1) ? rbAutoUpdateStableFast :
					(gpSet->UpdSet.isUpdateUseBuilds == 3) ? rbAutoUpdatePreviewFast : rbAutoUpdateDeveloperFast);
			}

			if (!bCheckIme)
			{
				ShowWindow(GetDlgItem(hDlg, gbDisableConImeFast), SW_HIDE);
				ShowWindow(GetDlgItem(hDlg, cbDisableConImeFast), SW_HIDE);
				ShowWindow(GetDlgItem(hDlg, stDisableConImeFast1), SW_HIDE);
				ShowWindow(GetDlgItem(hDlg, stDisableConImeFast2), SW_HIDE);
				ShowWindow(GetDlgItem(hDlg, stDisableConImeFast3), SW_HIDE);
				RECT rcGroup, rcBtn, rcWnd;
				if (GetWindowRect(GetDlgItem(hDlg, gbDisableConImeFast), &rcGroup))
				{
					int nShift = (rcGroup.bottom-rcGroup.top);

					HWND h = GetDlgItem(hDlg, IDOK);
					GetWindowRect(h, &rcBtn); MapWindowPoints(NULL, hDlg, (LPPOINT)&rcBtn, 2);
					SetWindowPos(h, NULL, rcBtn.left, rcBtn.top - nShift, 0,0, SWP_NOSIZE|SWP_NOZORDER);
					
					h = GetDlgItem(hDlg, IDCANCEL);
					GetWindowRect(h, &rcBtn); MapWindowPoints(NULL, hDlg, (LPPOINT)&rcBtn, 2);
					SetWindowPos(h, NULL, rcBtn.left, rcBtn.top - nShift, 0,0, SWP_NOSIZE|SWP_NOZORDER);

					h = GetDlgItem(hDlg, stHomePage);
					GetWindowRect(h, &rcBtn); MapWindowPoints(NULL, hDlg, (LPPOINT)&rcBtn, 2);
					SetWindowPos(h, NULL, rcBtn.left, rcBtn.top - nShift, 0,0, SWP_NOSIZE|SWP_NOZORDER);

					GetWindowRect(hDlg, &rcWnd);
					MoveWindow(hDlg, rcWnd.left, rcWnd.top+(nShift>>1), rcWnd.right-rcWnd.left, rcWnd.bottom-rcWnd.top-nShift, FALSE);
				}
			}

			return lbRc;
		}