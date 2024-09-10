CString Directories::browseForDir(CString title)
{
  static char buffer[1024];
  LPMALLOC pMalloc;
  LPITEMIDLIST pidl;
  
  CString res;
  
  if(SUCCEEDED(SHGetMalloc(&pMalloc))) {
    BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = m_hWnd;
    bi.lpszTitle = title;
    bi.pidlRoot = 0;
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
    bi.lpfn = browseCallbackProc;
    bi.lParam = (LPARAM)(LPCTSTR)initialFolderDir;
    
    pidl = SHBrowseForFolder(&bi);
    
    if(pidl) {
      if(SHGetPathFromIDList(pidl, buffer)) {
        res = buffer;
      }
      pMalloc->Free(pidl);
      pMalloc->Release();
    }
  }
  return res;
}