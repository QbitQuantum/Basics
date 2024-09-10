void CFileCommentsPage::OnDrawItem(int /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if ( lpDrawItemStruct->itemID == (UINT)-1 ||
		 ( lpDrawItemStruct->itemAction & ODA_SELECT ) == 0 &&
		 ( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE ) == 0 )
		return;

	const int nRating = lpDrawItemStruct->itemID;

	CRect rcItem( &lpDrawItemStruct->rcItem );

	CDC dc;

	dc.Attach( lpDrawItemStruct->hDC );
	if ( Settings.General.LanguageRTL )
		SetLayout( dc.m_hDC, LAYOUT_RTL );

	CFont* pOldFont = (CFont*)dc.SelectObject( nRating > 0 ? &theApp.m_gdiFontBold : &theApp.m_gdiFont );
	dc.SetBkMode( TRANSPARENT );

	if ( lpDrawItemStruct->itemState & ODS_SELECTED )
	{
		dc.SetTextColor( Colors.m_crHiText );
		if ( Images.m_bmSelected.m_hObject )
			CoolInterface.DrawWatermark( &dc, &rcItem, &Images.m_bmSelected, FALSE ); 	// No overdraw
		else
			dc.FillSolidRect( &rcItem, Colors.m_crHighlight );
	}
	else // Unselected
	{
		dc.SetTextColor( Colors.m_crText );
		dc.FillSolidRect( &rcItem, Colors.m_crSysWindow );
	}

	rcItem.DeflateRect( 4, 1 );

	if ( nRating > 1 )
	{
		for ( int nStar = nRating - 1; nStar; nStar-- )
		{
			rcItem.right -= 16;
			CoolInterface.Draw( &dc, IDI_STAR, 16, rcItem.right, rcItem.top, CLR_NONE,
				( lpDrawItemStruct->itemState & ODS_SELECTED ) );
			rcItem.right -= 2;
		}
	}
	else if ( nRating == 1 )
	{
		rcItem.right -= 16;
		CoolInterface.Draw( &dc, IDI_FAKE, 16, rcItem.right, rcItem.top, CLR_NONE,
			( lpDrawItemStruct->itemState & ODS_SELECTED ) );
	}

	if ( ( lpDrawItemStruct->itemState & ODS_SELECTED ) == 0 &&
		nRating >= 0 && nRating < 7 )
	{
		static COLORREF crRating[7] =
		{
			Colors.m_crRatingNull,	// Unrated
			Colors.m_crRating0,		// Fake
			Colors.m_crRating1,		// Poor
			Colors.m_crRating2,		// Average
			Colors.m_crRating3,		// Good
			Colors.m_crRating4,		// Very good
			Colors.m_crRating5,		// Excellent
		};

		dc.SetTextColor( crRating[ nRating ] );
	}

	CString str;
	m_wndRating.GetLBText( nRating, str );
	dc.DrawText( str, &rcItem, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_NOPREFIX );

	dc.SelectObject( pOldFont );
	dc.Detach();
}