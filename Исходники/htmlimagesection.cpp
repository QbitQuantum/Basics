void CHTMLImageSection::OnDraw( GS::CDrawContext &dc )
{
	if( m_pImage )
	{
		if( m_nBorder )
		{
			COLORREF clr = RGB( 0, 0, 0 );
			
			//
			//	Top border
			WinHelper::CRect rc( left, top, right, top + m_nBorder );
			dc.FillRect( rc, clr );

			//
			//	Bottom border
			rc.bottom = bottom;
			rc.top = bottom - m_nBorder;
			dc.FillRect( rc, clr );

			//
			//	Left border
			rc.top = top;
			rc.right = rc.left + m_nBorder;
			dc.FillRect( rc, clr );

			//
			//	Right border
			rc.right = right;
			rc.left = right - m_nBorder;
			dc.FillRect( rc, clr );

			(void)m_pImage->StretchFrame( m_nFrame, dc.GetSafeHdc(), left + m_nBorder, top + m_nBorder, right - m_nBorder, bottom - m_nBorder );
		}
		else
		{
			(void)m_pImage->StretchFrame( m_nFrame, dc.GetSafeHdc(), left, top, right, bottom );
		}
	}
	else
	{
		static TCHAR sz[] = _T("Image missing");

		dc.SelectFont( g_defaults.m_strFontName, GetFontSizeAsPixels( dc.GetSafeHdc(), g_defaults.m_nFontSize, 0 ), FW_NORMAL, false, false, false, g_defaults.m_cCharSet );

		dc.DrawText( left, top, sz, countof( sz ) - 1, 0 );
		dc.Rectangle( *this, CHTMLSectionABC::LinkHoverColour() );
	}

	if( IsMouseInSection() && IsLink() )
	{
		dc.Rectangle( *this, CHTMLSectionABC::LinkHoverColour() );
	}
#ifdef DRAW_DEBUG
	//	Do this after the image so it draws on top!
	CHTMLSectionABC::OnDraw( dc );
#endif	//	DRAW_DEBUG
}