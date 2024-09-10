static BOOL onInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
  CPlugin * pPlugin = (CPlugin *)lParam;
  SetWindowLong(hWnd, DWL_USER, (long)pPlugin);

  // look at the last used API call if needed
  int iSel = 0;
  if (pPlugin && pPlugin->m_Pref_bRememberLastCall) {
    char szFileName[_MAX_PATH];
    GetINIFileName(pPlugin->getInstance(), szFileName, sizeof(szFileName));
    iSel = XP_GetPrivateProfileInt(SECTION_PREFERENCES, KEY_LAST_API_CALL, 0, szFileName);
  }
  fillAPIComboBoxAndSetSel(GetDlgItem(hWnd, IDC_COMBO_API_CALL), iSel);
  updateUI(hWnd);

  int iTopMargin = 188;
  SetWindowPos(hWnd, NULL, 0,iTopMargin, 0,0, SWP_NOZORDER | SWP_NOSIZE);
  return TRUE;
}