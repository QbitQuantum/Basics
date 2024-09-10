    void OnSetFocus(HWND /*hWndOther*/)
    {
        //SetMsgHandled(false);
        CWindow activeWnd = m_tabbedChildWindow.GetActiveView();
        if (activeWnd.IsWindow() && activeWnd.IsWindowVisible())
            activeWnd.SetFocus();

        int syncRepository = GetIConfig(QUERYBUILDER_CFG)->Get(GLOBAL_SYNCREPOSITORY);
        if (syncRepository)
            GetIMainFrame()->SyncTOC(m_dlgview.GetAttribute());
    }