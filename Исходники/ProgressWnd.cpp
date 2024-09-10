void CProgressWnd::OnCancel() 
{
    if (m_bEnableCancel)
    {
        if (m_bPersistantPosition)
            SaveCurrentSettings();

        m_bCancelled = TRUE;
        Hide();

        if (m_bModal)
            PostMessage(WM_CLOSE);

        CWnd *pWnd = AfxGetMainWnd();
        if (pWnd && ::IsWindow(pWnd->m_hWnd))
            pWnd->SetForegroundWindow();
    }
}