LONG WINAPI MainWndProc(HWND hWnd, UINT message, WPARAM wPrm, LONG lPrm)
{
  DLGPROC lpProcAbout;
  FILE *fp;

  switch(message) {
  case WM_COMMAND:
    switch (GET_WM_COMMAND_ID(wPrm, lPrm)) {
    case IDM_ABOUT:
      lpProcAbout = (DLGPROC) MakeProcInstance((FARPROC) About, hInst);
      DialogBox(hInst, "AboutBox", hWnd, lpProcAbout);
      (void) FreeProcInstance((FARPROC) lpProcAbout);
      break;
    case IDM_NEW:
      if (! QuerySaveFile()) return(FALSE);
      bChanges = FALSE;
      FileName[0] = 0;
      SetNewBuffer(NULL, Untitled);
      break;
    case IDM_OPEN:
      if (! QuerySaveFile())
        return FALSE;
      if (! OpenDlg() || (fp = fopen(FileName, "r")) == NULL)
        return FALSE;
      ReanInFile(fp);
      return FALSE;
    case IDM_SAVE:
      if (! FileName[0]) goto saveas;
      if (bChanges) SaveFile();
      break;
    case IDM_SAVEAS:
saveas:
      if (SaveAsDlg()) {
	sprintf(buf, "LSPEdit - %s", FileName);
	if (SaveFile())
          SetWindowText(hWnd, buf);
        else {
          FileName[0] = 0;
          SetWindowText(hWnd, Untitled);
        }
      }
      break;
    case IDM_PRINT:
      WarningBox("Command Not Implemented");
      break;
    case IDM_EXIT:
      if (! QuerySaveFile()) return FALSE;
      DestroyWindow(hWnd);
      break;
    case IDM_UNDO:
      WarningBox("Command Not Implemented");
      break;
    case IDM_CUT:
      TTYSelToClip();
      TTYClearSel();
      break;
    case IDM_COPY:
      TTYSelToClip();
      break;
    case IDM_PASTE:
      TTYPasteFromClip();
      break;
    case IDM_CLEAR:
      TTYClearSel();
      break;
    case IDM_EVAL:
      {
        HSZ service, topic;
        HCONV hconv;

        service = DdeCreateStringHandle(ddeInst, "XLISP-STAT", CP_WINANSI);
        topic = DdeCreateStringHandle(ddeInst, "XLISP-STAT", CP_WINANSI);
        if ((hconv = DdeConnect(ddeInst, service, topic, NULL)) == NULL)
          WarningBox("Can't connect to XLISP-STAT");
        else {
          /**** switch to allocated buffer? */
          char *data = TTYSelectionStr();
          if (! DdeClientTransaction((LPVOID) data, strlen(data) + 1,
                                     hconv, NULL, CF_TEXT, XTYP_EXECUTE,
                                     60000L, NULL))
            WarningBox("Transaction failed");
          DdeDisconnect(hconv);
        }
        DdeFreeStringHandle(ddeInst, service);
        DdeFreeStringHandle(ddeInst, topic);
      }
      break;
    case IDC_EDIT:
      if (GET_WM_COMMAND_CMD(wPrm, lPrm) == EN_ERRSPACE) {
	WarningBox("Out of memory");
      }
      if (GET_WM_COMMAND_CMD(wPrm, lPrm) == EN_CHANGE) bChanges = TRUE;
      break;
    default: return(DefWindowProc(hWnd, message, wPrm, lPrm));
    }
    break;
  case WM_SETFOCUS:
    SetFocus(hEditWnd);
    break;
  case WM_SIZE:
    MoveWindow(hEditWnd, 0, 0, LOWORD(lPrm), HIWORD(lPrm), TRUE);
    break;
  case WM_QUERYENDSESSION:
    return(QuerySaveFile());
  case WM_CLOSE:
    if (QuerySaveFile()) DestroyWindow(hWnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return(DefWindowProc(hWnd, message, wPrm, lPrm));
  }
  return FALSE;
}