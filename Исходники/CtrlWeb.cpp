void CWebCtrl::EnterMenu(POINT* pPoint)
{
	if ( m_pThis != NULL )
	{
		SetWindowLongPtr( m_pThis->m_hWndThis, GWLP_WNDPROC, (LONG_PTR)m_pThis->m_pWndProc );
		m_pThis = NULL;
	}

	if ( pPoint == NULL || m_pMenu == NULL ) return;

	CPoint ptScreen( *pPoint );
	ptScreen.Offset( 2, 2 );

	CWnd* pChild = this;
	for ( ;; )
	{
		CPoint ptClient( ptScreen );
		pChild->ScreenToClient( &ptClient );
		CWnd* pNext = pChild->ChildWindowFromPoint( ptClient, CWP_ALL );
		if ( pNext == NULL || pNext == pChild ) break;
		pChild = pNext;
	}

	TCHAR szClass[128];
	GetClassName( *pChild, szClass, 128 );
	if ( _tcsistr( szClass, _T("Internet Explorer") ) == NULL ) return;

	m_pThis = this;
	m_hWndThis = pChild->GetSafeHwnd();
	m_pWndProc = (WNDPROC)(LONG_PTR)GetWindowLongPtr( m_hWndThis, GWLP_WNDPROC );
	SetWindowLongPtr( m_hWndThis, GWLP_WNDPROC, (LONG_PTR)&WebWndProc );
}