void CPreviewDC::MirrorAttributes()
{
	ASSERT(m_hAttribDC != NULL);

	if (m_hDC != NULL)
	{
		// extract and re-set Pen and Brush
		HGDIOBJ hTemp = ::SelectObject(m_hAttribDC, ::GetStockObject(BLACK_PEN));
		::SelectObject(m_hAttribDC, hTemp);
		::SelectObject(m_hDC, hTemp);
		hTemp = ::SelectObject(m_hAttribDC, ::GetStockObject(BLACK_BRUSH));
		::SelectObject(m_hAttribDC, hTemp);
		::SelectObject(m_hDC, hTemp);

		SetROP2(GetROP2());
		SetBkMode(GetBkMode());
		SetTextAlign(GetTextAlign());
		SetPolyFillMode(GetPolyFillMode());
		SetStretchBltMode(GetStretchBltMode());
		SetTextColor(GetNearestColor(GetTextColor()));
		SetBkColor(GetNearestColor(GetBkColor()));
	}
}