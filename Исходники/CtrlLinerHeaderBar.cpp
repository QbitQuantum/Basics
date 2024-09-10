void CLinerHeaderBar::PaintHeader(CDC* pDC, CRect& rcBar, BOOL bTransparent)
{
	LPCTSTR xTitle = m_strTitle;
	CFont* pOldFont = (CFont*)pDC->SelectObject( &CoolInterface.m_fntBold );
	
	CSize szText = pDC->GetTextExtent( xTitle );
	
	pDC->SetTextColor( CoolInterface.m_crCmdText );
	pDC->SetBkColor( CoolInterface.m_crMidtone );

	int nMiddle = ( rcBar.top + rcBar.bottom ) / 2;

	if ( bTransparent )
	{
		ImageList_DrawEx( CoolInterface.m_pImages, 22, pDC->GetSafeHdc(),
			rcBar.left + 4, nMiddle - 8, 16, 16, CLR_NONE, CLR_NONE, ILD_NORMAL );
		
		pDC->SetBkMode( TRANSPARENT );
		pDC->ExtTextOut( rcBar.left + 22, nMiddle - szText.cy / 2,
			ETO_CLIPPED, &rcBar, xTitle, NULL );
	}
	else
	{
		pDC->SetBkMode( OPAQUE );
		
		ImageList_DrawEx( CoolInterface.m_pImages, 22, pDC->GetSafeHdc(),
			rcBar.left + 4, nMiddle - 8, 16, 16, CoolInterface.m_crMidtone, CLR_NONE, ILD_NORMAL );
		
		pDC->ExcludeClipRect( rcBar.left + 4, nMiddle - 8, rcBar.left + 20, nMiddle + 8 );
		
		pDC->FillSolidRect( rcBar.left, rcBar.top, 20, rcBar.Height(),
			CoolInterface.m_crMidtone );

		rcBar.left += 20;
		pDC->ExtTextOut( rcBar.left + 2, nMiddle - szText.cy / 2,
			ETO_CLIPPED|ETO_OPAQUE, &rcBar, xTitle, NULL );
		rcBar.left -= 20;
	}

	pDC->SelectObject( pOldFont );
}