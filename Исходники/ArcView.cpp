void CArcView::computeEnclosingRect(BOOL init)
{
	CRect unionRect;
	Point currentPoint(*pathPoints.begin());
	for(auto it=pathPoints.begin() + 1; it != pathPoints.end(); ++it)
	{
		//Union des rectangles.
		CRect toAddRect(currentPoint.X, currentPoint.Y, it->X, it->Y);
		toAddRect.NormalizeRect();
		if(toAddRect.Width() == 0) toAddRect.InflateRect(1,0);
		if(toAddRect.Height() == 0) toAddRect.InflateRect(0,1);
		unionRect.UnionRect(unionRect, toAddRect);

		currentPoint = *it;
	}

	if(init)
		enclosingRect = new Rect(unionRect.left, unionRect.top, unionRect.Width(), unionRect.Height());
	else
	{
		enclosingRect->X = unionRect.left;
		enclosingRect->Y = unionRect.top;
		enclosingRect->Width = unionRect.Width();
		enclosingRect->Height = unionRect.Height();
	}
}