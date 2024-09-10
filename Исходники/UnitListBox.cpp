/**
 *
 * \param nFlags 
 * \param point 
 */
void	CUnitListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragging && m_pDragImage != NULL)
	{
		CPoint cPt(point);
		ClientToScreen(&cPt);

		m_pDragImage->DragMove(cPt);
		m_pDragImage->DragShowNolock(false);

		CWnd* pDropWnd = WindowFromPoint (cPt);
		if (pDropWnd)
		{
			pDropWnd->ScreenToClient(&cPt);

			if(pDropWnd->IsKindOf(RUNTIME_CLASS (CView)))
			{			
				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
			else
			{
				SetCursor(LoadCursor(NULL, IDC_NO));
			}

			m_pDragImage->DragShowNolock(true);
		}
	}
}