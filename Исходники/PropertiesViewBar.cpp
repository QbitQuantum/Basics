int CPropertiesViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create combo:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
		| WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	
	if (!m_wndObjectCombo.Create (dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Properies Combo \n");
		return -1;      // fail to create
	}

	m_wndObjectCombo.AddString (_T("IDD_ABOUTBOX (Dialog)"));
	m_wndObjectCombo.SetFont (CFont::FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT)));
	m_wndObjectCombo.SetCurSel (0);

	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properies Grid \n");
		return -1;      // fail to create
	}

	InitPropList ();

	m_wndToolBar.Create (this, dwDefaultToolbarStyle, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar (IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle ();

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
		
	m_wndToolBar.SetBarStyle (
		m_wndToolBar.GetBarStyle () & 
			~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner (this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame (FALSE);

	AdjustLayout ();
	return 0;
}