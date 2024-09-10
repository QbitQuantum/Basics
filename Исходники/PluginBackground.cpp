// Вызывается ТОЛЬКО в главной нити!
void CPluginBackground::UpdateBackground()
{
	if (!mn_BgPluginsCount)
		return;

	if (!ghConEmuWndDC || !IsWindow(ghConEmuWndDC))
		return;

	if (mb_ThNeedLoad)
	{
		LoadThSet(TRUE/*Мы уже в главной нити*/);
	}

	//RECT rcClient; GetClientRect(ghConEmuWndDC, &rcClient);
	struct PaintBackgroundArg Arg = m_Default;
	Arg.cbSize = sizeof(struct PaintBackgroundArg);
	//m_Default.dcSizeX = Arg.dcSizeX = rcClient.right+1;
	//m_Default.dcSizeY = Arg.dcSizeY = rcClient.bottom+1;
	m_Default.dcSizeX = Arg.dcSizeX = (m_Default.rcConWorkspace.right-m_Default.rcConWorkspace.left+1)*m_Default.MainFont.nFontCellWidth;
	m_Default.dcSizeY = Arg.dcSizeY = (m_Default.rcConWorkspace.bottom-m_Default.rcConWorkspace.top+1)*m_Default.MainFont.nFontHeight;
	// **********************************************************************************
	// запомнить данные из m_Default в m_Last, но т.к. там есть указатели - move не катит
	// **********************************************************************************
	//memmove(&m_Last, &m_Default, sizeof(m_Last));
	m_Last.MainFont = m_Default.MainFont;
	memmove(m_Last.crPalette, m_Default.crPalette, sizeof(m_Last.crPalette));
	m_Last.dcSizeX = m_Default.dcSizeX;
	m_Last.dcSizeY = m_Default.dcSizeY;
	m_Last.rcDcLeft = m_Default.rcDcLeft;
	m_Last.rcDcRight = m_Default.rcDcRight;
	m_Last.rcConWorkspace = m_Default.rcConWorkspace;
	m_Last.conCursor = m_Default.conCursor;
	m_Last.FarInterfaceSettings.Raw = m_Default.FarInterfaceSettings.Raw;
	m_Last.FarPanelSettings.Raw = m_Default.FarPanelSettings.Raw;
	memmove(m_Last.nFarColors, m_Default.nFarColors, sizeof(m_Last.nFarColors));
	m_Last.bPanelsAllowed = m_Default.bPanelsAllowed;
	// struct tag_BkPanelInfo
	m_Last.LeftPanel.bVisible = m_Default.LeftPanel.bVisible;
	m_Last.LeftPanel.bFocused = m_Default.LeftPanel.bFocused;
	m_Last.LeftPanel.bPlugin = m_Default.LeftPanel.bPlugin;
	m_Last.LeftPanel.rcPanelRect = m_Default.LeftPanel.rcPanelRect;
	m_Last.RightPanel.bVisible = m_Default.RightPanel.bVisible;
	m_Last.RightPanel.bFocused = m_Default.RightPanel.bFocused;
	m_Last.RightPanel.bPlugin = m_Default.RightPanel.bPlugin;
	m_Last.RightPanel.rcPanelRect = m_Default.RightPanel.rcPanelRect;
	// строки
	lstrcpyW(m_Last.LeftPanel.szCurDir, m_Default.LeftPanel.szCurDir);
	lstrcpyW(m_Last.LeftPanel.szFormat, m_Default.LeftPanel.szFormat);
	lstrcpyW(m_Last.LeftPanel.szHostFile, m_Default.LeftPanel.szHostFile);
	lstrcpyW(m_Last.RightPanel.szCurDir, m_Default.RightPanel.szCurDir);
	lstrcpyW(m_Last.RightPanel.szFormat, m_Default.RightPanel.szFormat);
	lstrcpyW(m_Last.RightPanel.szHostFile, m_Default.RightPanel.szHostFile);
	// **********************************************************************************

	if (m_Default.dcSizeX < 1 || m_Default.dcSizeY < 1)
	{
		_ASSERTE(m_Default.dcSizeX >= 1 && m_Default.dcSizeY >= 1);
		return;
	}

	SetDcPanelRect(&Arg.rcDcLeft, &Arg.LeftPanel, &Arg);
	SetDcPanelRect(&Arg.rcDcRight, &Arg.RightPanel, &Arg);

	// gpTabs отстает от реальности.
	Arg.Place = m_Default.Place;
	//if (!gpTabs)
	//	Arg.Place = pbp_Panels;
	//else if (gnCurrentWindowType == WTYPE_EDITOR)
	//	Arg.Place = pbp_Editor;
	//else if (gnCurrentWindowType == WTYPE_VIEWER)
	//	Arg.Place = pbp_Viewer;
	//else if (Arg.LeftPanel.bVisible || Arg.RightPanel.bVisible)
	//{
	//	_ASSERTE(gnCurrentWindowType == WTYPE_PANELS);
	//	Arg.Place = pbp_Panels;
	//}

	BITMAPINFOHEADER bi = {sizeof(BITMAPINFOHEADER)};
	bi.biWidth = Arg.dcSizeX;
	bi.biHeight = Arg.dcSizeY;
	bi.biPlanes = 1;
	bi.biBitCount = 32; //-V112
	bi.biCompression = BI_RGB;

	//_ASSERTE(Arg.LeftPanel.bVisible || Arg.RightPanel.bVisible);
	HDC hScreen = GetDC(NULL);

	RECT rcMeta = {0,0, Arg.dcSizeX, Arg.dcSizeY}; // (in pixels)
	int iWidthMM = GetDeviceCaps(hScreen, HORZSIZE); if (iWidthMM <= 0) { _ASSERTE(iWidthMM>0); iWidthMM = 1024; }
	int iHeightMM = GetDeviceCaps(hScreen, VERTSIZE); if (iHeightMM <= 0) { _ASSERTE(iHeightMM>0); iHeightMM = 768; }
	int iWidthPels = GetDeviceCaps(hScreen, HORZRES); if (iWidthPels <= 0) { _ASSERTE(iWidthPels>0); iWidthPels = 0; }
	int iHeightPels = GetDeviceCaps(hScreen, VERTRES); if (iHeightPels <= 0) { _ASSERTE(iHeightPels>0); iHeightPels = 0; }
	RECT rcMetaMM = {0,0, (rcMeta.right * iWidthMM * 100)/iWidthPels, (rcMeta.bottom * iHeightMM * 100)/iHeightPels}; // (in .01-millimeter units)

	HDC hdc = NULL;
	HENHMETAFILE hEmf = NULL;
	COLORREF* pBits = NULL;
	HBITMAP hDib = NULL, hOld = NULL;
#ifdef CREATE_EMF_TEMP_FILES
	wchar_t szEmfFile[MAX_PATH] = {};
#endif
	wchar_t *pszEmfFile = NULL;


	if (SETBACKGROUND_USE_EMF==1)
	{
		#ifdef CREATE_EMF_TEMP_FILES
		GetTempPath(MAX_PATH-32, szEmfFile);
		int nLen = lstrlen(szEmfFile);
		if (*szEmfFile && szEmfFile[nLen-1] != L'\\')
		{
			szEmfFile[nLen++] = L'\\';
			szEmfFile[nLen] = 0;
		}
		_wsprintf(szEmfFile+nLen, SKIPLEN(31) L"CeBack%u.emf", GetCurrentProcessId());
		pszEmfFile = szEmfFile;
		#endif

		hdc = CreateEnhMetaFile(hScreen, pszEmfFile, &rcMetaMM, L"ConEmu\0Far Background\0\0");
		if (!hdc)
		{
			_ASSERTE(hdc!=NULL);
			return;
		}
	}
	else
	{
		hdc = CreateCompatibleDC(hScreen);
		if (!hdc)
		{
			_ASSERTE(hdc!=NULL);
			return;
		}
		_ASSERTE(pBits = NULL);
		hDib = CreateDIBSection(hScreen, (BITMAPINFO*)&bi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	}
	ReleaseDC(NULL, hScreen); hScreen = NULL;

	Arg.hdc = hdc;

	if (SETBACKGROUND_USE_EMF==1)
	{
		HBRUSH hFillBr = CreateSolidBrush (
			#ifdef _DEBUG
				RGB(128,128,0)
			#else
				RGB(0,0,0)
			#endif
		);
		FillRect(hdc, &rcMeta, hFillBr);
		DeleteObject(hFillBr);
	}
	else
	{
		if (!hDib || !pBits)
		{
			_ASSERTE(hDib && pBits);
			if (hDib)
				DeleteObject(hDib);
			if (hdc)
				DeleteDC(hdc);
			return;
		}

		hOld = (HBITMAP)SelectObject(hdc, hDib);

		// Залить черным - по умолчанию
		#ifdef _DEBUG
			memset(pBits, 128, bi.biWidth*bi.biHeight*4); //-V112
		#else
			memset(pBits, 0, bi.biWidth*bi.biHeight*4);
		#endif
	}

	// Painting!
	int nProcessed = 0;
	MSectionLock SC; SC.Lock(csBgPlugins, TRUE);
	DWORD nFromLevel = 0, nNextLevel, nSuggested;
	DWORD dwDrawnPlaces = Arg.Place;

	while(true)
	{
		nNextLevel = nFromLevel;
		struct RegisterBackgroundArg *p = mp_BgPlugins;

		for(int i = 0; i < mn_BgPluginsCount; i++, p++)
		{
			if (p->Cmd != rbc_Register ||
			        !(p->dwPlaces & Arg.Place) ||
			        !(p->PaintConEmuBackground))
				continue; // пустая, неактивная в данном контексте, или некорректная ячейка

			// Слои
			nSuggested = p->dwSuggestedLevel;

			if (nSuggested < nFromLevel)
			{
				continue; // Этот слой уже обработан
			}
			else if (nSuggested > nFromLevel)
			{
				// Этот слой нужно будет обработать в следующий раз
				if ((nNextLevel == nFromLevel) || (nSuggested < nNextLevel))
					nNextLevel = nSuggested;

				continue;
			}

			// На уровне 0 (заливающий фон) должен быть только один плагин
			Arg.dwLevel = (nProcessed == 0) ? 0 : (nFromLevel == 0 && nProcessed) ? 1 : nFromLevel;
			Arg.lParam = mp_BgPlugins[i].lParam;
			Arg.dwDrawnPlaces = 0;
			//mp_BgPlugins[i].PaintConEmuBackground(&Arg);
			UpdateBackground_Exec(mp_BgPlugins+i, &Arg);
			// Что плагин покрасил (панели/редактор/вьювер считаются покрашенными по умолчанию)
			dwDrawnPlaces |= Arg.dwDrawnPlaces;
			//
			nProcessed++;
		}

		if (nNextLevel == nFromLevel)
			break; // больше слоев нет

		nFromLevel = nNextLevel;
	}

	SC.Unlock();
	// Sending background to GUI!

	if (nProcessed < 1)
	{
		// Ситуация возникает при старте ConEmu, когда панелей "еще нет"
		//_ASSERTE(nProcessed >= 1);
		if (mb_BgWasSent)
		{
			mb_BgWasSent = FALSE;
			CESERVER_REQ *pIn = ExecuteNewCmd(CECMD_SETBACKGROUND, sizeof(CESERVER_REQ_HDR)+sizeof(CESERVER_REQ_SETBACKGROUND));
			if (pIn)
			{
				pIn->Background.nType = 1;
				pIn->Background.bEnabled = FALSE;
				pIn->Background.dwDrawnPlaces = 0;
				CESERVER_REQ *pOut = ExecuteGuiCmd(FarHwnd, pIn, FarHwnd);

				if (pOut)
				{
					ExecuteFreeResult(pOut);
				}
				ExecuteFreeResult(pIn);
			}
		}
	}
	else // есть "отработавшие" плагины, обновить Background!
	{
		GdiFlush();
		DWORD nBitSize = 0, nBitsError = 0;
		if (SETBACKGROUND_USE_EMF==1)
		{
			hEmf = CloseEnhMetaFile(hdc);
			hdc = NULL;

			nBitSize = GetEnhMetaFileBits(hEmf, 0, NULL);
			if (nBitSize == 0)
			{
				dwDrawnPlaces = 0;
				nBitsError = GetLastError();
				_ASSERTE(nBitSize!=0);
				if (hEmf)
				{
					// В случае ошибки - сразу удаляем
					DeleteEnhMetaFile(hEmf);
					hEmf = NULL;
				}
			}
		}
		else
		{
			nBitSize = bi.biWidth*bi.biHeight*sizeof(COLORREF);
		}
		DWORD nWholeSize = sizeof(CESERVER_REQ_HDR)+sizeof(CESERVER_REQ_SETBACKGROUND)+nBitSize; //-V103 //-V119
		CESERVER_REQ *pIn = ExecuteNewCmd(CECMD_SETBACKGROUND, nWholeSize);

		if (!pIn)
		{
			_ASSERTE(pIn);
		}
		else
		{
			pIn->Background.nType = 1;
			pIn->Background.bEnabled = TRUE;
			pIn->Background.dwDrawnPlaces = dwDrawnPlaces;
			if (SETBACKGROUND_USE_EMF==1)
				pIn->Background.bmp.bfType = 0x4645/*EF*/;
			else
				pIn->Background.bmp.bfType = 0x4D42/*BM*/;
			pIn->Background.bmp.bfSize = nBitSize+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER); //-V119
			pIn->Background.bmp.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER); //-V119
			pIn->Background.bi = bi;

			if (SETBACKGROUND_USE_EMF==1)
			{
				LPBYTE pBits = ((LPBYTE)&pIn->Background)+sizeof(pIn->Background);
				DWORD nBitsRc = (nBitSize && hEmf) ? GetEnhMetaFileBits(hEmf, nBitSize, pBits) : 0;
				_ASSERTE(nBitsRc == nBitSize);
				if (!nBitsRc)
				{
					_ASSERTE(nBitsRc!=NULL);
					// Отключить нафиг
					ExecutePrepareCmd(&pIn->hdr, CECMD_SETBACKGROUND, nWholeSize-nBitSize);
					pIn->Background.nType = 1;
					pIn->Background.bEnabled = FALSE;
					pIn->Background.dwDrawnPlaces = 0;
				}
			}
			else
			{
				memmove(((LPBYTE)&pIn->Background)+sizeof(pIn->Background), pBits, bi.biWidth*bi.biHeight*sizeof(COLORREF));
			}
			CESERVER_REQ *pOut = ExecuteGuiCmd(FarHwnd, pIn, FarHwnd);

			// Вызывается ТОЛЬКО в главной нити
			_ASSERTE(GetCurrentThreadId() == gnMainThreadId);
			if (pOut)
			{
				mb_BgWasSent = TRUE;
				// Сбросим флажок "Ошибка уже была показана"
				if (pOut->BackgroundRet.nResult == esbr_OK)
				{
					mb_BgErrorShown = FALSE;
				}
				// Показать ошибку, если есть
				else if ((pOut->BackgroundRet.nResult > esbr_OK) && (pOut->BackgroundRet.nResult <= esbr_LastErrorNo)
					&& (pOut->BackgroundRet.nResult != esbr_ConEmuInShutdown)
					&& !mb_BgErrorShown)
				{
					mb_BgErrorShown = TRUE;
					Plugin()->ShowMessage(CEBkError_ExecFailed+pOut->BackgroundRet.nResult, 0);
				}
				ExecuteFreeResult(pOut);
			}
			else if (!mb_BgErrorShown)
			{
				mb_BgErrorShown = TRUE;
				Plugin()->ShowMessage(CEBkError_ExecFailed, 0);
			}

			ExecuteFreeResult(pIn);
		}
	}

	if (SETBACKGROUND_USE_EMF == 0)
	{
		if (hdc && hOld)
			SelectObject(hdc, hOld);
		if (hDib)
			DeleteObject(hDib);
		if (hdc)
			DeleteDC(hdc);
	}
	else
	{
		if (hdc)
		{
			hEmf = CloseEnhMetaFile(hdc);
			hdc = NULL;
		}
		if (hEmf)
		{
			DeleteEnhMetaFile(hEmf);
			hEmf = NULL;
		}
	}
}