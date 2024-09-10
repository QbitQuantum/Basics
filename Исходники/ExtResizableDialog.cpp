BOOL CExtResizableDialog::_TrackDialogSystemMenu(
	CPoint * pPoint,
	BOOL bSelectAny
	)
{
	if( (GetStyle() & WS_POPUP) == 0 )
		return FALSE;
	if(	CExtPopupMenuWnd::IsMenuTracking() )
		CExtPopupMenuWnd::CancelMenuTracking();
	m_bSysMenuTracking = FALSE;

CMenu * pSysMenu =
		GetSystemMenu( FALSE );
	if( pSysMenu == NULL )
		return FALSE;
	ASSERT( ::IsMenu(pSysMenu->GetSafeHmenu()) );
CExtPopupMenuWnd * pPopup = new CExtPopupMenuWnd;
	if( !pPopup->CreatePopupMenu( GetSafeHwnd() ) )
	{
		ASSERT( FALSE );
		return FALSE;
	}
	if( !pPopup->UpdateFromMenu(
			GetSafeHwnd(),
			pSysMenu,
			false
			)
		)
	{
		ASSERT( FALSE );
		return FALSE;
	}

CPoint point;
	if( pPoint != NULL)
		point = *pPoint;
	else
	{
		CRect rcWnd, rcClient, rcHelper;
		GetWindowRect( &rcWnd );
		GetClientRect( &rcClient );
		rcHelper = rcWnd;
		ScreenToClient( &rcHelper );
		ASSERT( rcHelper.top <= rcClient.top );
		int yDiff = rcClient.top - rcHelper.top;
		point = rcWnd.TopLeft();
		point.x += GetSystemMetrics(SM_CXFRAME);
		point.y += yDiff;
	}
	m_bSysMenuTracking =
		pPopup->TrackPopupMenu(
			TPMX_BOTTOMALIGN,
			point.x,point.y,
			GetSafeHwnd(),
			NULL,
			bSelectAny ? true : false
			) ? true : false;

	if( m_bSysMenuTracking )
		SetTimer( ID_TIMER_SYS_TRACKING, 20, NULL );
	return TRUE;
}