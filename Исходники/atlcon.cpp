	HRESULT PreMessageLoop(int nShowCmd) throw()	
	{
		HRESULT hr = S_OK;
		// call base first
		hr = __super::PreMessageLoop(nShowCmd);
		if(FAILED(hr))
			return hr;
			
		::InitCommonControls();
		
		m_pWndFrame = new CAtlCon;
		if(NULL == m_pWndFrame)
			return E_OUTOFMEMORY;
			
		RECT rcPos = { CW_USEDEFAULT, 0, 0, 0 };
		HMENU hMenu = LoadMenu(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDR_MENU1));
		HICON hIcon = LoadIcon(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON1));
		m_pWndFrame->GetWndClassInfo().m_wc.hIcon = hIcon;
		m_pWndFrame->Create(GetDesktopWindow(), rcPos, _T("ATL Container"), 0, 0, (UINT)hMenu);
		m_pWndFrame->ShowWindow(SW_SHOWNORMAL);
		
		return hr;
	}