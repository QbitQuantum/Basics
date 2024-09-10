// CDlgControl 消息处理程序
void CDlgControl::FullScreen ( )
{
	RECT			rectDesktop;
    WINDOWPLACEMENT	wpNew;

	GetWindowPlacement ( &wpNew );

	//Adjust RECT to new size of window
	::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
	::AdjustWindowRectEx( &rectDesktop, GetStyle(), TRUE, GetExStyle() );

	// Remember this for OnGetMinMaxInfo()
	//m_FullScreenWindowRect = rectDesktop;

	wpNew.showCmd			= SW_SHOWNORMAL;
	wpNew.rcNormalPosition	= rectDesktop;

	//don't allow the toolbar to dock
	SetWindowPlacement ( &wpNew );

	//SetWindowPos ( NULL, rectDesktop.left, rectDesktop.top,  rectDesktop.right, rectDesktop.bottom, SWP_NOREPOSITION );

	// 重新排列界面元素
	m_iLeft		= 0;
	m_iTop		= 22;
	//m_iTop		= 70;
	m_iRight	= rectDesktop.right-rectDesktop.left;
	m_iBottom	= rectDesktop.bottom-rectDesktop.top-150;
	m_tabCtrl.SetWindowPos ( NULL, m_iLeft, m_iTop, m_iRight, m_iBottom, SWP_NOREPOSITION );

	if ( m_pDlgClient )
		m_pDlgClient->SetWindowPos ( NULL, m_iLeft, m_iTop, m_iRight, m_iBottom, SWP_NOREPOSITION );

	if ( m_pDlgPrePrinting )
		m_pDlgPrePrinting->SetWindowPos ( NULL, m_iLeft, m_iTop, m_iRight, m_iBottom, SWP_NOREPOSITION );

	if ( m_pDlgOperator )
		m_pDlgOperator->SetWindowPos ( NULL, m_iLeft, m_iTop, m_iRight, m_iBottom, SWP_NOREPOSITION );

	GetDlgItem ( IDOK )->SetWindowPos ( NULL, (m_iRight - m_iLeft) / 2 + m_iLeft + 100, m_iBottom + 50, 0, 0, SWP_NOSIZE );

	ActivatePage( m_iCurrentItem )	;
}