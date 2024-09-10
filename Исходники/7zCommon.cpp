/**
 * @brief DLGPROC for C7ZipMismatchException's ReportError() popup.
 */
INT_PTR CALLBACK C7ZipMismatchException::DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			theApp.TranslateDialog(hWnd);
			if (GetDlgItem(hWnd, 9001) == NULL)
			{
				// Dialog template isn't up to date. Give it a second chance.
				EndDialog(hWnd, -1);
				return FALSE;
			}
			C7ZipMismatchException *pThis = (C7ZipMismatchException *)lParam;
			CRawString<TCHAR,2600> cText;
			CRawString<TCHAR,80> cPresent, cMissing, cOutdated, cNone, cPlugin;
			if (pThis->m_pCause)
			{
				pThis->m_pCause->GetErrorMessage(cText.Data, cText.Size);
				SetDlgItemText(hWnd, 107, cText.Data);
			}
			else
			{
				GetDlgItemText(hWnd, 107, cText.Data, cText.Size);
				switch (GetOptionsMgr()->GetInt(OPT_ARCHIVE_ENABLE))
				{
				case 0:
					lstrcat(cText.Data, theApp.LoadString(IDS_MERGE7Z_ENABLE_0).c_str());
					break;
				case 2:
					lstrcat(cText.Data, theApp.LoadString(IDS_MERGE7Z_ENABLE_2).c_str());
					break;
				}
				SetDlgItemText(hWnd, 107, cText.Data);
			}
			GetDlgItemText(hWnd, 112, cPresent.Data, cPresent.Size);
			GetDlgItemText(hWnd, 122, cMissing.Data, cMissing.Size);
			GetDlgItemText(hWnd, 132, cOutdated.Data, cOutdated.Size);
			GetDlgItemText(hWnd, 120, cNone.Data, cNone.Size);
			GetDlgItemText(hWnd, 102, cPlugin.Data, cPlugin.Size);
			wsprintf(cText.Data, cPlugin.Data, DllBuild_Merge7z);
			SetDlgItemText(hWnd, 102, cText.Data);
			SetDlgItemText
			(
				hWnd, 109,
				(
					pThis->m_dwVer7zRecommended == pThis->m_dwVer7zInstalled
				||	pThis->m_dwVer7zRecommended == pThis->m_dwVer7zLocal
				) ? cPresent.Data : cMissing.Data
			);
			DWORD dwDllBuild = FormatVersion(cText.Data, cPlugin.Data, pThis->m_dwVer7zRecommended);
			SetDlgItemText(hWnd, 110, *cText.Data ? cText.Data : cNone.Data);
			SetDlgItemText(hWnd, 111, cPlugin.Data);
			SetDlgItemText(hWnd, 112, *cPlugin.Data == '\0' ? cPlugin.Data :
				dwDllBuild == ~0 ? cMissing.Data : dwDllBuild < DllBuild_Merge7z ? cOutdated.Data : cPresent.Data);
			dwDllBuild = FormatVersion(cText.Data, cPlugin.Data, pThis->m_dwVer7zInstalled);
			SetDlgItemText(hWnd, 120, *cText.Data ? cText.Data : cNone.Data);
			SetDlgItemText(hWnd, 121, cPlugin.Data);
			SetDlgItemText(hWnd, 122, *cPlugin.Data == '\0' ? cPlugin.Data :
				dwDllBuild == ~0 ? cMissing.Data : dwDllBuild < DllBuild_Merge7z ? cOutdated.Data : cPresent.Data);
			dwDllBuild = FormatVersion(cText.Data, cPlugin.Data, pThis->m_dwVer7zLocal);
			SetDlgItemText(hWnd, 130, *cText.Data ? cText.Data : cNone.Data);
			SetDlgItemText(hWnd, 131, cPlugin.Data);
			SetDlgItemText(hWnd, 132, *cPlugin.Data == '\0' ? cPlugin.Data :
				dwDllBuild == ~0 ? cMissing.Data : dwDllBuild < DllBuild_Merge7z ? cOutdated.Data : cPresent.Data);
			GetModuleFileName(0, cText.Data, MAX_PATH);
			PathRemoveFileSpec(cText.Data);
			PathAppend(cText.Data, _T("Merge7z*.dll"));
			DlgDirListDLLs(hWnd, cText.Data, 105);
			if (DWORD cchPath = GetEnvironmentVariable(_T("path"), 0, 0))
			{
				static const TCHAR cSep[] = _T(";");
				LPTSTR pchPath = new TCHAR[cchPath];
				GetEnvironmentVariable(_T("PATH"), pchPath, cchPath);
				LPTSTR pchItem = pchPath;
				while (int cchItem = StrCSpn(pchItem += StrSpn(pchItem, cSep), cSep))
				{
					if (cchItem < MAX_PATH)
					{
						CopyMemory(cText.Data, pchItem, cchItem*sizeof*pchItem);
						cText.Data[cchItem] = 0;
						PathAppend(cText.Data, _T("Merge7z*.dll"));
						DlgDirListDLLs(hWnd, cText.Data, 105);
					}
					pchItem += cchItem;
				}
				delete[] pchPath;
			}
			if (SendDlgItemMessage(hWnd, 105, LB_GETCOUNT, 0, 0) == 0)
			{
				SendDlgItemMessage(hWnd, 105, LB_ADDSTRING, 0, (LPARAM) cNone.Data);
			}
			HICON hIcon = LoadIcon(0, IDI_EXCLAMATION);
			SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
			if (pThis->m_bShowAllways)
			{
				ShowWindow(GetDlgItem(hWnd, 106), SW_HIDE);
			}
		} return TRUE;
		case WM_DRAWITEM:
		{
			switch (wParam)
			{
			case 108:
				CDrawItemStruct::From(lParam)->DrawWebLinkButton();
				break;
			}
		} return TRUE;
		case WM_SETCURSOR:
		{
			HCURSOR hCursor = 0;
			switch (GetDlgCtrlID((HWND)wParam))
			{
			case 108:
				hCursor = CommCtrl_LoadCursor(MAKEINTRESOURCE(108));
				break;
			}
			if (hCursor)
			{
				SetCursor(hCursor);
				SetWindowLongPtr(hWnd, DWLP_MSGRESULT, 1);
				return TRUE;
			}
		} return FALSE;
		case WM_COMMAND:
		{
			switch (wParam)
			{
				case IDOK:
				case IDCANCEL:
				{
					int nDontShowAgain = SendDlgItemMessage(hWnd, 106, BM_GETCHECK, 0, 0);
					EndDialog(hWnd, MAKEWORD(IDOK, nDontShowAgain));
				} break;
				case 108:
				{
					HINSTANCE h = ShellExecute(hWnd, _T("open"), m_strDownloadURL, 0, 0, SW_SHOWNORMAL);
					if ((UINT)h > 32)
					{
						LONG lStyle = ::GetWindowLong((HWND)lParam, GWL_STYLE);
						::SetWindowLong((HWND)lParam, GWL_STYLE, lStyle|BS_LEFTTEXT);
						::InvalidateRect((HWND)lParam, 0, TRUE);
					}
					else
					{
						MessageBeep(0);
					}
				} break;
			}
		} return TRUE;
	}
	return FALSE;
}