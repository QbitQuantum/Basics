//draw client area
void WeaselPanel::DoPaint(CDCHandle dc)
{
	CRect rc;
	GetClientRect(&rc);

	if (!m_status.composing)
	{
		if (m_status.ascii_mode)
			dc.DrawIconEx(0, 0, m_iconAlpha, 0, 0);
		else
			dc.DrawIconEx(0, 0, m_iconEnabled, 0, 0); 
		return;
	}

	// background
	{
		CBrush brush;
		brush.CreateSolidBrush(m_style.back_color);
		CRgn rgn;
		rgn.CreateRectRgnIndirect(&rc);
		dc.FillRgn(rgn, brush);

		CPen pen;
		pen.CreatePen(PS_SOLID | PS_INSIDEFRAME, m_style.border, m_style.border_color);
		CPenHandle oldPen = dc.SelectPen(pen);
		CBrushHandle oldBrush = dc.SelectBrush(brush);
		dc.Rectangle(&rc);
		dc.SelectPen(oldPen);
		dc.SelectBrush(oldBrush);
	}

	long height = -MulDiv(m_style.font_point, dc.GetDeviceCaps(LOGPIXELSY), 72);

	CFont font;
	font.CreateFontW(height, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, m_style.font_face.c_str());
	CFontHandle oldFont = dc.SelectFont(font);

	dc.SetTextColor(m_style.text_color);
	dc.SetBkColor(m_style.back_color);
	dc.SetBkMode(TRANSPARENT);
	
	bool drawn = false;

	// draw preedit string
	if (!m_style.inline_preedit)
		drawn |= _DrawPreedit(m_ctx.preedit, dc, m_layout->GetPreeditRect());
	
	/* FIXME: What's this?
	// ascii mode icon
	if (m_status.ascii_mode && y > rc.top)
	{
		int icon_x = rc.right - STATUS_ICON_SIZE;
		int icon_y = (rc.top + y - m_style.spacing - STATUS_ICON_SIZE) / 2;
		dc.DrawIconEx(icon_x, icon_y, m_iconAlpha, 0, 0);
	}*/

	/* TODO: Deprecated? */
	// draw auxiliary string
	drawn |= _DrawPreedit(m_ctx.aux, dc, m_layout->GetAuxiliaryRect());

	// draw candidates
	drawn |= _DrawCandidates(dc);

	/* Nothing drawn, hide candidate window */
	if (!drawn)
		ShowWindow(SW_HIDE);

	dc.SelectFont(oldFont);	
}