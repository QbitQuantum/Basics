BOOL CAttachDlg::AttachDlgEnumWin(HWND hFind, LPARAM lParam)
{
	if (IsWindowVisible(hFind))
	{
		CAttachDlg* pDlg = (CAttachDlg*)lParam;

		// Условия?
		DWORD_PTR nStyle = GetWindowLongPtr(hFind, GWL_STYLE);
		DWORD_PTR nStyleEx = GetWindowLongPtr(hFind, GWL_EXSTYLE);
		DWORD nPID;
		if (!GetWindowThreadProcessId(hFind, &nPID))
			nPID = 0;

		bool lbCan = ((nStyle & (WS_VISIBLE/*|WS_CAPTION|WS_MAXIMIZEBOX*/)) == (WS_VISIBLE/*|WS_CAPTION|WS_MAXIMIZEBOX*/));
		if (lbCan)
		{
			// Более тщательно стили проверить
			lbCan = ((nStyle & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX) || ((nStyle & WS_THICKFRAME) == WS_THICKFRAME);
		}
		if (lbCan && nPID == GetCurrentProcessId())
			lbCan = false;
		if (lbCan && nPID == pDlg->mn_ExplorerPID)
			lbCan = false;
		if (lbCan && (nStyle & WS_CHILD))
			lbCan = false;
		if (lbCan && (nStyleEx & WS_EX_TOOLWINDOW))
			lbCan = false;
		if (lbCan && gpConEmu->isOurConsoleWindow(hFind))
			lbCan = false;
		if (lbCan && gpConEmu->mp_Inside && (hFind == gpConEmu->mp_Inside->mh_InsideParentRoot))
			lbCan = false;

		wchar_t szClass[MAX_PATH], szTitle[MAX_PATH];
		GetClassName(hFind, szClass, countof(szClass));
		GetWindowText(hFind, szTitle, countof(szTitle));

		if (gpSetCls->isAdvLogging)
		{
			wchar_t szLogInfo[MAX_PATH*3];
			_wsprintf(szLogInfo, SKIPLEN(countof(szLogInfo)) L"Attach:%s x%08X/x%08X/x%08X {%s} \"%s\"", (DWORD)hFind, nStyle, nStyleEx, szClass, szTitle);
			CVConGroup::LogString(szLogInfo);
		}

		if (lbCan)
		{
			wchar_t szPid[32], szHwnd[32], szType[16]; szPid[0] = szHwnd[0] = szType[0] = 0;
			wchar_t szExeName[MAX_PATH], szExePathName[MAX_PATH*4]; szExeName[0] = szExePathName[0] = 0;

			#ifndef ALLOW_GUI_ATTACH
			if (!isConsoleClass(szClass))
				return TRUE;
			#endif

			HWND hList = pDlg->mh_List;
			if (nPID)
			{
				_wsprintf(szPid, SKIPLEN(countof(szPid)) L"%u", nPID);
			}
			else
			{
				#ifdef _DEBUG
					wcscpy_c(szPid, L"????");
				#else
					return TRUE;
				#endif
			}

			HANDLE h;
			bool lbExeFound = false;
			int nImageBits = 32;

			#if 0
			// Так можно получить только имя файла процесса, а интересен еще и путь
			PROCESSENTRY32 pi = {sizeof(pi)};
			h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (h && h != INVALID_HANDLE_VALUE)
			{
				if (Process32First(h, &pi))
				{
					while (pi.th32ProcessID != nPID)
					{
						if (!Process32Next(h, &pi))
							pi.th32ProcessID = 0;
					}
				}
			}
			#endif

			if (pDlg->mp_ProcessData)
			{
				lbExeFound = pDlg->mp_ProcessData->GetProcessName(nPID, szExeName, countof(szExeName), szExePathName, countof(szExePathName), &nImageBits);
				if (lbExeFound)
				{
					//ListView_SetItemText(hList, nItem, alc_File, szExeName);
					//ListView_SetItemText(hList, nItem, alc_Path, szExePathName);
					if (pDlg->mb_IsWin64)
					{
						wcscat_c(szPid, (nImageBits == 64) ? L" *64" : L" *32");
					}
				}
			}

			if (!lbExeFound)
			{
				h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, nPID);
				if (h && h != INVALID_HANDLE_VALUE)
				{
					MODULEENTRY32 mi = {sizeof(mi)};
					if (Module32First(h, &mi))
					{
						//ListView_SetItemText(hList, nItem, alc_File, *mi.szModule ? mi.szModule : (wchar_t*)PointToName(mi.szExePath));
						lstrcpyn(szExeName, *mi.szModule ? mi.szModule : (wchar_t*)PointToName(mi.szExePath), countof(szExeName));
						//ListView_SetItemText(hList, nItem, alc_Path, mi.szExePath);
						lstrcpyn(szExePathName, mi.szExePath, countof(szExePathName));
						if (pDlg->mb_IsWin64)
						{
							wcscat_c(szPid, WIN3264TEST(L" *32",L" *64"));
						}
						lbExeFound = true;
					}
					else
					{
						if (pDlg->mb_IsWin64)
						{
							wcscat_c(szPid, L" *64");
						}
					}
					CloseHandle(h);
				}
				
				#ifdef _WIN64
				if (!lbExeFound)
				{
					h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32, nPID);
					if (h && h != INVALID_HANDLE_VALUE)
					{
						MODULEENTRY32 mi = {sizeof(mi)};
						if (Module32First(h, &mi))
						{
							//ListView_SetItemText(hList, nItem, alc_File, *mi.szModule ? mi.szModule : (wchar_t*)PointToName(mi.szExePath));
							lstrcpyn(szExeName, *mi.szModule ? mi.szModule : (wchar_t*)PointToName(mi.szExePath), countof(szExeName));
							//ListView_SetItemText(hList, nItem, alc_Path, mi.szExePath);
							lstrcpyn(szExePathName, mi.szExePath, countof(szExePathName));
							wcscat_c(szPid, L" *32");
						}
						CloseHandle(h);
					}
				}
				#endif
			}

			LVITEM lvi = {LVIF_TEXT|LVIF_STATE};
			lvi.state = 0;
			lvi.stateMask = LVIS_SELECTED|LVIS_FOCUSED;
			lvi.pszText = szPid;
			lvi.iItem = ListView_GetItemCount(hList); // в конец
			int nItem = ListView_InsertItem(hList, &lvi);
			ListView_SetItemState(hList, nItem, 0, LVIS_SELECTED|LVIS_FOCUSED);

			ListView_SetItemText(hList, nItem, alc_Title, szTitle);
			ListView_SetItemText(hList, nItem, alc_Class, szClass);
			
			_wsprintf(szHwnd, SKIPLEN(countof(szHwnd)) L"0x%08X", (DWORD)(((DWORD_PTR)hFind) & (DWORD)-1));
			ListView_SetItemText(hList, nItem, alc_HWND, szHwnd);

			wcscpy_c(szType, isConsoleClass(szClass) ? szTypeCon : szTypeGui);
			ListView_SetItemText(hList, nItem, alc_File, szExeName);
			ListView_SetItemText(hList, nItem, alc_Path, szExePathName);
			ListView_SetItemText(hList, nItem, alc_Type, szType);
		}
	}
	return TRUE; // Продолжить
}