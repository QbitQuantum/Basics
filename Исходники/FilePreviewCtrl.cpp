LRESULT CFilePreviewCtrl::OnVScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // React to the various vertical scroll related actions.
    // CAUTION:
    // All sizes are in unsigned values, so be carefull
    // when testing for < 0 etc

    SCROLLINFO info;
    int nVScrollInc;
    int  nOldVScrollPos = m_nVScrollPos;

    switch (LOWORD(wParam))
    {
    case SB_TOP:
        m_nVScrollPos = 0;
        break;

    case SB_BOTTOM:
        m_nVScrollPos = m_nVScrollMax - m_nMaxLinesPerPage + 1;
        break;

    case SB_LINEUP:
        if(m_nVScrollPos > 0) --m_nVScrollPos;
        break;

    case SB_LINEDOWN:
        m_nVScrollPos++;
        break;

    case SB_PAGEUP:
        m_nVScrollPos -= max(1, m_nMaxLinesPerPage);
        if(m_nVScrollPos > nOldVScrollPos) m_nVScrollPos = 0;
        break;

    case SB_PAGEDOWN:
        m_nVScrollPos += max(1, m_nMaxLinesPerPage);
        break;

    case SB_THUMBPOSITION:
        info.cbSize = sizeof(SCROLLINFO);
        info.fMask = SIF_TRACKPOS;
        GetScrollInfo(SB_VERT, &info);
        m_nVScrollPos = info.nTrackPos;
        break;

    case SB_THUMBTRACK:
        info.cbSize = sizeof(SCROLLINFO);
        info.fMask = SIF_TRACKPOS;
        GetScrollInfo(SB_VERT, &info);
        m_nVScrollPos = info.nTrackPos;
        break;

    default:
        nVScrollInc = 0;
    }

    //keep scroll position in range
    if(m_nVScrollPos > m_nVScrollMax - m_nMaxLinesPerPage+1)
        m_nVScrollPos = m_nVScrollMax - m_nMaxLinesPerPage+1;

    if(m_nVScrollPos<0)
        m_nVScrollPos = 0;

    nVScrollInc = m_nVScrollPos - nOldVScrollPos;

    if (nVScrollInc)
    {

        //finally setup the actual scrollbar!
        info.cbSize = sizeof(SCROLLINFO);
        info.fMask = SIF_POS;
        info.nPos = m_nVScrollPos;
        SetScrollInfo(SB_VERT, &info, TRUE);

        InvalidateRect(NULL);
    }

    return 0;
}