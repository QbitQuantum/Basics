BOOL RenameVolumeDialog::OnInitDialog(void)
{
    /* do the DoDataExchange stuff */
    CDialog::OnInitDialog();

    CTreeCtrl* pTree = (CTreeCtrl*) GetDlgItem(IDC_RENAMEVOL_TREE);
    DiskImgLib::DiskFS* pDiskFS = fpArchive->GetDiskFS();

    ASSERT(pTree != NULL);

    fDiskFSTree.fIncludeSubdirs = false;
    fDiskFSTree.fExpandDepth = -1;
    if (!fDiskFSTree.BuildTree(pDiskFS, pTree)) {
        LOGI("Tree load failed!");
        OnCancel();
    }

    int count = pTree->GetCount();
    LOGI("ChooseAddTargetDialog tree has %d items", count);

    /* select the default text and set the focus */
    CEdit* pEdit = (CEdit*) GetDlgItem(IDC_RENAMEVOL_NEW);
    ASSERT(pEdit != NULL);
    pEdit->SetSel(0, -1);
    pEdit->SetFocus();

    return FALSE;   // we set the focus
}