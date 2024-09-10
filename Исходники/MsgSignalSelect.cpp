void CMsgSignalSelect::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    int iXDelta = cx - m_szInitial.cx;
    int iYDelta = cy - m_szInitial.cy;
    HDWP hDefer = NULL;
    for (MovingChildren::iterator p = m_MovingChildren.begin();  p != m_MovingChildren.end();  ++p)
    {
        if (p->m_hWnd != NULL)
        {
            CRect rcNew(p->m_rcInitial);
            rcNew.OffsetRect(int(iXDelta * p->m_dXMoveFrac), int(iYDelta * p->m_dYMoveFrac));
            rcNew.right += int(iXDelta * p->m_dXSizeFrac);
            rcNew.bottom += int(iYDelta * p->m_dYSizeFrac);
            if (hDefer == NULL)
            {
                hDefer = BeginDeferWindowPos(m_MovingChildren.size());
            }
            UINT uFlags = SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER;
            if ((p->m_dXSizeFrac != 0.0) || (p->m_dYSizeFrac != 0.0))
            {
                uFlags |= SWP_NOCOPYBITS;
            }
            DeferWindowPos(hDefer, p->m_hWnd, NULL, rcNew.left, rcNew.top, rcNew.Width(), rcNew.Height(), uFlags);
        }
    }
    if (hDefer != NULL)
    {
        EndDeferWindowPos(hDefer);
    }

    //if (m_hGripper != NULL)
    //   ::ShowWindow(m_hGripper, (nType == SIZE_MAXIMIZED) ? SW_HIDE : SW_SHOW);
}