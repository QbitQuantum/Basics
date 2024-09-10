BOOL CToolBarCtrlPage::OnInitDialog()
{

	CPropertyPage::OnInitDialog();


	m_StandardBar.Create(WS_BORDER | WS_VISIBLE | WS_CHILD
			| CCS_TOP | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
		CRect(0,0,0,0),this, IDR_STANDARDBAR);

	m_PaletteBar.Create(WS_BORDER | WS_VISIBLE | WS_CHILD
			| CCS_BOTTOM | TBSTYLE_WRAPABLE | TBSTYLE_TOOLTIPS,
		CRect(0,0,0,0),this, IDR_PALETTEBAR);

	m_StandardBar.AutoSize();
	m_PaletteBar.AutoSize();

	m_ToolTip.Create(this);

	CString cstrToolTip;
	CWnd *pWnd = 0;
	CRect rect;

	// Setup the tooltip control for tooltips with the static controls
	for (int nIndex = ID_TOOLBARSTYLE; nIndex <= ID_TBSTYLETOOLTIPS2; nIndex++)
	{
		cstrToolTip.LoadString(nIndex);

		ENSURE(pWnd = GetDlgItem(nIndex));

		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);

		m_ToolTip.AddTool(this, (LPCTSTR)cstrToolTip, &rect, nIndex);
	}

	m_ToolTip.Activate(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}