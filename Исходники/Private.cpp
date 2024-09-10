STDMETHODIMP CBar::Attach(OLE_HANDLE hWndParentIn)
{
	if (m_bStartedToolBars)
		return NOERROR;

	HWND hWndParent = (HWND)hWndParentIn;
	if (!IsWindow(hWndParent))
		hWndParent = GetDockWindow();
	else
	{
		m_fInPlaceActive = TRUE;
		m_bUserMode = 1;
		m_hWndDock = m_hWndParent = hWndParent;
		// Create an ActiveBar Window
		CRect rc;
		GetClientRect(hWndParent, &rc);
		m_Size = rc.Size();
		if (NULL == m_hWnd)
			CreateInPlaceWindow(0, 0, FALSE);
		else
			SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW|SWP_NOACTIVATE);
	}

	if (!hWndParent)
		return E_FAIL;

	if (AmbientUserMode() && IsWindow(hWndParent))
		DragAcceptFiles(hWndParent, TRUE);

	if (GetAmbientProperty(DISPID_AMBIENT_BACKCOLOR, VT_I4, &m_ocAmbientBackColor))
		OleTranslateColor(m_ocAmbientBackColor, NULL, &m_crAmbientBackColor);

	void* pPrevBar;
	HWND hWndMdi;
	TCHAR szBuffer[_MAX_PATH];
	DWORD dwResult = GetModuleFileName(NULL, szBuffer, 255);

	if (dwResult > 0 && lstrlen(szBuffer) > 12 && 0 == lstrcmpi(szBuffer + lstrlen(szBuffer) - 12, _T("iexplore.exe")))
		m_bIE = TRUE;

	const int nLen = 15;
	TCHAR szClassName[nLen];
	if (AmbientUserMode())
	{
		hWndMdi = ::GetWindow(hWndParent, GW_CHILD);
		if (hWndMdi)
		{
			MAKE_TCHARPTR_FROMWIDE(szWindowClass, m_bstrWindowClass);
			GetClassName(hWndMdi, szClassName, nLen);
			if (0 == lstrcmpi(szClassName, szWindowClass))
			{
				//
				// Hook into the MDIClient Form
				//

				m_eAppType = eMDIForm;
				m_hWndMDIClient = hWndMdi;

				IOleControlSite* pControlSite;
				HRESULT hResult = m_pClientSite->QueryInterface(IID_IOleControlSite, (void**)&pControlSite);
				if (SUCCEEDED(hResult))
				{
					LPDISPATCH pDispatch;
					hResult = pControlSite->GetExtendedControl(&pDispatch);
					pControlSite->Release();
					if (SUCCEEDED(hResult))
					{
						VARIANT vWidth;
						vWidth.vt = VT_I4;
						vWidth.lVal = 0;
						hResult = PropertyPut(pDispatch, L"Width", vWidth);
						pDispatch->Release();
					}
				}

				if (AmbientUserMode())
					DragAcceptFiles(m_hWndMDIClient, TRUE);

				if (GetGlobals().m_pmapBar->Lookup((LPVOID)m_hWndMDIClient, pPrevBar))
				{
					TRACE2(1, _T("Window handle already entered Bar: %X hWnd: %X\n"), 
						   this, 
						   m_hWndMDIClient);
					return NOERROR;
				}
				GetGlobals().m_pmapBar->SetAt((LPVOID)m_hWndMDIClient,(LPVOID)this);

				m_pMDIClientProc = (WNDPROC)GetWindowLong(m_hWndMDIClient, GWL_WNDPROC);
				SetWindowLong(m_hWndMDIClient, GWL_WNDPROC, (LONG)MDIClientWindowProc);
				
				CacheSmButtonSize();
				
				CRect rcWin;
				::GetWindowRect(m_hWndMDIClient, &rcWin);
				m_nNewCustomizedFloatBandCounter = 0;
				m_ptNewCustomizedFloatBandPos.x = rcWin.left + 16;
				m_ptNewCustomizedFloatBandPos.y = rcWin.top + 16;
			}
		}
	}
	else
	{
		//
		// If we are in design mode check if we are on an MDI Form or not
		//

		GetClassName(hWndParent, szClassName, nLen);
		if (0 == lstrcmpi(szClassName, _T("ThunderMDIForm")))
			m_eAppType = eMDIForm;
	}

	if (eMDIForm == m_eAppType)
	{
		//
		// Check if two activebars are present
		//

		if (GetGlobals().m_pmapBar->Lookup((LPVOID)hWndParent, pPrevBar))
		{
			TRACE2(1, _T("Window handle already entered Bar: %X hWnd: %X\n"), 
				   this, 
				   hWndParent);
			return NOERROR;
		}

		//
		// Set the map and subclass the window procedure 
		//

		GetGlobals().m_pmapBar->SetAt((LPVOID)hWndParent,(LPVOID)this);
		TRACE2(1, _T("Window handle entered Bar: %X hWnd: %X\n"), 
			   this, 
			   hWndParent);

		m_pMainProc = (WNDPROC)GetWindowLong(hWndParent, GWL_WNDPROC);
		SetWindowLong (hWndParent, GWL_WNDPROC, (LONG)FrameWindowProc);
	}
	else
	{
		if (VARIANT_TRUE == bpV1.m_vbAlignToForm)
		{
			m_eAppType = eSDIForm;

			//
			// Check if two activebars are present
			//

			if (GetGlobals().m_pmapBar->Lookup((LPVOID)hWndParent, pPrevBar))
			{
				TRACE2(1, _T("Window handle already entered Bar: %X hWnd: %X\n"), 
					   this, 
					   hWndParent);
				return NOERROR;
			}

			//
			// Set the map and subclass the window procedure 
			//

			GetGlobals().m_pmapBar->SetAt((LPVOID)hWndParent,(LPVOID)this);
			TRACE2(1, _T("Window handle entered Bar: %X hWnd: %X\n"), 
				   this, 
				   hWndParent);

			m_pMainProc = (WNDPROC)GetWindowLong(hWndParent, GWL_WNDPROC);
			SetWindowLong (hWndParent, GWL_WNDPROC, (LONG)FormWindowProc);

			CRect rcClient;
			if (GetClientRect(hWndParent, &rcClient) && m_pInPlaceSite)
				m_pInPlaceSite->OnPosRectChange(&rcClient);
		}
		else
			m_eAppType = eClientArea;

		CRect rcWin;
		GetWindowRect(hWndParent, &rcWin);
		m_nNewCustomizedFloatBandCounter = 0;
		m_ptNewCustomizedFloatBandPos.x = rcWin.left + 64;
		m_ptNewCustomizedFloatBandPos.y = rcWin.top + 64;
	}
	LPVOID pTmp;
	if (!GetGlobals().m_pmapAccelator->Lookup((LPVOID)hWndParent, (void*&)pTmp))
		GetGlobals().m_pmapAccelator->SetAt(hWndParent, (LPVOID)this);
	m_bStartedToolBars = TRUE;
	return NOERROR;
}