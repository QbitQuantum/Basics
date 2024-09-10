bool WinClipboard::getString(StringStorage *str)
{
  UINT strType = CF_UNICODETEXT;

  if (sizeof(TCHAR) == 1) {
    strType = CF_TEXT;
  }
  int uFormat = GetPriorityClipboardFormat(&strType, sizeof(UINT));

  if (uFormat == 0 || uFormat == -1) {
     return false;
  }
  if (OpenClipboard(m_hWnd)) {
     HANDLE hndData = GetClipboardData(uFormat); 

     if (hndData) {
        TCHAR *szData = (TCHAR *)GlobalLock(hndData); 
        StringStorage nativeClipboard = szData;
        //str->setString(szData);
        GlobalUnlock(hndData); 
        CloseClipboard();
        *str = removeCR(&nativeClipboard);
        return true;
      }
    CloseClipboard();
    return false;
  }
  return false;
}