void CFastSplitter::OnMouseMove(UINT nFlags, CPoint point) 
{

	if (m_mode == MOD_Normal)
	{
		if (m_bDragging || m_SplitterRect.PtInRect(point))
		{
			::SetCursor( AfxGetApp()->LoadStandardCursor(LPCTSTR (m_bVertSplitter ? IDC_SIZEWE : IDC_SIZENS)));
			if (m_bDragging)
			{
				if (m_bLiveUpdate)
				{
					if (m_bVertSplitter)
						m_SplitterPos = m_BarPos + point.x - m_DragStartPoint.x;
					else
						m_SplitterPos = m_BarPos + point.y - m_DragStartPoint.y;
					MovePanes();
				}
				else
				{
					if (m_bVertSplitter)
						m_BarPos = m_RealSplitterPos + point.x - m_DragStartPoint.x;
					else
						m_BarPos = m_RealSplitterPos + point.y - m_DragStartPoint.y;
					DrawBar();	
				}
			}
			else if (!m_bTracking)
			{
				//TRACE(_T("CFastSplitter::OnMouseMove !m_bTracking\r\n"));
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = m_hWnd;
				tme.dwFlags = TME_LEAVE;
				tme.dwHoverTime = HOVER_DEFAULT;
				m_bTracking = _TrackMouseEvent(&tme);

				HWND hWnd = GetSafeHwnd();
				if ((hWnd != NULL) && ::IsWindow (hWnd))
					InvalidateRect(&m_SplitterRect);
			}
		}
		else
		{
			//TRACE(_T("CFastSplitter::OnMouseMove !m_bDragging !m_bTracking\r\n"));

		}
	}

	CWnd::OnMouseMove(nFlags, point);
}