void CDragDropListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_pDragImage)
	{
		// Must be dragging, as there is a drag image.

		// Move the drag image.
		CPoint ptDragImage(point);
		ClientToScreen(&ptDragImage);
		m_pDragImage->DragMove(ptDragImage);
		
		// Leave dragging so we can update potential drop target selection.
		m_pDragImage->DragLeave(CWnd::GetDesktopWindow());

		// Force x coordinate to always be in list control - only interested in y coordinate.
		// In effect the list control has captured all horizontal mouse movement.
		static const int nXOffset = 8;
		CRect rect;
		GetWindowRect(rect);
		CWnd* pDropWnd = CWnd::WindowFromPoint(CPoint(rect.left + nXOffset, ptDragImage.y));

		// Get the window under the drop point.
		if (pDropWnd == this)
		{
			// Still in list control so select item under mouse as potential drop target.
			point.x = nXOffset;	// Ensures x coordinate is always valid.
			UpdateSelection(HitTest(point));
		}

		CRect rectClient;
		GetClientRect(rectClient);
		CPoint ptClientDragImage(ptDragImage);
		ScreenToClient(&ptClientDragImage);

		// Client rect includes header height, so ignore it, i.e.,
		// moving the mouse over the header (and higher) will result in a scroll up.
		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
		if (pHeader)
		{
			CRect rectHeader;
			pHeader->GetClientRect(rectHeader);
			rectClient.top += rectHeader.Height();
		}

		if (ptClientDragImage.y < rectClient.top)
		{
			// Mouse is above the list control - scroll up.
			SetScrollTimer(scrollUp);
		}
		else if (ptClientDragImage.y > rectClient.bottom)
		{
			// Mouse is below the list control - scroll down.
			SetScrollTimer(scrollDown);
		}
		else
		{
			KillScrollTimer();
		}

		// Resume dragging.
		m_pDragImage->DragEnter(CWnd::GetDesktopWindow(), ptDragImage);
	}
	else
	{
		KillScrollTimer();
	}

	CListCtrl::OnMouseMove(nFlags, point);
}