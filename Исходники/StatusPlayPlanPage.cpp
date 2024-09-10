void CStatusPlayPlanPage::OnSize(UINT nType, int cx, int cy) 
{
	if (!m_bInitialized)
		return;
	CPropertyPage::OnSize(nType, cx, cy);

	// resize the list control
	CRect rect;
	GetClientRect(&rect);
	m_listPlayPlan.MoveWindow(m_nInitialX, m_nInitialY, 
							  rect.Width() - m_nInitialXMargin*2,
							  rect.Height() - m_nInitialY - m_nInitialYMargin);

	// resize the static text
	CWnd* pStatic = GetDlgItem(IDC_CURRENT_PLAY);
	pStatic->GetWindowRect(&rect);
	ScreenToClient(&rect);
	int dx = cx - rect.right;
	rect.InflateRect(0, 0, dx-4, 0);
	pStatic->MoveWindow(&rect);
}