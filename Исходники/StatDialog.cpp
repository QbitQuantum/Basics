BOOL CStatDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

//	m_Graph.SubclassWindow( GetDlgItem(IDC_GRAPH)->m_hWnd );

#if(0)
	RECT CtrlRect, DlgRect;

	GetDlgItem(IDC_GRAPH)->GetWindowRect(&CtrlRect);
	GetDlgItem(IDC_GRAPH)->DestroyWindow();
	GetWindowRect(&DlgRect);

	CRect NewRect = CtrlRect;
	NewRect.OffsetRect(-CRect(DlgRect).TopLeft());

	m_Graph.Create("LINE_CHART_CTRL", "", WS_VISIBLE | WS_CHILD, 
		NewRect, this, IDC_GRAPH);
	
	m_Graph.Add(RGB(0,255,0),100, 0, "Connections");
#endif

#if (_MFC_VER > 0x0421)
	m_GraphTab.InsertItem(0, "Logins");
	m_GraphTab.InsertItem(1, "Login Duration");
	m_GraphTab.InsertItem(2, "Login Duration Avg.");
	m_GraphTab.InsertItem(3, "Password Failures");
	m_GraphTab.InsertItem(4, "Download Count");
	m_GraphTab.InsertItem(5, "Download Size");
	m_GraphTab.InsertItem(6, "Download Duration");
	m_GraphTab.InsertItem(7, "Upload Count");
	m_GraphTab.InsertItem(8, "Upload Size");
	m_GraphTab.InsertItem(9, "Upload Duration");
#else
	TC_ITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = "Logins";
	m_GraphTab.InsertItem(0, &tcItem);
	tcItem.pszText = "Login Duration";
	m_GraphTab.InsertItem(1, &tcItem);
	tcItem.pszText = "Login Duration Avg.";
	m_GraphTab.InsertItem(2, &tcItem);
	m_GraphTab.InsertItem(3, &tcItem);
	m_GraphTab.InsertItem(4, &tcItem);
	m_GraphTab.InsertItem(5, &tcItem);
	m_GraphTab.InsertItem(6, &tcItem);
	m_GraphTab.InsertItem(7, &tcItem);
	m_GraphTab.InsertItem(8, &tcItem);
	m_GraphTab.InsertItem(9, &tcItem);
#endif

//	CImageList* ImageList = new CImageList();
//    ImageList->Create(MAKEINTRESOURCE(IDB_BITMAP_2), 22, 1, RGB(192,192,192));
//	m_ChartWnd.SetImageList(ImageList);

	m_ChartWnd.SetUserColTitle("Logins");

	m_StatCallback(&m_FullStat, -1, "", "", &m_GroupArray, &m_UserArray);
	FillUserGroupList();
	GetStats(m_User, m_Group);
	STAT_ADD_PLOTS(LoginCount);

    m_ChartWnd.EnableTitleTips();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}