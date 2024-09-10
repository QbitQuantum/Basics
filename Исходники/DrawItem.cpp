void DrawItemShape::OnPaint( Graphics &g )
{
	if(isChangeRegion())
	{
		ResetRegion();
	}
	auto region = getRegion();
	SolidBrush brush(DrawTools::ColorNormal);
	if (m_isFillPath)
	{
		if (StateNormal == m_state)
		{
			g.FillRegion(&brush, region.get());
		}
		else if (StateHovered == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorHovered), region.get());
		}
		else if (StateDisable == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorDisable), region.get());
		}
		else if (StateDown == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorDown), region.get());
		}
		else if (StateError == m_state)
		{
			g.FillRegion(&SolidBrush(DrawTools::ColorError), region.get());
		}
		else
		{
			g.FillRegion(&SolidBrush(m_fillColor), region.get());
		}
	}
	if (m_isDrawPath)
	{
		GraphicsPath path;
		path.StartFigure();
		for(auto itter = m_lines.begin();itter != m_lines.end() ; itter++ )
		{
			(*itter)->getPath(path);
		}
		path.CloseFigure();

		g.DrawPath(&Pen(m_drawColor),&path);
	}
}