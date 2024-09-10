void CBSObject::OnMouseMove(UINT nFlags, CPoint point)
{
    if (!m_bIsEnable)
    {
       
        return;
    }
    if (!m_bIsSelect )
	{
       
		if (!m_isHover)
		{			

          
			m_isHover = TRUE;

            if (m_isHoverEnabled)
            {
                
                PaintParent();
			    Invalidate();
            }
		}
	}

    if (!m_bIsSelect && m_isHover && GetCapture() != this)
    {

        TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize = sizeof (TRACKMOUSEEVENT);
		TrackMouseEvent.dwFlags = TME_LEAVE;
		TrackMouseEvent.hwndTrack = GetSafeHwnd();
		TrackMouseEvent.dwHoverTime = 0;
		_TrackMouseEvent(&TrackMouseEvent);

    }
    else if (!m_bIsSelect && m_isHover)
    {
        CRect rt;
        GetWindowRect(&rt);
        ScreenToClient(&rt);

        if (!rt.PtInRect(point))
        {
            TRACKMOUSEEVENT TrackMouseEvent;
		    TrackMouseEvent.cbSize = sizeof (TRACKMOUSEEVENT);
		    TrackMouseEvent.dwFlags = TME_LEAVE;
		    TrackMouseEvent.hwndTrack = GetSafeHwnd();
		    TrackMouseEvent.dwHoverTime = 0;
		    _TrackMouseEvent(&TrackMouseEvent);
        }
        
    }

    CWnd::OnMouseMove(nFlags, point);
}