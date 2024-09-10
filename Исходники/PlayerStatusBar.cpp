void CPlayerStatusBar::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    for (CWnd* pChild = GetWindow(GW_CHILD); pChild; pChild = pChild->GetNextWindow()) {
        if (!pChild->IsWindowVisible()) {
            continue;
        }

        CRect r;
        pChild->GetClientRect(&r);
        pChild->MapWindowPoints(this, &r);
        dc.ExcludeClipRect(&r);
    }

    CRect r;
    GetClientRect(&r);

    if (m_pMainFrame->m_pLastBar != this || m_pMainFrame->m_fFullScreen) {
        r.InflateRect(0, 0, 0, 1);
    }

    if (m_pMainFrame->m_fFullScreen) {
        r.InflateRect(1, 0, 1, 0);
    }

    dc.Draw3dRect(&r, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

    r.DeflateRect(1, 1);

    dc.FillSolidRect(&r, 0);

    if (m_bm.m_hObject) {
        BITMAP bm;
        m_bm.GetBitmap(&bm);
        CDC memdc;
        memdc.CreateCompatibleDC(&dc);
        memdc.SelectObject(&m_bm);
        CRect clientRect;
        GetClientRect(&clientRect);
        CRect statusRect;
        m_status.GetWindowRect(statusRect);
        ScreenToClient(statusRect);
        dc.BitBlt(clientRect.right - bm.bmWidth - 1,
                  statusRect.CenterPoint().y - bm.bmHeight / 2,
                  bm.bmWidth, bm.bmHeight, &memdc, 0, 0, SRCCOPY);
    }
}