void CPlayerSeekBar::OnLButtonDown(UINT nFlags, CPoint point)
{
    CRect clientRect;
    GetClientRect(&clientRect);
    if (m_bEnabled && m_bHasDuration && clientRect.PtInRect(point)) {
        m_bHovered = false;
        SetCapture();
        MoveThumb(point);
        VERIFY(SetTimer(TIMER_HOVER_CAPTURED, HOVER_CAPTURED_TIMEOUT, nullptr));
    } else {
        auto pFrame = AfxGetMainFrame();
        if (!pFrame->m_fFullScreen) {
            MapWindowPoints(pFrame, &point, 1);
            pFrame->PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
        }
    }
}