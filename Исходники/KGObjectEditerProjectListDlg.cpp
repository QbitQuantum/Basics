void KGClassButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CClientDC dc(this);
	COLORREF color;
	CRect rect;
	CPen  pen;

	GetClientRect(&rect);
	dc.FillRect(&rect, &CBrush(RGB(255, 255, 255)));
	if (m_nStateFlag)
	{
		color = RGB(255, 2, 2);
	}
	else
	{
		color = RGB(100, 100, 100);
	}

	pen.CreatePen(PS_SOLID, 2, color);
	dc.SelectObject(&pen);

	if (m_hButtonIcon)
	{
		dc.DrawIcon(rect.left, rect.top, m_hButtonIcon);
	}

	if (m_nSelFlag)
	{
		dc.MoveTo(rect.left, rect.top);
		dc.LineTo(rect.right, rect.top);
		dc.LineTo(rect.right, rect.bottom);
		dc.LineTo(rect.left, rect.bottom);
		dc.LineTo(rect.left, rect.top - 2);
	}
}