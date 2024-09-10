BOOL CQuestionnaireSettings::OnInitDialog() {
    BOOL bResult = CPropertySheet::OnInitDialog();

    DWORD dwIds[] = {IDOK,
        IDCANCEL,
        -1};

    MfcUtils::Localize(this, dwIds);

    CWnd *pApply = GetDlgItem(ID_APPLY_NOW);
    if (pApply != NULL)
        pApply->DestroyWindow();

    CWnd *pHelp = GetDlgItem(IDHELP);
    if (pHelp != NULL)
        pHelp->DestroyWindow();

    CRect rectBtn;
    int nSpacing = 6;        // space between two buttons...

    int ids [] = {IDOK, IDCANCEL};
    for (int i = 0; i < sizeof(ids)/sizeof(int); i++) {
        GetDlgItem (ids [i])->GetWindowRect (rectBtn);

        ScreenToClient (&rectBtn);
        int btnWidth = rectBtn.Width();
        rectBtn.left = rectBtn.left + (btnWidth + nSpacing)* 2;
        rectBtn.right = rectBtn.right + (btnWidth + nSpacing)* 2;

        GetDlgItem (ids [i])->MoveWindow(rectBtn);
    }

    CPropertyPage *pActivePage = GetActivePage();
    SetActivePage(m_pQuestionnaireQuestionPage);
    SetActivePage(m_pQuestionnaireOptionPage);
    SetActivePage(m_pQuestionnaireButtonPage);

    SetActivePage(pActivePage);

    return bResult;
}