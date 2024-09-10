void CExtStatusControlBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
#if (!defined __EXT_MFC_NO_CUSTOMIZE)
CExtCustomizeSite * pSite =
		CExtCustomizeSite::GetCustomizeSite( m_hWnd );
	if(		pSite != NULL
		&&	pSite->IsCustomizeMode()
		)
		return;
#endif // (!defined __EXT_MFC_NO_CUSTOMIZE)

	if( CExtControlBar::FindHelpMode(this) )
		return;

CFrameWnd * pFrame = _GetDockingFrameImpl();
	if( pFrame == NULL )
	{
		CStatusBar::OnContextMenu( pWnd, point );
		return;
	}

	ASSERT_VALID( pFrame );
HWND hWndTrack = GetOwner()->GetSafeHwnd();
	ASSERT( hWndTrack != NULL && ::IsWindow(hWndTrack) );
CExtPopupMenuWnd * pPopup =
		new CExtPopupMenuWnd;
	VERIFY( pPopup->CreatePopupMenu(hWndTrack) );

	if(	! CExtDockBar::_ConstructDockSiteControlBarPopupMenu(
			pFrame,
			pPopup,
			CExtControlBar::POPUP_MENU_EVENT_DATA::__PMED_STATUSBAR_CTX,
			this,
			WM_CONTEXTMENU,
			NULL
			)
		)
	{
		delete pPopup;
		return;
	}
	if( pPopup->ItemGetCount() == 0 )
	{
		delete pPopup;
		return;
	}
	::SetFocus( hWndTrack );
	if( ! pPopup->TrackPopupMenu(
			TPMX_OWNERDRAW_FIXED,
			point.x,
			point.y
			)
		)
	{
		delete pPopup;
	}
}