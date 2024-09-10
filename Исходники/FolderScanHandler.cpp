void CFolderScanHandler::InitDir( const SStringT & strDir )
{
    SWindow *pBtn = m_pPageRoot->FindChildByName(L"btn_go");
    SWindow *pEditDir = m_pPageRoot->FindChildByName(L"edit_dir");

    DWORD dwAttr = GetFileAttributes(strDir);
    if(dwAttr ==INVALID_FILE_ATTRIBUTES)
        return;
    if(!(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
        return;

    pEditDir->SetWindowText(strDir);

    pBtn->EnableWindow(FALSE,TRUE);
    pEditDir->EnableWindow(FALSE,TRUE);

    SWindow *pScanAni = m_pPageRoot->FindChildByName(L"ani_scan");
    pScanAni->SetVisible(TRUE,TRUE);
    SFolderTreeCtrl *pMcTreeCtrl = m_pTreelist->GetFolderTreeCtrl();
    pMcTreeCtrl->RemoveAllItems();
    HSTREEITEM hRoot = pMcTreeCtrl->InsertItem(_T("root"),TRUE,0,STVI_ROOT);
    if(EnumFiles(strDir,hRoot))
    {
        m_pTreelist->GetFolderTreeCtrl()->GetFileInfo(hRoot)->percent=100;
        m_pTreelist->GetFolderTreeCtrl()->UpdateTreeItemPercent(hRoot);
    }
    m_pTreelist->GetFolderTreeCtrl()->Invalidate();
    pBtn->EnableWindow(TRUE,TRUE);
    pEditDir->EnableWindow(TRUE,TRUE);
    pScanAni->SetVisible(FALSE,TRUE);
}