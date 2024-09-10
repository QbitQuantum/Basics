void CColourPickerCB::DrawItem( LPDRAWITEMSTRUCT pDIStruct )
{
	CString strColour;
	CDC dcContext;
	CRect rItemRect( pDIStruct->rcItem );
	CRect rBlockRect( rItemRect );
	CRect rTextRect( rBlockRect );
	CBrush brFrameBrush;
	int iFourthWidth = 0;
	int iItem = pDIStruct->itemID;
	int iAction = pDIStruct->itemAction;
	int iState = pDIStruct->itemState;
	COLORREF crColour = NULL;
	COLORREF crNormal = GetSysColor( COLOR_WINDOW );
	COLORREF crSelected = GetSysColor( COLOR_HIGHLIGHT );
	COLORREF crText = GetSysColor( COLOR_WINDOWTEXT );

	if( !dcContext.Attach( pDIStruct->hDC ) )
	{
		return;
	}

	iFourthWidth = ( rBlockRect.Width() / 4 );
	brFrameBrush.CreateStockObject( BLACK_BRUSH );

	if( iState & ODS_SELECTED )
	{
		dcContext.SetTextColor(	( 0x00FFFFFF & ~( crText ) ) );
		dcContext.SetBkColor( crSelected );
		dcContext.FillSolidRect( &rBlockRect, crSelected );
	}
	else
	{
		dcContext.SetTextColor( crText );
		dcContext.SetBkColor( crNormal );
		dcContext.FillSolidRect( &rBlockRect, crNormal );
	}

	if( iState & ODS_FOCUS )
	{
		dcContext.DrawFocusRect( &rItemRect );
	}

	// calculate text area.
	rTextRect.left += ( iFourthWidth + 2 );
	rTextRect.top += 2;

	// calculate colour block area.
	rBlockRect.DeflateRect( CSize( 2, 2 ) );
	rBlockRect.right = iFourthWidth;

	// draw colour text and block.
	if( iItem != -1 )
	{
		GetLBText( iItem, strColour );

		if( iState & ODS_DISABLED )
		{
			crColour = GetSysColor( COLOR_INACTIVECAPTIONTEXT );
			dcContext.SetTextColor( crColour );
		}
		else
		{
			crColour = (COLORREF)GetItemData( iItem );
		}

		dcContext.SetBkMode( TRANSPARENT );
		dcContext.TextOut( rTextRect.left, rTextRect.top,	strColour );

		dcContext.FillSolidRect( &rBlockRect, crColour );
				
		dcContext.FrameRect( &rBlockRect, &brFrameBrush );
	}

	dcContext.Detach();
}