void CTimelineView::PaintCursors(gdi::TimelineDC& dc)
{
	auto rect = dc.GetClientArea();

	CPen redpen(CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
	CPen greenpen(CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));

	dc.SelectPen(redpen);
	dc.MoveTo(m_cursorPosition, scaleBottom);
	dc.LineTo(m_cursorPosition, rect.bottom);

	dc.SelectPen(greenpen);
	dc.MoveTo(m_selectedPosition, scaleBottom);
	dc.LineTo(m_selectedPosition, rect.bottom);
}