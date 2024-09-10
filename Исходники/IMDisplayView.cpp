void CIMDisplayView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CIMDisplayDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    CRect rectSave;
    m_tracker.GetTrueRect(rectSave);
    if (m_tracker.HitTest(point) < 0)
    {
		// just to demonstrate CRectTracker::TrackRubberBand
		CRectTracker tracker;
		if (tracker.TrackRubberBand(this, point, true))
		{
			// MessageBeep(0); // beep indicates TRUE

			// see if rubber band intersects with the doc's tracker
			CRect rectT;
			tracker.m_rect.NormalizeRect(); // so intersect rect works
			if (rectT.IntersectRect(tracker.m_rect, m_tracker.m_rect))
			{
				/*
				// dotted line for outline
				m_tracker.m_nStyle &= CRectTracker::dottedLine;

				// if so, put resize handles on it (ie. select it)
				if (m_tracker.m_nStyle & CRectTracker::resizeInside)
				{
					// swap from resize inside to resize outside for effect
					m_tracker.m_nStyle &= ~CRectTracker::resizeInside;
					m_tracker.m_nStyle |= CRectTracker::resizeOutside;
				}
				else
				{
					// just use inside resize handles on first time
					m_tracker.m_nStyle &= ~CRectTracker::resizeOutside;
					m_tracker.m_nStyle |= CRectTracker::resizeInside;
				}
				*/

				UpdateTheView( false );
			}

			m_tracker.m_rect = tracker.m_rect;
		} else {	// clear the selection!
			m_tracker.m_rect.left	= m_tracker.m_rect.right = 0;
			m_tracker.m_rect.top	= m_tracker.m_rect.bottom = 0;
		}

		UpdateTheView( false );
    }
    else if (m_tracker.Track(this, point, true))
    {
		UpdateTheView( false );
    }

    CScrollView::OnLButtonDown(nFlags, point);
}