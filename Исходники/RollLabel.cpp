void CRollLabel::OnPaint()
{
	CPaintDC dc(this);
	
	DWORD dwLayout;
	GetProcessDefaultLayout(&dwLayout);
	if (LAYOUT_RTL & dwLayout) 
		dc.SetLayout(LAYOUT_RTL);

	dc.SetBkMode(TRANSPARENT);
	CFont *pOldFont = dc.SelectObject(&m_ftText);
	dc.SetTextColor(m_crText);

	if (m_bRollTimer)
	{
		dc.TextOut(m_nCurXPos, m_nCurYPos, m_strText);
	}
	else
	{
		UINT uFormat = DT_VCENTER|DT_SINGLELINE;
		if (m_nTextAlign == ELCRLABEL_TEXT_ALIGN_LEFT)
			uFormat |= DT_LEFT;
		else if (m_nTextAlign == ELCRLABEL_TEXT_ALIGN_CENTER)
			uFormat |= DT_CENTER;
		else if (m_nTextAlign == ELCRLABEL_TEXT_ALIGN_RIGHT)
			uFormat |= DT_RIGHT;
		dc.DrawText(m_strText, m_rcClient, uFormat);
	}

	dc.SelectObject(pOldFont);
}