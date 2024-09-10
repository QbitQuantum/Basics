// IDYES    - Close All consoles
// IDNO     - Close active console only
// IDCANCEL - As is
int ConfirmCloseConsoles(const ConfirmCloseParam& Parm)
{
	DontEnable de;

	wchar_t szText[512], *pszText;
	int nBtn = IDCANCEL;

	static LONG lCounter = 0;
	LONG l = InterlockedIncrement(&lCounter);
	if (l > 1)
	{
		if (l == 2)
		{
			_ASSERTE(FALSE && "Confirm stack overflow!");
		}
		goto wrap;
	}

	if (Parm.rpLeaveConEmuOpened) *Parm.rpLeaveConEmuOpened = false;

	// Use TaskDialog?
	if (gOSVer.dwMajorVersion >= 6)
	{
		// must be already initialized: CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		wchar_t szMessage[128];
		if (Parm.asSingleConsole)
			lstrcpyn(szMessage, Parm.asSingleConsole, countof(szMessage));
		else if (Parm.bForceKill)
			wcscpy_c(szMessage, L"Confirm killing?");
		else if (Parm.bGroup)
			wcscpy_c(szMessage, L"Confirm closing group?");
		else
			wcscpy_c(szMessage, L"Confirm closing?");

		wchar_t szWWW[MAX_PATH]; _wsprintf(szWWW, SKIPLEN(countof(szWWW)) L"<a href=\"%s\">%s</a>", gsHomePage, gsHomePage);

		wchar_t szCloseAll[MAX_PATH*2]; wchar_t *pszText;
		if (Parm.asSingleConsole)
		{
			wcscpy_c(szCloseAll, L"Yes\n");
			pszText = szCloseAll + _tcslen(szCloseAll);
			lstrcpyn(pszText, Parm.asSingleTitle, min(MAX_PATH,(countof(szCloseAll)-(pszText-szCloseAll))));
			pszText += _tcslen(pszText);
		}
		else
		{
			_wsprintf(szCloseAll, SKIPLEN(countof(szCloseAll))
				(Parm.bGroup && (Parm.nConsoles>1))
					? ((Parm.bGroup == ConfirmCloseParam::eGroup)
						? L"Close group (%u consoles)"
						: L"Close (%u consoles)")
					: (Parm.nConsoles>1)
						? L"Close all %u consoles."
						: L"Close %u console.",
				Parm.nConsoles);
			pszText = szCloseAll + _tcslen(szCloseAll);
		}
		if ((Parm.asSingleConsole == NULL) || (Parm.nOperations || Parm.nUnsavedEditors))
		{
			//if (nOperations)
			{
				_wsprintf(pszText, SKIPLEN(countof(szCloseAll)-(pszText-szCloseAll)) L"\nIncomplete operations: %i", Parm.nOperations);
				pszText += _tcslen(pszText);
			}
			//if (nUnsavedEditors)
			{
				_wsprintf(pszText, SKIPLEN(countof(szCloseAll)-(pszText-szCloseAll)) L"\nUnsaved editor windows: %i", Parm.nUnsavedEditors);
				pszText += _tcslen(pszText);
			}
		}

		wchar_t szCloseOne[MAX_PATH];
		wcscpy_c(szCloseOne, L"Close active console only");
		if (Parm.nConsoles > 1)
		{
			CVConGuard VCon;
			int iCon = gpConEmu->GetActiveVCon(&VCon);
			if (iCon >= 0)
			{
				pszText = szCloseOne + _tcslen(szCloseOne);
				_wsprintf(pszText, SKIPLEN(countof(szCloseOne)-(pszText-szCloseOne)) L"\n#%u: ", (iCon+1));
				pszText += _tcslen(pszText);
				lstrcpyn(pszText, VCon->RCon()->GetTitle(true), countof(szCloseOne)-(pszText-szCloseOne));
			}
		}

		const wchar_t* szCancel = L"Cancel\nDon't close anything";


		int nButtonPressed                  = 0;
		TASKDIALOGCONFIG config             = {sizeof(config)};
		TASKDIALOG_BUTTON buttons[]   = {
			{ IDYES,    szCloseAll },
			{ IDNO,     szCloseOne },
			{ IDCANCEL, szCancel },
		};
		config.cButtons                     = countof(buttons);
		if (Parm.nConsoles <= 1)
		{
			buttons[1] = buttons[2];
			config.cButtons--;
		}

		config.hwndParent                   = ghWnd;
		config.hInstance                    = NULL /*g_hInstance*/;
		config.dwFlags                      = TDF_USE_HICON_MAIN|TDF_USE_COMMAND_LINKS|TDF_ALLOW_DIALOG_CANCELLATION
		                                      |TDF_ENABLE_HYPERLINKS; //|TDIF_SIZE_TO_CONTENT|TDF_CAN_BE_MINIMIZED;
		//config.pszMainIcon                  = MAKEINTRESOURCE(IDI_ICON1);
		config.hMainIcon                    = hClassIcon;
		config.pszWindowTitle               = gpConEmu->GetDefaultTitle();
		config.pszMainInstruction           = szMessage;
		//config.pszContent                 = L"...";
		config.pButtons                     = buttons;
		config.nDefaultButton               = IDYES;
		config.pszFooter                    = szWWW;

		//{
		//	config.dwFlags |= TDF_VERIFICATION_FLAG_CHECKED;
		//	config.pszVerificationText = L"Text on checkbox";
		//}

		HRESULT hr = TaskDialog(&config, &nButtonPressed, NULL, NULL);

		if (hr == S_OK)
		{
			switch (nButtonPressed)
			{
			case IDCANCEL: // user cancelled the dialog
			case IDYES:
			case IDNO:
				nBtn = nButtonPressed;
				goto wrap;

			default:
				_ASSERTE(nButtonPressed==IDCANCEL||nButtonPressed==IDYES||nButtonPressed==IDNO);
				break; // should never happen
			}
		}
	}

	// Иначе - через стандартный MessageBox

	if (Parm.asSingleConsole)
	{
		lstrcpyn(szText,
			Parm.asSingleConsole ? Parm.asSingleConsole : Parm.bForceKill ? L"Confirm killing?" : L"Confirm closing?",
			min(128,countof(szText)));
		wcscat_c(szText, L"\r\n\r\n");
		int nLen = lstrlen(szText);
		lstrcpyn(szText+nLen, Parm.asSingleTitle, countof(szText)-nLen);
	}
	else
	{
		_wsprintf(szText, SKIPLEN(countof(szText)) L"About to close %u console%s.\r\n", Parm.nConsoles, (Parm.nConsoles>1)?L"s":L"");
	}
	pszText = szText+_tcslen(szText);

	if (Parm.nOperations || Parm.nUnsavedEditors)
	{
		*(pszText++) = L'\r'; *(pszText++) = L'\n'; *(pszText) = 0;

		if (Parm.nOperations)
		{
			_wsprintf(pszText, SKIPLEN(countof(szText)-(pszText-szText)) L"Incomplete operations: %i\r\n", Parm.nOperations);
			pszText += _tcslen(pszText);
		}
		if (Parm.nUnsavedEditors)
		{
			_wsprintf(pszText, SKIPLEN(countof(szText)-(pszText-szText)) L"Unsaved editor windows: %i\r\n", Parm.nUnsavedEditors);
			pszText += _tcslen(pszText);
		}
	}

	if (Parm.nConsoles > 1)
	{
		wcscat_c(szText,
			L"\r\nPress button <No> to close active console only\r\n"
			L"\r\nProceed with close ConEmu?");
	}

	nBtn = MsgBox(szText, (/*rpPanes ? MB_OKCANCEL :*/ (Parm.nConsoles>1) ? MB_YESNOCANCEL : MB_OKCANCEL)|MB_ICONEXCLAMATION,
		gpConEmu->GetDefaultTitle(), ghWnd);

	if (nBtn == IDOK)
	{
		nBtn = IDYES; // для однозначности
	}

wrap:
	InterlockedDecrement(&lCounter);
	return nBtn;
}