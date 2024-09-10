CSize CToolbarWnd::CalcDynamicLayout(int nLength, DWORD dwMode)
{
    CFrameWnd* pFrm = GetDockingFrame();

    // This function is typically called with
    // CSize sizeHorz = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK);
    // CSize sizeVert = m_pBar->CalcDynamicLayout(0, LM_VERTDOCK);
    // CSize sizeFloat = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH);

    CRect rcFrmClnt;
    pFrm->GetClientRect(&rcFrmClnt);
    CRect rcInside = rcFrmClnt;
    CalcInsideRect(rcInside, dwMode & LM_HORZDOCK);
    CRect rcBorders;
    rcBorders.left = rcInside.left - rcFrmClnt.left;
    rcBorders.top = rcInside.top - rcFrmClnt.top;
    rcBorders.bottom = rcFrmClnt.bottom - rcInside.bottom;
    rcBorders.right = rcFrmClnt.right - rcInside.right;

    if (dwMode & (LM_HORZDOCK | LM_VERTDOCK))
    {
        if (dwMode & LM_VERTDOCK)
        {
            CSize szFloat;
            szFloat.cx = MIN_VERT_WIDTH;
            szFloat.cy = rcFrmClnt.Height() + GetSystemMetrics(SM_CYEDGE) * 2;
            m_szFloat = szFloat;
            return szFloat;
        }
        else if (dwMode & LM_HORZDOCK)
        {
            CSize szFloat;
            szFloat.cx = rcFrmClnt.Width() + GetSystemMetrics(SM_CXEDGE) * 2;
            szFloat.cy = m_sizeDefault.cy + rcBorders.top + rcBorders.bottom;
            m_szFloat = szFloat;
            return szFloat;
        }
        return CDialogBar::CalcDynamicLayout(nLength, dwMode);
    }

    if (dwMode & LM_MRUWIDTH) {
        return m_szMRU;
    }
    if (dwMode & LM_COMMIT) {
        m_szMRU = m_szFloat;
        return m_szFloat;
    }

    CSize szFloat;
    if ((dwMode & LM_LENGTHY) == 0)
    {
        szFloat.cx = nLength;
        if (nLength < m_sizeDefault.cx + rcBorders.left + rcBorders.right)
        {
            szFloat.cx = MIN_VERT_WIDTH;
            szFloat.cy = MIN_HORZ_WIDTH;
        }
        else
        {
            szFloat.cy = m_sizeDefault.cy + rcBorders.top + rcBorders.bottom;
        }
    }
    else
    {
        szFloat.cy = nLength;
        if (nLength < MIN_HORZ_WIDTH)
        {
            szFloat.cx = m_sizeDefault.cx + rcBorders.left + rcBorders.right;
            szFloat.cy = m_sizeDefault.cy + rcBorders.top + rcBorders.bottom;
        }
        else
        {
            szFloat.cx = MIN_VERT_WIDTH;
        }
    }

    m_szFloat = szFloat;
    return szFloat;
}