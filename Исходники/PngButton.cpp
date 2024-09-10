void PngButton::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if(!m_bOver)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = m_hWnd;
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = 1;

        _TrackMouseEvent(&tme);
    }


    if (m_bHandCursor)
    {
        HCURSOR hCur = LoadCursor(NULL, IDC_HAND);
        ::SetCursor(hCur);
    } else
    {
        HCURSOR hCur = LoadCursor(NULL, IDC_ARROW);
        ::SetCursor(hCur);
    }

    CWnd::OnMouseMove(nFlags, point);
}