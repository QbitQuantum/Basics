void CColumnTreeView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    UNREFERENCED_PARAMETER( pScrollBar );

    CRect rcClient;
    GetClientRect(&rcClient);
    int cx = rcClient.Width();

    int xLast = m_xPos;

    switch (nSBCode)
    {
    case SB_LINELEFT:
        m_xPos -= 15;
        break;
    case SB_LINERIGHT:
        m_xPos += 15;
        break;
    case SB_PAGELEFT:
        m_xPos -= cx;
        break;
    case SB_PAGERIGHT:
        m_xPos += cx;
        break;
    case SB_LEFT:
        m_xPos = 0;
        break;
    case SB_RIGHT:
        m_xPos = m_cxTotal - cx;
        break;
    case SB_THUMBTRACK:
        m_xPos = nPos;
        break;
    }

    if (m_xPos < 0)
        m_xPos = 0;
    else if (m_xPos > m_cxTotal - cx)
        m_xPos = m_cxTotal - cx;

    if (xLast == m_xPos)
        return;

    SetScrollPos(SB_HORZ, m_xPos);
    RepositionControls();
}