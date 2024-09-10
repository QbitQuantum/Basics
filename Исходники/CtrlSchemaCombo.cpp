void CSchemaCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if ( lpDrawItemStruct->itemID == (UINT)-1 ) return;
	if ( ( lpDrawItemStruct->itemAction & ODA_SELECT ) == 0 &&
		 ( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE ) == 0 ) return;

	CRect rcItem( &lpDrawItemStruct->rcItem );
	CPoint pt( rcItem.left + 1, rcItem.top + 1 );
	CDC dc;

	dc.Attach( lpDrawItemStruct->hDC );
	if ( Settings.General.LanguageRTL )
		SetLayout( dc.m_hDC, LAYOUT_RTL );

	dc.SetTextColor( ( lpDrawItemStruct->itemState & ODS_SELECTED )
		? CoolInterface.m_crHiText : CoolInterface.m_crDropdownText );

	CSchemaPtr pSchema = (CSchemaPtr)lpDrawItemStruct->itemData;

	if ( pSchema != NULL )
	{
		/*dc.FillSolidRect( &rcItem,
			GetSysColor( ( lpDrawItemStruct->itemState & ODS_SELECTED ) ? COLOR_HIGHLIGHT : COLOR_WINDOW ) );*/
		if ( IsWindowEnabled() )
		{
			if ( lpDrawItemStruct->itemState & ODS_SELECTED )
				dc.FillSolidRect( &rcItem, CoolInterface.m_crHighlight );
			else
				dc.FillSolidRect( &rcItem, CoolInterface.m_crDropdownBox );
		}
		else
			dc.FillSolidRect( &rcItem, GetBkColor(lpDrawItemStruct->hDC) );

		dc.SetBkMode( TRANSPARENT );

		ShellIcons.Draw( &dc, pSchema->m_nIcon16, 16, pt.x, pt.y, CLR_NONE,
			( lpDrawItemStruct->itemState & ODS_SELECTED ) );

		rcItem.left += 20; rcItem.right -= 2;

		CFont* pOldFont = (CFont*)dc.SelectObject( &theApp.m_gdiFont );
		CString strURI = pSchema->GetURI();

		if ( dc.GetTextExtent( pSchema->m_sTitle + strURI ).cx > rcItem.Width() - 20
			 && strURI.GetLength() > 8 )
		{
			LPCTSTR pszLeft = _tcschr( (LPCTSTR)strURI + 7, '/' );
			int nRight		= strURI.ReverseFind( '/' );

			if ( pszLeft && nRight >= 0 )
			{
				int nLeft = static_cast< int >( pszLeft - (LPCTSTR)strURI );  // !!! (TODO)
				strURI = strURI.Left( nLeft ) + _T("/\x2026") + strURI.Mid( nRight );
			}
		}

		if ( dc.GetTextExtent( pSchema->m_sTitle + strURI ).cx <= rcItem.Width() - 20 )
		{
			// COLORREF crBackup = dc.SetTextColor( GetSysColor( COLOR_GRAYTEXT ) );
			dc.DrawText( strURI, &rcItem, DT_SINGLELINE|DT_RIGHT|DT_VCENTER|DT_NOPREFIX );
			// dc.SetTextColor( crBackup );
		}

		dc.SelectObject( &theApp.m_gdiFontBold );
		dc.DrawText( pSchema->m_sTitle, &rcItem, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_NOPREFIX );
		dc.SelectObject( pOldFont );
	}
	else if ( lpDrawItemStruct->itemID == 0 )
	{
		/*dc.FillSolidRect( &rcItem,
			GetSysColor( ( lpDrawItemStruct->itemState & ODS_SELECTED ) ? COLOR_HIGHLIGHT : COLOR_WINDOW ) );*/
		if ( IsWindowEnabled() )
		{
			if ( lpDrawItemStruct->itemState & ODS_SELECTED )
				dc.FillSolidRect( &rcItem, CoolInterface.m_crHighlight );
			else
				dc.FillSolidRect( &rcItem, CoolInterface.m_crDropdownBox );
		}
		else
			dc.FillSolidRect( &rcItem, GetBkColor(lpDrawItemStruct->hDC) );
		dc.SetBkMode( TRANSPARENT );

		CoolInterface.Draw( &dc, IDR_SEARCHFRAME, 16,
			pt.x, pt.y, CLR_NONE, ( lpDrawItemStruct->itemState & ODS_SELECTED ) );

		rcItem.left += 20; rcItem.right -= 2;

		CFont* pOldFont = (CFont*)dc.SelectObject( &theApp.m_gdiFontBold );
		dc.DrawText( m_sNoSchemaText, &rcItem, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_NOPREFIX );
		dc.SelectObject( pOldFont );
	}
	else
	{
		dc.Draw3dRect( &rcItem, CoolInterface.m_crDropdownBox , CoolInterface.m_crDropdownBox );
		rcItem.DeflateRect( 1, 1 );

		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
		{
			dc.Draw3dRect( &rcItem, CoolInterface.m_crBorder, CoolInterface.m_crBorder );
			rcItem.DeflateRect( 1, 1 );
			dc.FillSolidRect( &rcItem, CoolInterface.m_crBackSel );
		}
		else
		{
			dc.FillSolidRect( &rcItem, GetSysColor( COLOR_WINDOW /* COLOR_BTNFACE */ ) );
		}

		dc.SetBkMode( TRANSPARENT );

		pt = rcItem.CenterPoint();
		pt.x -= 8;
		pt.y -= 8;

		CoolInterface.Draw( &dc, IDI_CHEVRON, 16, pt.x, pt.y );
	}

	dc.Detach();
}