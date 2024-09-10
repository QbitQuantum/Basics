void CDlgVectorize::UpdateControls()
{
    CMenu* pSysMenu = GetSystemMenu(FALSE);

    if ( !pSysMenu )
    {
        return;
    }

    if ( m_pRedirect )
    {
        m_EditRun.EnableWindow(FALSE);
        //m_BtnBrowse.EnableWindow(FALSE);
        m_BtnRun.EnableWindow(FALSE);
        m_BtnStop.EnableWindow(TRUE);
        m_BtnShow.EnableWindow(FALSE);
        m_BtnExit.EnableWindow(FALSE);

        //----------------------------------------------------------------------
        //	Disable Close in System Menu (this also disables close box).
        //----------------------------------------------------------------------
        if (pSysMenu != NULL)
        {
            pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
        }
    }
    else 
    {
        m_EditRun.EnableWindow(TRUE);
        //m_BtnBrowse.EnableWindow(TRUE);
        m_BtnRun.EnableWindow(m_EditRun.GetWindowTextLength() > 0);
        m_BtnStop.EnableWindow(FALSE);
        m_BtnShow.EnableWindow(TRUE);
        m_BtnExit.EnableWindow(TRUE);

        //----------------------------------------------------------------------
        //	Enable Close in System Menu (this also enables close box).
        //----------------------------------------------------------------------
        if (pSysMenu != NULL)
        {
            pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
        }
    }
}