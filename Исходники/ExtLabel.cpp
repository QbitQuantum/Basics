void CExtAviLabel::OnAviPaintCurrentFrame( CDC & dc, const CRect & rcDrawDst, const CSize & sizeAvi )
{
	ASSERT_VALID( this );
	ASSERT( GetSafeHwnd() != NULL );
	ASSERT( dc.GetSafeHdc() != NULL );
	if( sizeAvi.cx <= 0 || sizeAvi.cy <= 0 )
		return;
LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER)AVIStreamGetFrame(m_pGF, (LONG)m_nAviFrameCurrent);
//	ASSERT( pBIH != NULL );
	if( pBIH == NULL )
		return;
CExtMemoryDC dcProcessingSurface( &dc, rcDrawDst, CExtMemoryDC::MDCOPT_TO_MEMORY|CExtMemoryDC::MDCOPT_FORCE_DIB|CExtMemoryDC::MDCOPT_RTL_COMPATIBILITY );
	VERIFY(
		::DrawDibDraw(
			m_hDrawDib, dcProcessingSurface.GetSafeHdc(),
			rcDrawDst.left + m_ptAviOffset.x, rcDrawDst.top + m_ptAviOffset.y, sizeAvi.cx, sizeAvi.cy,
			pBIH, NULL, 0, 0, -1, -1, 0
			)
		);
COLORREF clrTransparentPixels = ( ( AviStyleGet() & __EXT_AVI_TRANSPARENT_VIDEO ) != 0 ) ? m_clrTransparentEffective : PmBridge_GetPM()->GetColor( COLOR_WINDOW );
	CExtPaintManager::stat_TransparentBlt(
		dc.m_hDC,
		rcDrawDst.left + m_ptAviOffset.x, rcDrawDst.top + m_ptAviOffset.y, sizeAvi.cx, sizeAvi.cy,
		dcProcessingSurface.GetSafeHdc(),
		rcDrawDst.left + m_ptAviOffset.x, rcDrawDst.top + m_ptAviOffset.y, sizeAvi.cx, sizeAvi.cy,
		clrTransparentPixels
		);
	dcProcessingSurface.__Flush( FALSE );
}