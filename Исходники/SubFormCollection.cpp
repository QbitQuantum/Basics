bool CSubFormCollection::ShowSubForm(int ix)
{
    ASSERT(ix <= m_Forms.GetUpperBound());
    if (ix > m_Forms.GetUpperBound()) return(false); // does not exist

    CDialog* pDlg;
    if (ix != -1) {
        if (m_nActiveForm != -1) {
            pDlg = m_Forms.GetAt(m_nActiveForm);
            ASSERT(pDlg != NULL);
            ASSERT(pDlg->m_hWnd != NULL);
            if ((pDlg == NULL) 
            ||  (pDlg->m_hWnd == NULL)) return(false);
            pDlg->ShowWindow(SW_HIDE);
        }
        m_nActiveForm = ix; // this is the active one now;
    }
    else {
        if (m_nActiveForm == -1) {
            m_nActiveForm = 0;
        }
    }
    pDlg = m_Forms.GetAt(m_nActiveForm);
    ASSERT(pDlg != NULL);
    ASSERT(pDlg->m_hWnd != NULL);
    if ((pDlg == NULL) 
    ||  (pDlg->m_hWnd == NULL)) return(false);
    pDlg->ShowWindow(SW_SHOW);
    pDlg->Invalidate();
    pDlg->RedrawWindow();
    return(true);
}