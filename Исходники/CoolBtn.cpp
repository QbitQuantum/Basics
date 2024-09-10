////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	  OnMouseMove
//
// DESCRIPTION:	Tracks mouse whilst pressed
//
//
// NOTES:
//
// MAINTENANCE:
// Name:		  Date:	  Version:	Notes:
// NT ALMOND	210100	1.0			  Origin
//
////////////////////////////////////////////////////////////////////////////////
void CCoolBtn::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bPushed)
    {
        ClientToScreen(&point);

        if (WindowFromPoint(point) != this)
        {
            m_bPushed = FALSE;
            ReleaseCapture();
            Invalidate();
        }
    }
    if (!m_bTracking)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = m_hWnd;
        tme.dwFlags = TME_LEAVE|TME_HOVER;
        tme.dwHoverTime = 1;
        m_bTracking = _TrackMouseEvent(&tme) != FALSE;
    }

    CButton::OnMouseMove(nFlags, point);
}