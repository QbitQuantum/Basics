bool CMouse::CursorOnRootWindow(const CPoint& screenPoint, const CFrameWnd& frameWnd)
{
    bool ret = false;
    CWnd* pWnd = CWnd::WindowFromPoint(screenPoint);
    CWnd* pRoot = pWnd ? pWnd->GetAncestor(GA_ROOT) : nullptr;
    if (pRoot) {
        ret = (pRoot->m_hWnd == frameWnd.m_hWnd);
    } else {
        ASSERT(FALSE);
    }
    return ret;
}