//------------------------------------------------------------------------------
void __fastcall TPrefsForm::BrowseButtonClick(TObject* Sender) {
  BROWSEINFO    info;
  char          szDir[MAX_PATH];
  char          szDisplayName[MAX_PATH];
  LPITEMIDLIST  pidl;
  LPMALLOC      pShellMalloc;

  if(SHGetMalloc(&pShellMalloc) == NO_ERROR) {
    memset(&info, 0x00, sizeof(info));
    info.hwndOwner = Handle;
    info.pidlRoot  = 0;
    info.pszDisplayName = szDisplayName;
    info.lpszTitle = LMessagesOpt.SelectFolder;
    info.ulFlags = BIF_NEWDIALOGSTYLE; //BIF_RETURNONLYFSDIRS;
    info.lpfn = 0;
    pidl = SHBrowseForFolder(&info);

    if(pidl) {
      if(SHGetPathFromIDList(pidl, szDir))
        BackupPath->Text = szDir;

      pShellMalloc->Free(pidl);
    }

    pShellMalloc->Release();
  }
}