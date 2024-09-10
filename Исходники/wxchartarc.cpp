void wxChartArc::Draw(wxGraphicsContext &gc)
{
	wxGraphicsPath path = gc.CreatePath();

	if (m_innerRadius > 0)
	{
		path.AddArc(m_x, m_y, m_innerRadius, m_startAngle, m_endAngle, true);
		path.AddArc(m_x, m_y, m_outerRadius, m_endAngle, m_startAngle, false);
	}
	else
	{
		path.AddArc(m_x, m_y, m_outerRadius, m_endAngle, m_startAngle, false);
		path.AddLineToPoint(m_x, m_y);
	}

	path.CloseSubpath();

	wxBrush brush(m_options.GetFillColor());
	gc.SetBrush(brush);
	gc.FillPath(path);

	wxPen pen(*wxWHITE, m_options.GetOutlineWidth());
	gc.SetPen(pen);
	gc.StrokePath(path);
}