bool CheckCanCreateWindow(LPCSTR lpClassNameA, LPCWSTR lpClassNameW, DWORD& dwStyle, DWORD& dwExStyle, HWND& hWndParent, BOOL& bAttachGui, BOOL& bStyleHidden)
{
	bAttachGui = FALSE;

#ifdef _DEBUG
	// "!dwStyle" добавил для shell32.dll!CExecuteApplication::_CreateHiddenDDEWindow()
	_ASSERTE(hWndParent==NULL || ghConEmuWnd == NULL || hWndParent!=ghConEmuWnd || !dwStyle);
	STARTUPINFO si = {sizeof(si)};
	GetStartupInfo(&si);

	bool lbAfxFrameOrView90 = false;
	if (lpClassNameA && (((DWORD_PTR)lpClassNameA) & ~0xFFFF))
	{
		lbAfxFrameOrView90 = lstrcmpA(lpClassNameA, "AfxFrameOrView90") == 0 || lstrcmpiA(lpClassNameA, "Xshell4:MainWnd") == 0;
	}
	else if (lpClassNameW && (((DWORD_PTR)lpClassNameW) & ~0xFFFF))
	{
		lbAfxFrameOrView90 = lstrcmpW(lpClassNameW, L"AfxFrameOrView90") == 0 || lstrcmpiW(lpClassNameW, L"Xshell4:MainWnd") == 0;
	}
	if (lbAfxFrameOrView90)
	{
		lbAfxFrameOrView90 = true;
	}
#endif

	if (gbAttachGuiClient && ghConEmuWndBack)
	{
		#ifdef _DEBUG
		WNDCLASS wc = {}; BOOL lbClass = FALSE;
		if ((lpClassNameW && ((DWORD_PTR)lpClassNameW) <= 0xFFFF))
		{
			lbClass = GetClassInfo((HINSTANCE)GetModuleHandle(NULL), lpClassNameW, &wc);
		}
		#endif

		DWORD nTID = GetCurrentThreadId();
		if ((nTID != gnHookMainThreadId) && (gnAttachGuiClientThreadId && nTID != gnAttachGuiClientThreadId))
		{
			_ASSERTEX(nTID==gnHookMainThreadId || !gnAttachGuiClientThreadId || (ghAttachGuiClient && IsWindow(ghAttachGuiClient)));
		}
		else
		{
			const DWORD dwNormalSized = (WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX); // Some applications can 'disable' Maximize button but they are still 'resizeable'
			const DWORD dwDlgSized = (WS_POPUP|WS_THICKFRAME);
			const DWORD dwSizedMask = (WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_POPUP|DS_MODALFRAME|WS_CHILDWINDOW);
			const DWORD dwNoCaptionSized = (WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX);
			// Lets check
			bool lbCanAttach =
							// Обычное окно с заголовком (0x00CF0000 or 0x00CE0000)
							((dwStyle & dwNormalSized) == dwNormalSized)
							// Диалог с ресайзом рамки (0x80040000)
							|| ((dwStyle & dwDlgSized) == dwDlgSized)
							// Обычное окно без заголовка (0xC0070080 : 0x00070000)
							|| ((dwStyle & dwSizedMask) == dwNoCaptionSized)
							;
			if (dwStyle & (DS_MODALFRAME|WS_CHILDWINDOW))
				lbCanAttach = false;
			else if ((dwStyle & WS_POPUP) && !(dwStyle & WS_THICKFRAME))
				lbCanAttach = false;
			else if (dwExStyle & (WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_DLGMODALFRAME|WS_EX_MDICHILD))
				lbCanAttach = false;

			// Disable attach of some window classes
			if (lbCanAttach && lpClassNameW && (((DWORD_PTR)lpClassNameW) & ~0xFFFF))
			{
				if (lstrcmpW(lpClassNameW, L"MozillaTempWindowClass") == 0)
					lbCanAttach = false;
			}

			if (lbCanAttach)
			{
				// Родительское окно - ConEmu DC
				// -- hWndParent = ghConEmuWndBack; // Надо ли его ставить сразу, если не включаем WS_CHILD?

				// WS_CHILDWINDOW перед созданием выставлять нельзя, т.к. например у WordPad.exe сносит крышу:
				// все его окна создаются нормально, но он показывает ошибку "Не удалось создать новый документ"
				//// Уберем рамку, меню и заголовок - оставим
				//dwStyle = (dwStyle | WS_CHILDWINDOW|WS_TABSTOP) & ~(WS_THICKFRAME/*|WS_CAPTION|WS_MINIMIZEBOX|WS_MAXIMIZEBOX*/);
				bStyleHidden = (dwStyle & WS_VISIBLE) == WS_VISIBLE;
				dwStyle &= ~WS_VISIBLE; // А вот видимость - точно сбросим
				////dwExStyle = dwExStyle & ~WS_EX_WINDOWEDGE;

				bAttachGui = TRUE;
				//gbAttachGuiClient = FALSE; // Только одно окно приложения -- сбросим после реального создания окна
				gbGuiClientAttached = TRUE; // Сразу взведем флажок режима

				#ifdef _DEBUG
				if (!ghGuiClientRetHook)
					ghGuiClientRetHook = SetWindowsHookExW(WH_CALLWNDPROCRET, GuiClientRetHook, NULL, GetCurrentThreadId());
				//if (!ghGuiClientCallHook)
				//	ghGuiClientCallHook = SetWindowsHookExW(WH_CALLWNDPROC, GuiClientCallHook, NULL, GetCurrentThreadId());
				//if (!ghGuiClientMsgHook)
				//	ghGuiClientMsgHook = SetWindowsHookExW(WH_GETMESSAGE, GuiClientMsgHook, NULL, GetCurrentThreadId());
				#endif

				//gnAttachGuiClientThreadId = nTID; -- перенес к "ghAttachGuiClient = hWindow;"

				RECT rcGui = AttachGuiClientPos(dwStyle, dwExStyle);
				if (hWndParent != ghConEmuWndBack)
				{
					MapWindowPoints(ghConEmuWndBack, hWndParent, (LPPOINT)&rcGui, 2);
				}
				grcConEmuClient = rcGui;
			}
			return true;
		}
	}

	if (gbGuiClientAttached /*ghAttachGuiClient*/)
	{
		return true; // В GUI приложениях - разрешено все
	}

#ifndef _DEBUG
	return true;
#else
	if (gnHookMainThreadId && gnHookMainThreadId != GetCurrentThreadId())
		return true; // Разрешено, отдается на откуп консольной программе/плагинам

	if ((dwStyle & (WS_POPUP|DS_MODALFRAME)) == (WS_POPUP|DS_MODALFRAME))
	{
		// Это скорее всего обычный диалог, разрешим, но пока для отладчика - assert
		_ASSERTE((dwStyle & WS_POPUP) == 0);
		return true;
	}

	if ((lpClassNameA && ((DWORD_PTR)lpClassNameA) <= 0xFFFF)
		|| (lpClassNameW && ((DWORD_PTR)lpClassNameW) <= 0xFFFF))
	{
		// Что-то системное
		return true;
	}

	// Окно на любой чих создается. dwStyle == 0x88000000.
	if ((lpClassNameW && lstrcmpW(lpClassNameW, L"CicMarshalWndClass") == 0)
		|| (lpClassNameA && lstrcmpA(lpClassNameA, "CicMarshalWndClass") == 0)
		)
	{
		return true;
	}

	// WiX
	if ((lpClassNameW && lstrcmpW(lpClassNameW, L"MsiHiddenWindow") == 0)
		)
	{
		return true;
	}

	#ifdef _DEBUG
	// В консоли нет обработчика сообщений, поэтому создание окон в главной
	// нити приводит к "зависанию" приложения - например, любые программы,
	// использующие DDE могут виснуть.
	wchar_t szModule[MAX_PATH] = {}; GetModuleFileName(ghOurModule, szModule, countof(szModule));
	//const wchar_t* pszSlash = PointToName(szModule);
	//if (lstrcmpi(pszSlash, L"far.exe")==0 || lstrcmpi(szModule, L"far64.exe")==0)
	if (IsFarExe(szModule))
	{
		_ASSERTE(dwStyle == 0 && FALSE);
	}
	//SetLastError(ERROR_THREAD_MODE_NOT_BACKGROUND);
	//return false;
	#endif

	// Разрешить? По настройке?
	return true;
#endif
}