void CProgStatusBar::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect ;
	int Width = 0;
	CWnd *pst = GetDlgItem( IDC_ST_NET_TB ) ;
	if ( NULL != pst ) {
		pst->GetWindowRect( rect ) ;
		pst->SetWindowPos( NULL ,8 , 12, rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		Width += rect.Width();
	}

	pst = GetDlgItem(IDC_ST_HEIGHT);
	if( NULL != pst)
	{
		pst->GetWindowRect(rect);
		pst->SetWindowPos( NULL ,Width + 20, 12, rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		Width += rect.Width();
	}
	/*
	pst = GetDlgItem(IDC_PROGRESS);
	if( NULL != pst)
	{
		pst->GetWindowRect(rect);
		pst->SetWindowPos( NULL ,Width , rect.top, rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		Width += rect.Width();
	}*/

	int nVerWidth = 0;
	pst = GetDlgItem(IDC_ST_VERSION);
	if(NULL != pst)
	{
		pst->GetWindowRect(rect);
		nVerWidth = rect.Width();
		pst->SetWindowPos( NULL ,900 - 80 - nVerWidth - 25, 12, rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
	}

	int nQQWidth = 0;
	if(::IsWindow(m_vlinkCtrlQQ.m_hWnd))
	{
		m_vlinkCtrlQQ.GetWindowRect(rect);
		nQQWidth = rect.Width();
		m_vlinkCtrlQQ.SetWindowPos( NULL ,900 - 80 - nVerWidth - nQQWidth - 46, 12, rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
	}
	
	int nblockWidth = 0;
	if(::IsWindow(m_vlinkCtrlBlock.m_hWnd))
	{
		m_vlinkCtrlBlock.GetWindowRect(rect);
		nblockWidth = rect.Width();
		m_vlinkCtrlBlock.SetWindowPos( NULL ,900 - 80 - nVerWidth - nQQWidth - nblockWidth - 68 , 12, rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
	}

}