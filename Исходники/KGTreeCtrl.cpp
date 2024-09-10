void KGTreeCtrl::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == m_nHoverTimerID)
	{
		KillTimer(m_nHoverTimerID);
		m_nHoverTimerID = 0;
		HTREEITEM  trItem = 0;
		UINT  uFlag = 0;
		trItem = HitTest(m_HoverPoint, &uFlag);
		if (trItem && m_bDragging)
		{
			//SelectItem(trItem);
			Expand(trItem, TVE_EXPAND);
			Invalidate();

			CRect rect;
			GetItemRect(trItem, &rect, true);
			rect.left -= 35;
			m_curPointLeft.x = rect.left;
			m_curPointLeft.y = rect.bottom;
			m_curPointRigh.x = rect.right;
			m_curPointRigh.y = rect.bottom;
		}
	}
	else if(nIDEvent == m_nScrollTimerID)
	{
		m_TimerTicks++;
		CPoint  pt;
		GetCursorPos(&pt);
		CRect  rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);

		HTREEITEM  hItem = GetFirstVisibleItem();

		if ( pt.y < rect.top +10)
		{
			int  slowscroll = 6 - (rect.top + 10 - pt.y )/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEUP );
				SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
		else if( pt.y > rect.bottom - 10 )
		{
			int  slowscroll = 6 - (pt.y - rect.bottom + 10)/20;
			if( 0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)) )
			{
				CImageList::DragShowNolock ( false );
				SendMessage( WM_VSCROLL,SB_LINEDOWN );
				int  nCount = GetVisibleCount();
				for( int i=0 ; i<nCount-1 ; i++ )
					hItem = GetNextVisibleItem( hItem );
				if( hItem )
					SelectDropTarget( hItem );
				m_hItemDragD = hItem;
				CImageList::DragShowNolock ( true );
			}
		}
	}
	else if (nIDEvent == m_nDrawLineTimerID)
	{
		CClientDC dc(this);

		CPen penP(PS_SOLID, 2, GetBkColor());
		dc.SelectObject(&penP);
		dc.MoveTo(m_pointLeft);
		dc.LineTo(m_pointRigh);
		dc.MoveTo(m_pointLeft.x, m_pointLeft.y - 5);
		dc.LineTo(m_pointLeft.x, m_pointLeft.y + 5);

		CPen penN(PS_SOLID, 2, RGB(122, 178, 255));
		dc.SelectObject(&penN);
		dc.MoveTo(m_curPointLeft);
		dc.LineTo(m_curPointRigh);
		dc.MoveTo(m_curPointLeft.x, m_curPointLeft.y - 5);
		dc.LineTo(m_curPointLeft.x, m_curPointLeft.y + 5);

		m_pointLeft.x = m_curPointLeft.x;
		m_pointLeft.y = m_curPointLeft.y;
		m_pointRigh.x = m_curPointRigh.x;
		m_pointRigh.y = m_curPointRigh.y;
	}
	else
		CTreeCtrl::OnTimer(nIDEvent);
}