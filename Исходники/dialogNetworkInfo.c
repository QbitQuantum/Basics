/*********************************************************
*NAME:          dialogNetInfoSetup
*AUTHOR:        John Morrison
*CREATION DATE:  3/3/99
*LAST MODIFIED: 29/4/00
*PURPOSE:
* Sets up the dialog box
*
*ARGUMENTS:
*  hWnd - The dialog window handle
*********************************************************/
void dialogNetInfoSetup(HWND hWnd) {
  char str[FILENAME_MAX]; /* Our address as a string */
  char addr[FILENAME_MAX];

  /* Setup languages */
  SetWindowTextA(hWnd, langGetText(STR_DLGNETINFO_TITLE));
  SetDlgItemTextA(hWnd, IDC_SERVERS, langGetText(STR_DLGNETINFO_SERVERADDRESS));
  SetDlgItemTextA(hWnd, IDC_THISADDRESSS, langGetText(STR_DLGNETINFO_THISGAMEADDRESS));
  SetDlgItemTextA(hWnd, IDC_SERVERPINGS, langGetText(STR_DLGNETINFO_SERVERPING));
  SetDlgItemTextA(hWnd, IDC_PPSPLS, langGetText(STR_DLGNETINFO_PACKETS));
  SetDlgItemTextA(hWnd, IDC_NETSTATUSS, langGetText(STR_DLGNETINFO_STATUS));
  SetDlgItemTextA(hWnd, IDC_NETERRORSS, langGetText(STR_DLGNETINFO_ERRORS));

  /* We are in a client and playing a networked game.. */
  if (threadsGetContext() == FALSE && netGetType() != netSingle)
  {
	  playersGetPlayerLocation(screenGetPlayers(),playersGetSelf(screenGetPlayers()),addr);
	  netGetOurAddressStr(str);
	  strcat(addr,strchr(str,':'));
	  SendDlgItemMessageA(hWnd, IDC_THISADDRESS, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) (addr));
  }
  else /* Single player game, no networking */
  {
      netGetOurAddressStr(str);
	  SendDlgItemMessageA(hWnd, IDC_THISADDRESS, WM_SETTEXT, 0, (LPARAM)(LPCTSTR) (str));
  }
  timerNetInfo = SetTimer(hWnd, timerNetInfo, SECOND, NULL);
  dialogNetInfoUpdate(hWnd);
}