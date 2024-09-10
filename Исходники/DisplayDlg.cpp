void CDisplayDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    int h = 10;
    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_ALL;
    GetScrollInfo(SB_VERT, &si);
    int nOldPos = si.nPos;

    switch (nSBCode)
    {
    case SB_LINEDOWN:
        si.nPos = min(si.nPos + h, si.nMax);
        break;
    case SB_PAGEDOWN:
        si.nPos = min(si.nPos + h * 10, si.nMax);
        break;
    case SB_LINEUP:
        si.nPos = max(si.nPos - h, si.nMin);
        break;
    case SB_PAGEUP:
        si.nPos = max(si.nPos - h * 10, si.nMin);
        break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        si.nPos = si.nTrackPos;
        break;
    case SB_TOP:
        si.nPos = si.nMin;
        break;
    case SB_BOTTOM:
        si.nPos = si.nMax;
        break;
    }

    SetScrollInfo(SB_VERT, &si);
    GetScrollInfo(SB_VERT, &si); //重新获取新的位置


    ScrollWindowEx(0, nOldPos - si.nPos,NULL, NULL, NULL, NULL, SW_ERASE|SW_SCROLLCHILDREN);
    UpdateWindow();
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
    //m_ScreenDisplayer->ReflashDC();
    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}