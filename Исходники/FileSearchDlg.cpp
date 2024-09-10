void CFileSearchDlg::OnBnClickedExampleQueriesButton() {
    RECT rc;
    m_ExampleQueriesButton.GetWindowRect(&rc);
    POINT menuOrigin = { rc.left, rc.bottom };

    CMenu popupMenu;
    popupMenu.CreatePopupMenu();
    int i = IDM_POPUPMENU_ITEM_FIRST;

    for (int j = 0; j < ARRAYSIZE(SampleQueries); j++) {
        popupMenu.AppendMenu(MF_STRING, i++, SampleQueries[j]);
    }

    TPMPARAMS excludeArea;
    ZeroMemory(&excludeArea, sizeof(excludeArea));
    excludeArea.cbSize = sizeof(excludeArea);
    excludeArea.rcExclude = rc;
    popupMenu.TrackPopupMenuEx(TPM_LEFTALIGN | TPM_LEFTBUTTON, menuOrigin.x, menuOrigin.y, this, &excludeArea);
}