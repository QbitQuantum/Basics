BOOL CChildWnd::TestPoint(const CPoint& ptScreen)
{
	CWnd* pHit = WindowFromPoint( ptScreen );

	if ( pHit == NULL )
		return FALSE;

	if ( pHit == this )
		return TRUE;

	if ( ! IsWindow( pHit->m_hWnd ) || ! IsWindow( GetSafeHwnd() ) )
		return FALSE;

	if ( ::GetAncestor( pHit->m_hWnd, GA_ROOT ) != ::GetAncestor( GetSafeHwnd(), GA_ROOT ) )
		return FALSE;

	CPoint ptChild( ptScreen );
	pHit->ScreenToClient( &ptChild );

	CWnd* pChild = pHit->ChildWindowFromPoint( ptChild, CWP_SKIPINVISIBLE );
	if ( pChild == NULL ) pChild = pHit;

	while ( pChild != NULL )
	{
		if ( pChild == this ) return TRUE;
		pChild = pChild->GetParent();
	}

	return FALSE;
}