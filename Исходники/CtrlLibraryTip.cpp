void CLibraryTipCtrl::DrawThumb(CDC* pDC, CRect& rcThumb)
{
	pDC->Draw3dRect( &rcThumb, CoolInterface.m_crTipBorder, CoolInterface.m_crTipBorder );
	rcThumb.DeflateRect( 1, 1 );

	if ( m_bmThumb.m_hObject )
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC( pDC );

		CBitmap* pOld = (CBitmap*)dcMem.SelectObject( &m_bmThumb );

		CPoint ptImage(	( rcThumb.left + rcThumb.right ) / 2 - m_szThumb.cx / 2,
						( rcThumb.top + rcThumb.bottom ) / 2 - m_szThumb.cy / 2 );

		pDC->BitBlt( ptImage.x, ptImage.y, m_szThumb.cx, m_szThumb.cy,
			&dcMem, 0, 0, SRCCOPY );
		pDC->ExcludeClipRect( ptImage.x, ptImage.y,
			ptImage.x + m_szThumb.cx, ptImage.y + m_szThumb.cy );

		dcMem.SelectObject( pOld );

		pDC->FillSolidRect( &rcThumb, m_crLight );
	}
	else
	{
		CPoint pt(	( rcThumb.left + rcThumb.right ) / 2 - 24,
					( rcThumb.top + rcThumb.bottom ) / 2 - 24 );

		ImageList_DrawEx( ShellIcons.GetHandle( 48 ), m_nIcon, pDC->GetSafeHdc(),
			pt.x, pt.y, 48, 48, m_crLight, CLR_NONE, ILD_NORMAL );

		pDC->ExcludeClipRect( pt.x, pt.y, pt.x + 48, pt.y + 48 );
		pDC->FillSolidRect( &rcThumb, m_crLight );
	}
}