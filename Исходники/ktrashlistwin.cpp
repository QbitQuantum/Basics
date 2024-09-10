BOOL CTrashCleanCtrl::SetSelectedItem(UINT nItemID)
{
    BOOL bRet = FALSE;
    size_t iCount, jCount;
    SCROLLINFO si;
    int nItemHeiht = 0;

    if (nItemID < 0)
        goto Clear0;

    for (iCount = 0; iCount < m_vecTrashItems.size(); ++iCount)
    {
        if (!m_vecTrashItems[iCount].bShow)
        {
            continue;
        }
        for (jCount = 0; jCount < m_vecTrashItems[iCount].vecItems.size(); ++jCount)
        {
            if (nItemID == m_vecTrashItems[iCount].vecItems[jCount].nItemId)
            {
                m_nSelectedIndex = m_vecTrashItems[iCount].vecItems[jCount].nItemId;
                m_vecTrashItems[iCount].bShowDetail = TRUE;
                nItemHeiht = m_vecTrashItems[iCount].vecItems[jCount].rcCheck.top;
                if (nItemHeiht == 0)
                    nItemHeiht = m_vecTrashItems[iCount].rcBox.bottom;
                bRet = TRUE;
                break;
            }
        }
        if (bRet) break;
    }
    
    if (bRet)
    {
        si.cbSize = sizeof si;
        si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
        GetScrollInfo(SB_VERT, &si);

        si.fMask = SIF_POS;

        m_nPos = (nItemHeiht - (int)si.nPage / 4);

        if (m_nPos < 0)
            m_nPos = 0;

        si.nPos = m_nPos;

        SetScrollInfo(SB_VERT, &si, TRUE);
    }

Clear0:
    return bRet;
}