void CListViewCtrlEx::OnMouseMove(UINT nFlags, CPoint point)
{
    TRACKMOUSEEVENT trkMouse;
    trkMouse.cbSize = sizeof( TRACKMOUSEEVENT );
    trkMouse.dwFlags = TME_LEAVE;
    trkMouse.hwndTrack = m_hWnd;

    // notify when the mouse leaves button
    _TrackMouseEvent( &trkMouse );

    CRect	rcItem;

    LVHITTESTINFO hti;
    hti.pt = point;
    SubItemHitTest( &hti );

    if( m_nHoverItem != hti.iItem || m_nHoverSubItem != hti.iSubItem)
    {
        m_nHoverItem = hti.iItem;
        m_nHoverSubItem = hti.iSubItem;
        _FireEvent(WMH_LISTEX_HOVERCHANGED, m_nHoverItem);

        KillTimer(XX_TIMER_ID_TIPS);
        //CBkSafeTip::Hide();
    }

    static CPoint ptLast;
    if (ptLast != point && hti.iItem != -1)
        SetTimer(XX_TIMER_ID_TIPS, 200);

    ptLast = point;
}