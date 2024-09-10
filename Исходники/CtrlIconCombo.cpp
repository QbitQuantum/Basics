void CIconComboCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if ( lpDrawItemStruct->itemID == -1 ) return;
	if ( ( lpDrawItemStruct->itemAction & ODA_SELECT ) == 0 &&
		 ( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE ) == 0 ) return;
		 
	CRect rcItem, rcText;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	BOOL	bSelected	= lpDrawItemStruct->itemState & ODS_SELECTED;
	
	rcItem.CopyRect( &lpDrawItemStruct->rcItem );
	//	rcItem.OffsetRect( -rcItem.left, -rcItem.top );
	
	rcText.CopyRect( &rcItem );
	rcText.left += 24;
	rcText.right -= 2;
	
	if ( bSelected )
	{
		pDC->Draw3dRect( rcItem.left + 1, rcItem.top + 1,
			rcItem.Width() - 2, rcItem.Height() - 1,
			CoolInterface.m_crBorder, CoolInterface.m_crBorder );
		pDC->FillSolidRect( rcItem.left + 2, rcItem.top + 2,
			rcItem.Width() - 4, rcItem.Height() - 3,
			CoolInterface.m_crBackSel );
		
		pDC->SetBkColor( CoolInterface.m_crBackSel );
	}
	else
	{
		pDC->FillSolidRect( rcItem.left + 1, rcItem.top + 1,
			rcItem.Width() - 2, rcItem.Height() - 1,
			CoolInterface.m_crBackNormal );
		pDC->SetBkColor( CoolInterface.m_crBackNormal );
	}
	
	CPoint pt( rcItem.left + 4, rcItem.top + 3 );
	int nIcon = GetItemImage( lpDrawItemStruct->itemID );
	
	if ( bSelected )
	{
		pt.Offset( 1, 1 );
		pDC->SetTextColor( CoolInterface.m_crShadow );
		CoolInterface.m_pImages.Draw( pDC, nIcon, pt, ILD_MASK );
		pt.Offset( -3, -3 );
		CoolInterface.m_pImages.Draw( pDC, nIcon, pt, ILD_TRANSPARENT );
	}
	else
	{
		ImageList_DrawEx( CoolInterface.m_pImages.m_hImageList, nIcon, pDC->GetSafeHdc(),
			pt.x, pt.y, 0, 0, CLR_NONE, CoolInterface.m_crMargin, ILD_BLEND25 );
	}
	
	CString sText;
	CComboBox::GetLBText(lpDrawItemStruct->itemID, sText);
	
	CFont* pOld = (CFont*)pDC->SelectObject(
		( lpDrawItemStruct->itemState & ODS_DEFAULT ) ?
		&CoolInterface.m_fntBold : &CoolInterface.m_fntNormal );
	
	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( bSelected ? CoolInterface.m_crCmdTextSel : CoolInterface.m_crCmdText );
	pDC->DrawText( sText, &rcText, DT_SINGLELINE|DT_VCENTER|DT_LEFT );
	
	pDC->SelectObject( pOld );
}