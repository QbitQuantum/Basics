BOOL CUserDesktopDlg::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(rect);

    if(m_desktopwnd && m_desktopwnd->nSessionID)
    {
        SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
        TT_PaintDesktopWindow(ttInst, m_nUserID, pDC->m_hDC, rect.left, 
                              rect.top, rect.Width(), rect.Height());
        //const int W = 100, H = 100;
        //BOOL b;
        //b = TT_PaintDesktopWindowEx(ttInst, m_nUserID, pDC->m_hDC, rect.left, 
        //                            rect.top, rect.Width(), rect.Height(),
        //                            m_desktopwnd.nWidth-W, m_desktopwnd.nHeight-H, W, H);
        //ASSERT(b);
        return FALSE;
    }
    else
        return CDialog::OnEraseBkgnd(pDC);
}