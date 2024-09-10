void
TextDocumentView::_GetSelectionShape(BShape& shape, int32 start, int32 end)
{
	float startX1;
	float startY1;
	float startX2;
	float startY2;
	fTextDocumentLayout.GetTextBounds(start, startX1, startY1, startX2,
		startY2);

	startX1 = floorf(startX1);
	startY1 = floorf(startY1);
	startX2 = ceilf(startX2);
	startY2 = ceilf(startY2);

	float endX1;
	float endY1;
	float endX2;
	float endY2;
	fTextDocumentLayout.GetTextBounds(end, endX1, endY1, endX2, endY2);

	endX1 = floorf(endX1);
	endY1 = floorf(endY1);
	endX2 = ceilf(endX2);
	endY2 = ceilf(endY2);

	int32 startLineIndex = fTextDocumentLayout.LineIndexForOffset(start);
	int32 endLineIndex = fTextDocumentLayout.LineIndexForOffset(end);

	if (startLineIndex == endLineIndex) {
		// Selection on one line
		BPoint lt(startX1, startY1);
		BPoint rt(endX1, endY1);
		BPoint rb(endX1, endY2);
		BPoint lb(startX1, startY2);

		shape.MoveTo(lt);
		shape.LineTo(rt);
		shape.LineTo(rb);
		shape.LineTo(lb);
		shape.Close();
	} else if (startLineIndex == endLineIndex - 1 && endX1 <= startX1) {
		// Selection on two lines, with gap:
		// ---------
		// ------###
		// ##-------
		// ---------
		float width = ceilf(fTextDocumentLayout.Width());

		BPoint lt(startX1, startY1);
		BPoint rt(width, startY1);
		BPoint rb(width, startY2);
		BPoint lb(startX1, startY2);

		shape.MoveTo(lt);
		shape.LineTo(rt);
		shape.LineTo(rb);
		shape.LineTo(lb);
		shape.Close();

		lt = BPoint(0, endY1);
		rt = BPoint(endX1, endY1);
		rb = BPoint(endX1, endY2);
		lb = BPoint(0, endY2);

		shape.MoveTo(lt);
		shape.LineTo(rt);
		shape.LineTo(rb);
		shape.LineTo(lb);
		shape.Close();
	} else {
		// Selection over multiple lines
		float width = ceilf(fTextDocumentLayout.Width());

		shape.MoveTo(BPoint(startX1, startY1));
		shape.LineTo(BPoint(width, startY1));
		shape.LineTo(BPoint(width, endY1));
		shape.LineTo(BPoint(endX1, endY1));
		shape.LineTo(BPoint(endX1, endY2));
		shape.LineTo(BPoint(0, endY2));
		shape.LineTo(BPoint(0, startY2));
		shape.LineTo(BPoint(startX1, startY2));
		shape.Close();
	}
}