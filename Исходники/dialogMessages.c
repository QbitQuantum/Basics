/*********************************************************
*NAME:          dialogMessagesChange
*AUTHOR:        John Morrison
*CREATION DATE: 7/4/99
*LAST MODIFIED: 3/1/00
*PURPOSE:
* Changes the "Sending to X players" message 
*
*ARGUMENTS:
*  hWnd - The dialog window handle
*********************************************************/
void dialogMessagesChange(HWND hWnd) {
  char output[256]; /* Output string                */
  int numSend;      /* Number of players to send to */

  /* Get the number of selected players */
  if (IsDlgButtonChecked(hWnd, IDC_ALL_PLAYERS) == BST_CHECKED) {
    numSend = screenGetNumPlayers();
  } else if (IsDlgButtonChecked(hWnd, IDC_ALL_ALLIES) == BST_CHECKED) {
    numSend = screenNumAllies();
  } else if (IsDlgButtonChecked(hWnd, IDC_ALL_NEARBY) == BST_CHECKED) {
    numSend = screenNumNearbyTanks();
  } else {
    numSend = screenNumCheckedPlayers();
  }

  /* Make the appropriate message */
  if (numSend == 1) {
    sprintf(output, langGetText(STR_DLGMSG_SENDPLAYER), 1);
  } else {
    sprintf(output, langGetText(STR_DLGMSG_SENDPLAYERS), numSend);
  }
  /* Print it */
  SendDlgItemMessageA(hWnd, IDC_NUM_PLAYERS, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) (output));
/*  SetFocus(GetDlgItem(hWnd, IDC_EDITSEND));  */
}