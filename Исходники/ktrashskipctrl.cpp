LRESULT CTrashSkipCtrl::OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SCROLLINFO si;
    int vertPos;

    si.cbSize = sizeof si;
    si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
    GetScrollInfo(SB_VERT, &si);

    vertPos = si.nPos;

    switch (LOWORD(wParam))
    {
    case SB_TOP:
        si.nPos = si.nMin;
        break;

    case SB_BOTTOM:
        si.nPos = si.nMax;
        break;

    case SB_LINEUP:
        si.nPos -= 1;
        break;

    case SB_LINEDOWN:
        si.nPos += 1;
        break;

    case SB_PAGEUP:
        si.nPos -= si.nPage;
        break;

    case SB_PAGEDOWN:
        si.nPos += si.nPage;
        break;

    case SB_THUMBTRACK:
        si.nPos = si.nTrackPos;
        break;

    default:
        break;
    }

    si.fMask = SIF_ALL;

    m_nPos = abs(si.nPos);
    SetScrollInfo(SB_VERT, &si, TRUE);
    int nScrollHeight = int((m_rcRealClient.Height() - m_rcClient.Height()) * (m_nPos * 1.0) / (m_rcRealClient.Height()));
    int n = (m_nHeight - nScrollHeight);
    if (n > 1 || n < -1)
    {
        Invalidate();
    }
    bHandled = FALSE;
    return TRUE;
}