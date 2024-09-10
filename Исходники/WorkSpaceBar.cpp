int CWorkSpaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tree windows.
	// TODO: create your own tab windows here:
// 	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
// 								TVS_LINESATROOT | TVS_HASBUTTONS;
// 	
// 	if (!m_wndTree.Create (dwViewStyle, rectDummy, this, 1))
// 	{
// 		TRACE0("Failed to create workspace view\n");
// 		return -1;      // fail to create
// 	}
// 
// 	// Setup trees content:
// 	HTREEITEM hRoot1 = m_wndTree.InsertItem (_T("Root 1"));
// 	m_wndTree.InsertItem (_T("Item 1"), hRoot1);
// 	m_wndTree.InsertItem (_T("Item 2"), hRoot1);
	m_pGridView = new CBCGPGridCtrl;
	if(!m_pGridView)
		return -1;
	CRect rect(0,0,300,300);
	if (!m_pGridView->Create(WS_CHILD|WS_VISIBLE,rect,this,1))
	{
		TRACE0("Warning: couldn't create Grid View!\n");
		return FALSE;
	}
	BCGP_GRID_COLOR_DATA clrData;
	clrData = m_pGridView->GetColorTheme();
	clrData.m_clrBackground = ::GetSysColor(COLOR_3DFACE);
	clrData.m_EvenColors.m_clrBackground = RGB(255,192,203);	// 奇数行
	clrData.m_OddColors.m_clrBackground = RGB(175,238,238);		// 偶数行

	m_pGridView->SetColorTheme(clrData);	
	m_pGridView->SetReadOnly();	
	m_pGridView->SetSingleSel(TRUE);
	m_pGridView->SetWholeRowSel(TRUE);	
	m_pGridView->EnableHeader (TRUE, BCGP_GRID_HEADER_HIDE_ITEMS);
	m_pGridView->EnableDragSelection(FALSE);

	SetGridHead();
	LoadMembers(members);
	LoadState (_T("WorkSpaceBar"));

	return 0;
}