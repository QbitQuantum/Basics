HBITMAP CLiveList::CreateDragImage(CListCtrl* pList, const CPoint& ptMouse, CPoint& ptMiddle)
{
	ASSERT_VALID( pList );

	CRect rcClient, rcOne, rcAll( 32000, 32000, -32000, -32000 );
	int nIndex;

	if ( pList->GetSelectedCount() == 0 ) return NULL;

	pList->SetFocus();
	pList->GetClientRect( &rcClient );

	for ( nIndex = -1 ; ( nIndex = pList->GetNextItem( nIndex, LVNI_SELECTED ) ) >= 0 ; )
	{
		pList->GetItemRect( nIndex, rcOne, LVIR_BOUNDS );

		if ( rcOne.IntersectRect( &rcClient, &rcOne ) )
		{
			rcAll.left		= min( rcAll.left, rcOne.left );
			rcAll.top		= min( rcAll.top, rcOne.top );
			rcAll.right		= max( rcAll.right, rcOne.right );
			rcAll.bottom	= max( rcAll.bottom, rcOne.bottom );
		}

		pList->SetItemState( nIndex, 0, LVIS_FOCUSED );
	}

	BOOL bClipped = rcAll.Height() > MAX_DRAG_SIZE;

	if ( bClipped )
	{
		rcAll.left		= max( rcAll.left, ptMouse.x - MAX_DRAG_SIZE_2 );
		rcAll.right		= max( rcAll.right, ptMouse.x + MAX_DRAG_SIZE_2 );
		rcAll.top		= max( rcAll.top, ptMouse.y - MAX_DRAG_SIZE_2 );
		rcAll.bottom	= max( rcAll.bottom, ptMouse.y + MAX_DRAG_SIZE_2 );
	}

	CClientDC dcClient( pList );
	CBitmap bmAll, bmDrag;
	CDC dcAll, dcDrag;

	if ( ! dcAll.CreateCompatibleDC( &dcClient ) )
		return NULL;
	if ( ! bmAll.CreateCompatibleBitmap( &dcClient, rcClient.Width(), rcClient.Height() ) )
		return NULL;

	if ( ! dcDrag.CreateCompatibleDC( &dcClient ) )
		return NULL;
	if ( ! bmDrag.CreateCompatibleBitmap( &dcClient, rcAll.Width(), rcAll.Height() ) )
		return NULL;

	CBitmap *pOldAll = dcAll.SelectObject( &bmAll );

	dcAll.FillSolidRect( &rcClient, DRAG_COLOR_KEY );

	COLORREF crBack = pList->GetBkColor();
	pList->SetBkColor( DRAG_COLOR_KEY );
	pList->SendMessage( WM_PAINT, (WPARAM)dcAll.GetSafeHdc() );
	pList->SetBkColor( crBack );

	CBitmap *pOldDrag = dcDrag.SelectObject( &bmDrag );

	dcDrag.FillSolidRect( 0, 0, rcAll.Width(), rcAll.Height(), DRAG_COLOR_KEY );

	CRgn pRgn;

	ptMiddle.SetPoint( ptMouse.x - rcAll.left, ptMouse.y - rcAll.top );
	if ( bClipped )
	{
		pRgn.CreateEllipticRgn(	ptMiddle.x - MAX_DRAG_SIZE_2, ptMiddle.y - MAX_DRAG_SIZE_2,
								ptMiddle.x + MAX_DRAG_SIZE_2, ptMiddle.y + MAX_DRAG_SIZE_2 );
		dcDrag.SelectClipRgn( &pRgn );
	}

	for ( nIndex = -1 ; ( nIndex = pList->GetNextItem( nIndex, LVNI_SELECTED ) ) >= 0 ; )
	{
		pList->GetItemRect( nIndex, rcOne, LVIR_BOUNDS );

		if ( rcOne.IntersectRect( &rcAll, &rcOne ) )
		{
			dcDrag.BitBlt( rcOne.left - rcAll.left, rcOne.top - rcAll.top,
				rcOne.Width(), rcOne.Height(), &dcAll, rcOne.left, rcOne.top, SRCCOPY );
		}
	}

	dcDrag.SelectObject( pOldDrag );
	dcAll.SelectObject( pOldAll );

	dcDrag.DeleteDC();
	bmAll.DeleteObject();
	dcAll.DeleteDC();

	return (HBITMAP) bmDrag.Detach ();
}