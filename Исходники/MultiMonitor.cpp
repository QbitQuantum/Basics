BOOL CMonitor::IsOnMonitor(const CWnd* pWnd) const
{
    CRect rect;
    GetMonitorRect(rect);

    ASSERT(::IsWindow(pWnd->GetSafeHwnd()));
    CRect wndRect;
    pWnd->GetWindowRect(&wndRect);

    return rect.IntersectRect(rect, wndRect);
}