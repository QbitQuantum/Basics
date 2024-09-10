BOOL CModelessDialog::DestroyWindow()
{
    CWnd* pMainWnd = AfxGetApp()->m_pMainWnd;
    if (pMainWnd) {
        pMainWnd->SetActiveWindow();
    }
    return __super::DestroyWindow();
}