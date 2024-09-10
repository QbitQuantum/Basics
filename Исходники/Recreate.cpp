INT_PTR CRecreateDlg::OnInitDialog(HWND hDlg, UINT messg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lbRc = FALSE;

	gpConEmu->OnOurDialogOpened();

	// Visual
	SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hClassIcon);
	SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hClassIconSm);

	// Set password style (avoid "bars" on some OS)
	SendDlgItemMessage(hDlg, tRunAsPassword, WM_SETFONT, (LPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), 0);

	// Add menu items
	HMENU hSysMenu = GetSystemMenu(hDlg, FALSE);
	InsertMenu(hSysMenu, 0, MF_BYPOSITION, MF_SEPARATOR, 0);
	InsertMenu(hSysMenu, 0, MF_BYPOSITION | MF_STRING | MF_ENABLED,
				ID_RESETCMDHISTORY, L"Clear history...");
	InsertMenu(hSysMenu, 0, MF_BYPOSITION | MF_STRING | MF_ENABLED
				| (gpSet->isSaveCmdHistory ? MF_CHECKED : 0),
				ID_STORECMDHISTORY, L"Store history");

	//#ifdef _DEBUG
	//SetWindowPos(ghOpWnd, HWND_NOTOPMOST, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
	//#endif

	RConStartArgs* pArgs = mp_Args;
	_ASSERTE(pArgs);

	// Fill command and task drop down
	SendMessage(hDlg, UM_FILL_CMDLIST, TRUE, 0);

	// Set text in command and folder fields
	SetDlgItemText(hDlg, IDC_RESTART_CMD, mpsz_DefCmd ? mpsz_DefCmd : pArgs->pszSpecialCmd ? pArgs->pszSpecialCmd : L"");

	// Current directory, startup directory, ConEmu startup directory, and may be startup directory history in the future
	AddDirectoryList(mpsz_DefDir ? mpsz_DefDir : pArgs->pszStartupDir);
	AddDirectoryList(ms_RConCurDir);
	AddDirectoryList(ms_RConStartDir);
	AddDirectoryList(gpConEmu->WorkDir());
	LPCWSTR pszShowDir;
	if ((pArgs->aRecreate == cra_RecreateTab) && !ms_RConCurDir.IsEmpty())
		pszShowDir = ms_RConCurDir;
	else
		pszShowDir = mpsz_DefDir ? mpsz_DefDir : pArgs->pszStartupDir ? pArgs->pszStartupDir : gpConEmu->WorkDir();
	SetDlgItemText(hDlg, IDC_STARTUP_DIR, pszShowDir);

	// Split controls
	if (pArgs->aRecreate == cra_RecreateTab)
	{
		// Hide Split's
		ShowWindow(GetDlgItem(hDlg, gbRecreateSplit), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, rbRecreateSplitNone), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, rbRecreateSplit2Right), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, rbRecreateSplit2Bottom), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, stRecreateSplit), SW_HIDE);
		ShowWindow(GetDlgItem(hDlg, tRecreateSplit), SW_HIDE);
	}
	else
	{
		// Fill splits
		SetDlgItemInt(hDlg, tRecreateSplit, (1000-pArgs->nSplitValue)/10, FALSE);
		CheckRadioButton(hDlg, rbRecreateSplitNone, rbRecreateSplit2Bottom, rbRecreateSplitNone+pArgs->eSplit);
		EnableWindow(GetDlgItem(hDlg, tRecreateSplit), (pArgs->eSplit != pArgs->eSplitNone));
		EnableWindow(GetDlgItem(hDlg, stRecreateSplit), (pArgs->eSplit != pArgs->eSplitNone));
	}

	// Спрятать флажок "New window"
	bool bRunInNewWindow_Hidden = (pArgs->aRecreate == cra_EditTab || pArgs->aRecreate == cra_RecreateTab);
	ShowWindow(GetDlgItem(hDlg, cbRunInNewWindow), bRunInNewWindow_Hidden ? SW_HIDE : SW_SHOWNORMAL);


	const wchar_t *pszUser = pArgs->pszUserName;
	const wchar_t *pszDomain = pArgs->pszDomain;
	bool bResticted = (pArgs->RunAsRestricted == crb_On);
	int nChecked = rbCurrentUser;
	DWORD nUserNameLen = countof(ms_CurUser);

	if (!GetUserName(ms_CurUser, &nUserNameLen))
		ms_CurUser[0] = 0;

	wchar_t szRbCaption[MAX_PATH*3];
	lstrcpy(szRbCaption, L"Run as current &user: "******"UPN format" остается в pszUser
					lstrcpyn(szOtherUser, pszUser, MAX_PATH);
					wcscat_c(szOtherUser, L"@");
					lstrcpyn(szOtherUser+_tcslen(szOtherUser), pszDomain, MAX_PATH);
				}
				else
				{
					// "Старая" нотация domain\user
					lstrcpyn(szOtherUser, pszDomain, MAX_PATH);
					wcscat_c(szOtherUser, L"\\");
					lstrcpyn(szOtherUser+_tcslen(szOtherUser), pszUser, MAX_PATH);
				}
			}
			else
			{
				lstrcpyn(szOtherUser, pszUser, countof(szOtherUser));
			}

			SetDlgItemText(hDlg, tRunAsPassword, pArgs->szUserPassword);
		}
	}

	SetDlgItemText(hDlg, tRunAsUser, (nChecked == rbAnotherUser) ? szOtherUser : L"");
	CheckRadioButton(hDlg, rbCurrentUser, rbAnotherUser, nChecked);
	RecreateDlgProc(hDlg, UM_USER_CONTROLS, 0, 0);

	if (gOSVer.dwMajorVersion < 6)
	{
		// В XP и ниже это просто RunAs - с возможностью ввода имени пользователя и пароля
		//apiShowWindow(GetDlgItem(hDlg, cbRunAsAdmin), SW_HIDE);
		SetDlgItemTextA(hDlg, cbRunAsAdmin, "&Run as..."); //GCC hack. иначе не собирается
		// И уменьшить длину
		RECT rcBox; GetWindowRect(GetDlgItem(hDlg, cbRunAsAdmin), &rcBox);
		SetWindowPos(GetDlgItem(hDlg, cbRunAsAdmin), NULL, 0, 0, (rcBox.right-rcBox.left)/2, rcBox.bottom-rcBox.top,
				        SWP_NOMOVE|SWP_NOZORDER);
	}
	else if (gpConEmu->mb_IsUacAdmin || (pArgs && (pArgs->RunAsAdministrator == crb_On)))
	{
		CheckDlgButton(hDlg, cbRunAsAdmin, BST_CHECKED);

		if (gpConEmu->mb_IsUacAdmin)  // Только в Vista+ если GUI уже запущен под админом
		{
			EnableWindow(GetDlgItem(hDlg, cbRunAsAdmin), FALSE);
		}
		else //if (gOSVer.dwMajorVersion < 6)
		{
			RecreateDlgProc(hDlg, WM_COMMAND, cbRunAsAdmin, 0);
		}
	}

	//}
	SetClassLongPtr(hDlg, GCLP_HICON, (LONG_PTR)hClassIcon);

	RECT rcBtnBox = {0};
	if (pArgs->aRecreate == cra_RecreateTab)
	{
		//GCC hack. иначе не собирается
		SetDlgItemTextA(hDlg, IDC_RESTART_MSG, "About to restart console");
		SendDlgItemMessage(hDlg, IDC_RESTART_ICON, STM_SETICON, (WPARAM)LoadIcon(NULL,IDI_EXCLAMATION), 0);
		// Выровнять флажок по кнопке
		GetWindowRect(GetDlgItem(hDlg, IDC_START), &rcBtnBox);
		lbRc = TRUE;
	}
	else
	{
		//GCC hack. иначе не собирается
		SetDlgItemTextA(hDlg, IDC_RESTART_MSG,  "Create new console");

		// Если ВЫКЛЮЧЕН "Multi consoles in one window"
		// - Check & Disable "New window" checkbox
		CheckDlgButton(hDlg, cbRunInNewWindow, (pArgs->aRecreate == cra_CreateWindow || !gpSetCls->IsMulti()) ? BST_CHECKED : BST_UNCHECKED);
		EnableWindow(GetDlgItem(hDlg, cbRunInNewWindow), gpSetCls->IsMulti());

		//
		SendDlgItemMessage(hDlg, IDC_RESTART_ICON, STM_SETICON, (WPARAM)LoadIcon(NULL,IDI_QUESTION), 0);
		POINT pt = {0,0};
		MapWindowPoints(GetDlgItem(hDlg, IDC_TERMINATE), hDlg, &pt, 1);
		DestroyWindow(GetDlgItem(hDlg, IDC_TERMINATE));
		SetWindowPos(GetDlgItem(hDlg, IDC_START), NULL, pt.x, pt.y, 0,0, SWP_NOSIZE|SWP_NOZORDER);
		SetDlgItemText(hDlg, IDC_START, (pArgs->aRecreate == cra_EditTab) ? L"&Save" : L"&Start");
		DestroyWindow(GetDlgItem(hDlg, IDC_WARNING));
		// Выровнять флажок по кнопке
		GetWindowRect(GetDlgItem(hDlg, IDC_START), &rcBtnBox);
	}

	if (rcBtnBox.left)
	{
		// Выровнять флажок по кнопке
		MapWindowPoints(NULL, hDlg, (LPPOINT)&rcBtnBox, 2);
		RECT rcBox; GetWindowRect(GetDlgItem(hDlg, cbRunAsAdmin), &rcBox);
		POINT pt;
		pt.x = rcBtnBox.left - (rcBox.right - rcBox.left) - 5;
		pt.y = rcBtnBox.top + ((rcBtnBox.bottom-rcBtnBox.top) - (rcBox.bottom-rcBox.top))/2;
		SetWindowPos(GetDlgItem(hDlg, cbRunAsAdmin), NULL, pt.x, pt.y, 0,0, SWP_NOSIZE|SWP_NOZORDER);
	}

	// Correct cbRunInNewWindow position
	if (!bRunInNewWindow_Hidden)
	{
		POINT pt = {};
		MapWindowPoints(GetDlgItem(hDlg, cbRunAsAdmin), hDlg, &pt, 1);
		RECT rcBox2; GetWindowRect(GetDlgItem(hDlg, cbRunInNewWindow), &rcBox2);
		SetWindowPos(GetDlgItem(hDlg, cbRunInNewWindow), NULL,
			pt.x-(rcBox2.right-rcBox2.left), pt.y, 0,0, SWP_NOSIZE);
	}

	// Dpi aware processing at the end of sequence
	// because we done some manual control reposition
	if (mp_DpiAware)
	{
		mp_DpiAware->Attach(hDlg, ghWnd);
	}

	// Ensure, it will be "on screen"
	RECT rect; GetWindowRect(hDlg, &rect);
	RECT rcCenter = CenterInParent(rect, mh_Parent);
	MoveWindow(hDlg, rcCenter.left, rcCenter.top,
			    rect.right - rect.left, rect.bottom - rect.top, false);


	// Была отключена обработка CConEmuMain::OnFocus (лишние телодвижения)
	PostMessage(hDlg, (WM_APP+1), 0,0);


	// Default focus control
	if (pArgs->aRecreate == cra_RecreateTab)
		SetFocus(GetDlgItem(hDlg, IDC_START)); // Win+~ (Recreate tab), Focus on "Restart" button"
	else if ((pArgs->pszUserName && *pArgs->pszUserName) && !*pArgs->szUserPassword)
		SetFocus(GetDlgItem(hDlg, tRunAsPassword)); // We need password, all other fields are ready
	else
		SetFocus(GetDlgItem(hDlg, IDC_RESTART_CMD)); // Set focus in command-line field

	return lbRc;
}