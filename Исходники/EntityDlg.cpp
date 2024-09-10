CPreviewDlg *CEntityDlg::ShowSkinChooser(entity_t *ent) {
    static CPreviewDlg modelDlg;
    modelDlg.SetMode(CPreviewDlg::SKINS);
    modelDlg.SetModal();
    if (modelDlg.GetSafeHwnd() == NULL) {
        modelDlg.Create(MAKEINTRESOURCE(IDD_DIALOG_PREVIEW));
    }
    modelDlg.RebuildTree( ( ent ) ? ent->epairs.GetString( "model" ) : "" );
    modelDlg.ShowWindow(SW_SHOW);
    modelDlg.BringWindowToTop();
    while (modelDlg.Waiting()) {
    }
    return &modelDlg;
}