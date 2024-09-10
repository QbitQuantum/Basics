void CHTMLSection::OnDraw( GS::CDrawContext &dc )
{
	HBRUSH hbr = NULL;
	if( GetBackgroundColours( dc.GetSafeHdc(), hbr ) )
	{
		FillRect( dc.GetSafeHdc(), *this, hbr );
	}
	else if( !IsTransparent() )
	{
		if( m_pDocument )
		{
			if( !m_pDocument->m_back.Draw( dc, *this ) )
			{
				dc.FillRect( *this, m_pDefaults->m_crBackground );
			}

			if( m_pDocument->m_pimgBackground )
			{
				const int nPosX = left - GetScrollPosH();
				const int nPosY = top - GetScrollPos();
				DrawTiledBitmap( nPosX, nPosY, max( GetMaxWidth(), (UINT)Width() ), max( GetMaxHeight(), (UINT)Height() ), dc.GetSafeHdc(), m_pDocument->m_pimgBackground, m_nBackgroundFrame );
			}
		}
		else
		{
			dc.FillRect( *this, m_pDefaults->m_crBackground );
		}
	}
	CScrollContainer::OnDraw( dc );
}