string pDialogWindow::folderSelect(Window &parent, const string &path) {
  wchar_t wfilename[PATH_MAX + 1] = L"";
  BROWSEINFO bi;
  bi.hwndOwner = &parent != &Window::None ? parent.p.hwnd : 0;
  bi.pidlRoot = NULL;
  bi.pszDisplayName = wfilename;
  bi.lpszTitle = L"";
  bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS;
  bi.lpfn = NULL;
  bi.lParam = 0;
  bi.iImage = 0;
  bool result = false;
  LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
  if(pidl) {
    if(SHGetPathFromIDList(pidl, wfilename)) {
      result = true;
      IMalloc *imalloc = 0;
      if(SUCCEEDED(SHGetMalloc(&imalloc))) {
        imalloc->Free(pidl);
        imalloc->Release();
      }
    }
  }
  if(result == false) return "";
  string name = (const char*)utf8_t(wfilename);
  if(name == "") return "";
  name.transform("\\", "/");
  if(name.endswith("/") == false) name.append("/");
  return name;
}