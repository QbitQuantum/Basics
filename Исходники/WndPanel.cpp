void CPanelWnd::PaintCaption(CDC& dc)
{
	CString strCaption;
	CRect rc, rcWnd;
	
	BITMAP info = { 0, 0, CAPTION_HEIGHT };
	if ( Skin.m_bmPanelMark.m_hObject) Skin.m_bmPanelMark.GetBitmap( &info );

	GetWindowRect( &rcWnd );
	rc.SetRect( 0, 0, rcWnd.Width(), info.bmHeight );
	GetWindowText( strCaption );

	CSize size = rc.Size();
	CDC* pBuffer = CoolInterface.GetBuffer( dc, size );

	if ( ! CoolInterface.DrawWatermark( pBuffer, &rc, &Skin.m_bmPanelMark, 0, 0 ) )
	{
		pBuffer->FillSolidRect( &rc, Skin.m_crPanelBack );
	}

	int nIconY = rc.Height() / 2 - 8;
	DrawIconEx( pBuffer->GetSafeHdc(), 4, nIconY,
		GetIcon( FALSE ), 16, 16, 0, NULL, DI_NORMAL );

	CFont* pOldFont	= (CFont*)pBuffer->SelectObject( &CoolInterface.m_fntCaption );
	CSize szCaption	= pBuffer->GetTextExtent( strCaption );

	pBuffer->SetBkMode( TRANSPARENT );

	if ( Skin.m_crPanelBorder != CLR_NONE )
	{
		pBuffer->SetTextColor( Skin.m_crPanelBorder );
		pBuffer->ExtTextOut( 8 + 16 - 1, rc.Height() / 2 - szCaption.cy / 2 - 1,
			ETO_CLIPPED, &rc, strCaption, NULL );
		pBuffer->ExtTextOut( 8 + 16 + 1, rc.Height() / 2 - szCaption.cy / 2 - 1,
			ETO_CLIPPED, &rc, strCaption, NULL );
		pBuffer->ExtTextOut( 8 + 16, rc.Height() / 2 - szCaption.cy / 2 - 1 - 1,
			ETO_CLIPPED, &rc, strCaption, NULL );
		pBuffer->ExtTextOut( 8 + 16, rc.Height() / 2 - szCaption.cy / 2 - 1 + 1,
			ETO_CLIPPED, &rc, strCaption, NULL );
	}

	pBuffer->SetTextColor( Skin.m_crPanelText );
	pBuffer->ExtTextOut( 8 + 16, rc.Height() / 2 - szCaption.cy / 2 - 1,
		ETO_CLIPPED, &rc, strCaption, NULL );

	if ( m_bPanelClose )
	{
		pBuffer->SelectObject( &theApp.m_gdiFont );
		CString strText	= _T("Close");
		CSize szText	= pBuffer->GetTextExtent( strText );

		m_rcClose.SetRect( rc.right - szText.cx - 8, rc.top, rc.right, rc.bottom );
		pBuffer->ExtTextOut( m_rcClose.left + 2,
			( m_rcClose.top + m_rcClose.bottom ) / 2 - szText.cy / 2 - 1,
			ETO_CLIPPED, &m_rcClose, strText, NULL );
		m_rcClose.OffsetRect( rcWnd.left, rcWnd.top );
	}

	pBuffer->SelectObject( pOldFont );

	dc.BitBlt( rc.left, rc.top, rc.Width(), rc.Height(), pBuffer, 0, 0, SRCCOPY );

	dc.SelectStockObject( SYSTEM_FONT ); // GDI font leak fix
	dc.SelectStockObject( NULL_BRUSH );	 // GDI brush leak fix
}