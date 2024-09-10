bool CPrintFolder::PrintHeaders(CDCHandle dc, UINT nPage)
{
	try
	{
		int nBkMode = dc.SetBkMode(TRANSPARENT);
		COLORREF clrTextColor = dc.SetTextColor(RGB(0,0,0));				

		// Draw header and footer!!
		if (m_bShowFooter || m_bShowPageNumbers)
		{
			HFONT hOldFont = dc.SelectFont(m_font);

			int cy = _rectExtents.bottom - (m_nFooterHeight - m_nPadding);
			
			dc.MoveTo(_rectExtents.left + m_nPadding, cy);
			dc.LineTo(_rectExtents.right - m_nPadding, cy);
			
			CRect r(_rectExtents.left, cy, _rectExtents.right, _rectExtents.bottom);
			
			if (m_bShowFooter)
			{
				
				DWORD dwStyle = DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;
				dwStyle |= (!m_bShowPageNumbers) ? DT_CENTER : DT_LEFT;
				dc.DrawText(_strFooter, -1, r, dwStyle);
			}

			if (m_bShowPageNumbers)
			{
				
				DWORD dwStyle = DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;
				dwStyle |= (!m_bShowFooter) ? DT_CENTER : DT_RIGHT;

				CString str;
				str.Format(IDS_PRINT_PAGE_FMT, nPage + 1, GetPageCount());
				dc.DrawText(str, -1, &r, dwStyle);
			}

			dc.SelectFont(hOldFont);
		}
		
		if (m_bShowHeader)
		{
			int cy = (_rectExtents.top + m_nHeaderHeight) - m_nPadding;
			
			dc.MoveTo(_rectExtents.left + m_nPadding, cy);
			dc.LineTo(_rectExtents.right - m_nPadding, cy);
			
			CRect r(_rectExtents.left, _rectExtents.top, _rectExtents.right, cy);
			
			HFONT hOldFont = dc.SelectFont(m_fontTitle);
			dc.DrawText(_strHeader, -1, &r, 
				DT_NOCLIP | DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX);
			dc.SelectFont(hOldFont);
		}

		dc.SetBkMode(nBkMode);
		dc.SetTextColor(clrTextColor);
	}
	catch(_com_error &e) 
	{
		IW::CMessageBoxIndirect mb;
		mb.ShowException(IDS_LOW_LEVEL_ERROR_FMT, e);
	}

	return true;
}