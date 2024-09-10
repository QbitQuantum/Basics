void CSetProxy::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragging)
	{
		CPoint pt (point);
		ClientToScreen (&pt);
		// move the drag image
		VERIFY (m_pDragImage->DragMove (pt));
		// unlock window updates
		VERIFY (m_pDragImage->DragShowNolock (FALSE));

		// get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT (pDropWnd);

		// convert from screen coordinates to drop target client coordinates
		pDropWnd->ScreenToClient (&pt);

		// if window is CTreeCtrl
		if (pDropWnd == m_pDropWnd)
		{			
			UINT uFlags;
			CListCtrl* pList = (CListCtrl*)pDropWnd;

			// turn off hilight for previous drop target
			pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);
			// redraw previous item
			pList->RedrawItems (m_nDropIndex, m_nDropIndex);
			
			// get the item that is below cursor
			m_nDropIndex = ((CListCtrl*)pDropWnd)->HitTest (pt, &uFlags);
			// highlight it
			if(m_nDropIndex>=0)
			{
				pList->SetItemState (m_nDropIndex, LVIS_DROPHILITED, LVIS_DROPHILITED);
				// redraw item
				pList->RedrawItems (m_nDropIndex, m_nDropIndex);
				pList->UpdateWindow ();
			}
		}
		// lock window updates
		VERIFY (m_pDragImage->DragShowNolock (TRUE));
	}
	
	CDialog::OnMouseMove(nFlags, point);
}