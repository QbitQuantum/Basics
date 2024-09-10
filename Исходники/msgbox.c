/*************************************************************************
 * @ [SHLWAPI.185]
 *
 * Pop up a 'Don't show this message again' dialogue box.
 *
 * PARAMS
 *  hWnd      [I] Window to be the dialogues' parent
 *  lpszText  [I] Text of the message to show
 *  lpszTitle [I] Title of the dialogue box
 *  dwType    [I] Type of dialogue buttons (See below)
 *  iRet      [I] Value to return if dialogue is not shown
 *  lpszId    [I] Name of registry subkey which determines whether to show the dialog
 *
 * RETURNS
 *  Success: The value returned from the dialogue procedure (e.g. IDOK).
 *  Failure: iRet, if the default dialogue resource could not be loaded or the
 *           dialogue should not be shown.
 *
 * NOTES
 *  - Both lpszTitle and lpszId must be less than MAX_PATH in length.
 *  - Possible values for dwType are:
 *| Value     Buttons
 *| -----     -------
 *|   0       OK
 *|   1       OK/Cancel
 *|   2       Yes/No
 */
INT_PTR WINAPI SHMessageBoxCheckA(HWND hWnd, LPCSTR lpszText, LPCSTR lpszTitle,
                                  DWORD dwType, INT_PTR iRet, LPCSTR lpszId)
{
  WCHAR szTitleBuff[MAX_PATH], szIdBuff[MAX_PATH];
  WCHAR *szTextBuff = NULL;
  int iLen;
  INT_PTR iRetVal;

  if (lpszTitle)
    MultiByteToWideChar(CP_ACP, 0, lpszTitle, -1, szTitleBuff, MAX_PATH);

  if (lpszText)
  {
    iLen = MultiByteToWideChar(CP_ACP, 0, lpszText, -1, NULL, 0);
    szTextBuff = HeapAlloc(GetProcessHeap(), 0, iLen * sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, lpszText, -1, szTextBuff, iLen);
  }

  MultiByteToWideChar(CP_ACP, 0, lpszId, -1, szIdBuff, MAX_PATH);

  iRetVal = SHMessageBoxCheckW(hWnd, szTextBuff, lpszTitle ? szTitleBuff : NULL,
                               dwType, iRet, szIdBuff);
  HeapFree(GetProcessHeap(), 0, szTextBuff);
  return iRetVal;
}