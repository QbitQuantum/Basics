LRESULT CHtmlColorCtrl::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    RECT rcClient;
    if( GetClientRect(&rcClient) ) {
        if(!m_bTrackingMouse) {
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(tme);
            tme.hwndTrack = m_hWnd;
            tme.dwFlags = /*TME_HOVER|*/TME_LEAVE;
            m_bTrackingMouse = TrackMouseEvent(&tme);
        }

        m_ptMouse.x=min(pt.x/BOX_SIZE, COL_COUNT-1);
        m_ptMouse.y=min(pt.y/BOX_SIZE, LINE_COUNT-1);

        CRect rcBtn(0, LINE_COUNT*BOX_SIZE+20, COL_COUNT*BOX_SIZE, rcClient.bottom);
        m_bOnButton=rcBtn.PtInRect(pt);
        if( m_bOnButton )
            m_ptMouse.x=m_ptMouse.y=-1;
        InvalidateRect(&rcClient);
    }

    return 0;
}