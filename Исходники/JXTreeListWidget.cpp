void
JXTreeListWidget::TableDrawCell
	(
	JPainter&		p,
	const JPoint&	cell,
	const JRect&	rect
	)
{
	if (JIndex(cell.x) == itsNodeColIndex && itsDrawSelectionFlag)
		{
		HilightIfSelected(p, cell, rect);
		}

	const JTreeNode* node = itsTreeList->GetNode(cell.y);
	if (JIndex(cell.x) == itsToggleOpenColIndex && node->IsOpenable())
		{
		p.ShiftOrigin(rect.topLeft());

		const JPolygon* triangle = (itsTreeList->IsOpen(cell.y) ?
									&kOpenTriangle : &kClosedTriangle);
		if (kOpenTriangle.IsEmpty())
			{
			kOpenTriangle.AppendElement(JPoint(5,  6));
			kOpenTriangle.AppendElement(JPoint(15, 6));
			kOpenTriangle.AppendElement(JPoint(10, 11));

			kClosedTriangle.AppendElement(JPoint(10, 3));
			kClosedTriangle.AppendElement(JPoint(15, 8));
			kClosedTriangle.AppendElement(JPoint(10, 13));
			}

		const JColormap* colormap = p.GetColormap();

		if ((itsToggleDragIndex == cell.y && itsMouseInToggleFlag) ||
			itsDNDTargetIndex == JIndex(cell.y))
			{
			p.SetFilling(kJTrue);
			p.SetPenColor(colormap->GetBlackColor());
			p.Polygon(*triangle);
			}
		else
			{
			p.SetFilling(kJTrue);
			p.SetPenColor(colormap->GetGrayColor(90));
			p.Polygon(*triangle);

			p.SetFilling(kJFalse);
			p.SetPenColor(colormap->GetBlackColor());
			p.Polygon(*triangle);
			}

		p.ShiftOrigin(-(rect.topLeft()));
		}

	else if (JIndex(cell.x) == itsNodeColIndex)
		{
		JRect r = rect;
		r.left += GetNodeIndent(cell.y);
		p.SetClipRect(r);
		TLWDrawNode(p, cell, r);
		// Table controls clip rect, so we don't have to reset it.
		}
}