int CAxRectTracker::HitTest(CPoint point) const
{
	TrackerHit hitResult = hitNothing;
	CRect rectTrue;
	GetTrueRect(&rectTrue);
	ASSERT(rectTrue.left <= rectTrue.right);
	ASSERT(rectTrue.top  <= rectTrue.bottom);
	if (rectTrue.PtInRect(point))
	{
		if ((m_nStyle & (resizeInside|resizeOutside)) != 0)
			hitResult = (TrackerHit)HitTestHandles(point);
		else
			hitResult = hitMiddle;
	}
	return hitResult;
}