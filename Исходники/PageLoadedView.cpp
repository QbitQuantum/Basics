void CPageLoadedView::DoPaint(WTL::CDCHandle & dc, CRect rect) const
{
	DWORD win_color = GetSysColor(COLOR_3DFACE);
	DWORD page_color = GetSysColor(COLOR_WINDOW);
	DWORD requested_color = GetSysColor(COLOR_INACTIVECAPTION);
	DWORD loaded_color = GetSysColor(COLOR_ACTIVECAPTION);

	WORD wHue, wLuminance, wSaturation;	
	ColorRGBToHLS(loaded_color, &wHue, &wLuminance, &wSaturation);
	wHue = 80;
	DWORD fully_loaded_color = ColorHLSToRGB(wHue, wLuminance, wSaturation);

	dc.DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);
	rect.DeflateRect(1, 1, 1, 1);
	dc.FillSolidRect(rect, win_color);
	RowRangeVector::const_iterator itr = m_loaded.begin(); 
	if (m_loaded.size() == 1 && itr->m_state == RowRange::S_LOADED)
	{
		dc.FillSolidRect(rect, fully_loaded_color);
	}
	else
	{
		int previous_bottom = rect.top;
		for(; itr != m_loaded.end(); ++itr)
		{
			CRect r = rect;	//For Width;
			r.top = rect.top + MulDiv(itr->m_from, rect.Height(), m_total) - 1;
			if (r.top > previous_bottom)
			{
				r.top = previous_bottom;
			}
			r.bottom = rect.top + MulDiv(itr->m_to, rect.Height(), m_total);
			switch (itr->m_state)
			{
			case RowRange::S_BLANK:
				dc.FillSolidRect(r, page_color);
				break;
			case RowRange::S_REQUESTED:
				dc.FillSolidRect(r, requested_color);
				break;
			case RowRange::S_LOADED:
				dc.FillSolidRect(r, loaded_color);
				break;
			}
			previous_bottom = r.bottom;
		}
	}
}