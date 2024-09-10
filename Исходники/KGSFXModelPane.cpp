DWORD KGSFXModelPane::UpdateWndState()
{
    KSceneSFXEditorView* pEditView = dynamic_cast<KSceneSFXEditorView*>(m_pDependWnd);
    KG_PROCESS_ERROR(pEditView);

    if (m_dwWndState == SFX_WND_STATE_FREE)
    {
        ModifyStyle(NULL, WS_CAPTION | WS_BORDER | WS_SIZEBOX, SWP_DRAWFRAME);
        RECT rectWnd;
        GetWindowRect(&rectWnd);
        SetParent(NULL);
        MoveWindow(&rectWnd);
    }
    else
    {
        ModifyStyle(WS_CAPTION | WS_BORDER | WS_SIZEBOX, NULL, SWP_DRAWFRAME);
        SetParent(m_pDependWnd);
        MoveWindow(&(pEditView->GetPaneRect(WND_LEFT_PANE)));
    }
    pEditView->m_paneSFXKeyFrame.UpdateWndState();
    pEditView->m_paneSFXMainWnd.UpdateWndState();
Exit0:
    return m_dwWndState;
}