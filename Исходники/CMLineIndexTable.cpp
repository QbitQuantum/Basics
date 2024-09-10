void
CMLineIndexTable::TableDrawCell
	(
	JPainter&		p,
	const JPoint&	cell,
	const JRect&	rect
	)
{
	HilightIfSelected(p, cell, rect);

	if (JIndex(cell.x) == kBreakpointColumn)
		{
		DrawBreakpoints(p, cell, rect);
		}

	else if (JIndex(cell.x) == kExecPointColumn && cell.y == itsCurrentLineIndex)
		{
		// We can't use a static polygon because line heights can vary,
		// e.g. due to underlines.

		const JCoordinate delta = rect.height()/2;

		JPolygon poly;
		poly.AppendElement(JPoint(rect.left+kMarginWidth,       rect.top));
		poly.AppendElement(JPoint(rect.left+kMarginWidth+delta, rect.top + delta));
		poly.AppendElement(JPoint(rect.left+kMarginWidth,       rect.top + 2*delta));

		p.SetPenColor(GetCurrentLineMarkerColor());
		p.SetFilling(kJTrue);
		p.Polygon(poly);

		p.SetPenColor(GetColormap()->GetBlackColor());
		p.SetFilling(kJFalse);
		p.Polygon(poly);
		}

	else if (JIndex(cell.x) == kLineNumberColumn)
		{
		p.SetFont(itsText->GetDefaultFont());

		JRect r  = rect;
		r.right -= kMarginWidth;

		const JString str = GetLineText(cell.y);
		p.String(r, str, JPainter::kHAlignRight);
		}
}