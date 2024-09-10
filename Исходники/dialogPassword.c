/*********************************************************
*NAME:          dialogPasswordCallback
*AUTHOR:        John Morrison
*CREATION DATE: 24/1/99
*LAST MODIFIED: 29/4/00
*PURPOSE:
*  The Opening Dialog call back function.
*
*ARGUMENTS:
*  hWnd   - Handle to the window
*  msg    - The message
*  wParam - Message parameters
*  lParam - More Message parameters
*********************************************************/
BOOL CALLBACK dialogPasswordCallback( HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam ) {
  char pass[MAP_STR_SIZE]; /* The password to get */

  switch ( uMsg ) {
  case WM_INITDIALOG:
    /* Set languages */
    SetWindowTextA(hWnd, langGetText(STR_DLGPASSWORD_TITLE));
    SetDlgItemTextA(hWnd, IDC_BLURB, langGetText(STR_DLGPASSWORD_BLURB));
    SetDlgItemTextA(hWnd, IDOK, langGetText(STR_OK));
    SetFocus(GetDlgItem(hWnd, IDC_PASSWORD));
    break;
  case WM_COMMAND:
    switch (LOWORD(wParam)) {
    case IDOK:
      GetDlgItemText(hWnd, IDC_PASSWORD, pass, (sizeof(pass)));
      gameFrontSetGameOptions(pass, gameOpen, FALSE, FALSE, 0, 0, TRUE);
      EndDialog(hWnd, TRUE);
      break;
    }
    break;
  case WM_PAINT:
    break;
  case WM_DESTROY:
    break;
  }
  return FALSE;
}