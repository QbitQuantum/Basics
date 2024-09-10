static String _GetProfilePath()
{
  String sPath;

  ITEMIDLIST* pidl;
  HRESULT hr = SHGetFolderLocation(NULL, CSIDL_APPDATA, NULL, 0, &pidl);
  if (hr == S_OK) {
    TCHAR szPath[MAX_PATH];
    if (SHGetPathFromIDList(pidl, szPath)) {
      sPath = szPath;
      sPath.makeTrailingSlash();
    }
    CoTaskMemFree(pidl);
  }

  return sPath;
}