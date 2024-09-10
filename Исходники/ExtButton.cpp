void CExtButton::_CbPaintCombinedContent(
	LPVOID pCookie,
	CDC & dc,
	const CWnd & refWndMenu,
	const CRect & rcExcludeArea, // in screen coords
	int eCombineAlign // CExtPopupMenuWnd::e_combine_align_t values
	)
{
	pCookie;
	dc;
	refWndMenu;
	rcExcludeArea;
	eCombineAlign;
	ASSERT( dc.GetSafeHdc() != NULL );
	ASSERT( refWndMenu.GetSafeHwnd() != NULL );

CExtButton * pBtn = (CExtButton *)pCookie;
	ASSERT( pBtn != NULL );
	ASSERT_VALID( pBtn );
	ASSERT( pBtn->IsKindOf(RUNTIME_CLASS(CExtButton)) );
	
	ASSERT( eCombineAlign != CExtPopupMenuWnd::__CMBA_NONE );

	if( rcExcludeArea.IsRectEmpty() )
		return;

CRect rcClientBar,rcClientExcludeArea;
	pBtn->GetClientRect( &rcClientBar );
	pBtn->ClientToScreen( &rcClientBar );
	refWndMenu.GetClientRect( &rcClientExcludeArea );
	refWndMenu.ClientToScreen( &rcClientExcludeArea );
CPoint ptOffset =
		rcClientBar.TopLeft()
		- rcClientExcludeArea.TopLeft()
		;
CPoint ptViewportOrg = dc.GetViewportOrg();
	dc.SetViewportOrg( ptOffset );
	pBtn->_RenderImpl(dc,true);
	dc.SetViewportOrg( ptViewportOrg );
}