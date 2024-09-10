void CTrackerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTrackerDoc* pDoc = GetDocument();
	CRect rectSave;
	pDoc->m_tracker.GetTrueRect(rectSave);
	if (pDoc->m_tracker.HitTest(point) < 0)
	{
		// just to demonstrate CRectTracker::TrackRubberBand
		CRectTracker tracker;
		if (tracker.TrackRubberBand(this, point, pDoc->m_bAllowInvert))
		{
			MessageBeep(0); // beep indicates TRUE

			// see if rubber band intersects with the doc's tracker
			CRect rectT;
			tracker.m_rect.NormalizeRect(); // so intersect rect works
			if (rectT.IntersectRect(tracker.m_rect, pDoc->m_tracker.m_rect))
			{
				// if so, put resize handles on it (ie. select it)
				if (pDoc->m_tracker.m_nStyle & CRectTracker::resizeInside)
				{
					// swap from resize inside to resize outside for effect
					pDoc->m_tracker.m_nStyle &= ~CRectTracker::resizeInside;
					pDoc->m_tracker.m_nStyle |= CRectTracker::resizeOutside;
				}
				else
				{
					// just use inside resize handles on first time
					pDoc->m_tracker.m_nStyle &= ~CRectTracker::resizeOutside;
					pDoc->m_tracker.m_nStyle |= CRectTracker::resizeInside;
				}
				pDoc->SetModifiedFlag();
				pDoc->UpdateAllViews(NULL, (LPARAM)(LPCRECT)rectSave);
				pDoc->UpdateAllViews(NULL);
			}
		}
	}
	else if (pDoc->m_tracker.Track(this, point, pDoc->m_bAllowInvert))
	{
		// normal tracking action, when tracker is "hit"
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL, (LPARAM)(LPCRECT)rectSave);
		pDoc->UpdateAllViews(NULL);
	}
	CView::OnLButtonDown(nFlags, point);
}