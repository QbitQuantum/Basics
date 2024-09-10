static INT_PTR CALLBACK MessageBoxProc( HWND hwnd, UINT message,
                                        WPARAM wParam, LPARAM lParam )
{
  int i, Alert;
  PMSGBOXINFO mbi;
  HELPINFO hi;
  HWND owner;

  switch(message) {
    case WM_INITDIALOG:
      mbi = (PMSGBOXINFO)lParam;

      SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)mbi);
      NtUserxSetMessageBox(hwnd);

      if(!GetPropW(hwnd, L"ROS_MSGBOX"))
      {
        SetPropW(hwnd, L"ROS_MSGBOX", (HANDLE)lParam);

        if (mbi->dwContextHelpId)
          SetWindowContextHelpId(hwnd, mbi->dwContextHelpId);

        if (mbi->Icon)
        {
          SendDlgItemMessageW(hwnd, MSGBOX_IDICON, STM_SETICON, (WPARAM)mbi->Icon, 0);
          Alert = ALERT_SYSTEM_WARNING;
        }
        else // Setup the rest of the alerts.
        {
          switch(mbi->dwStyle & MB_ICONMASK)
          {
             case MB_ICONWARNING:
                Alert = ALERT_SYSTEM_WARNING;
             break;
             case MB_ICONERROR:
                Alert = ALERT_SYSTEM_ERROR;
             break;
             case MB_ICONQUESTION:
                Alert = ALERT_SYSTEM_QUERY;
             break;
             default:
                Alert = ALERT_SYSTEM_INFORMATIONAL;
             /* fall through */
          }
        }
        /* Send out the alert notifications. */
        NotifyWinEvent(EVENT_SYSTEM_ALERT, hwnd, OBJID_ALERT, Alert);

        /* set control fonts */
        SendDlgItemMessageW(hwnd, MSGBOX_IDTEXT, WM_SETFONT, (WPARAM)mbi->Font, 0);
        for(i = 0; i < mbi->nButtons; i++)
        {
          SendDlgItemMessageW(hwnd, mbi->Btns[i], WM_SETFONT, (WPARAM)mbi->Font, 0);
        }
        switch(mbi->dwStyle & MB_TYPEMASK)
        {
          case MB_ABORTRETRYIGNORE:
          case MB_YESNO:
            RemoveMenu(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_BYCOMMAND);
            break;
        }
        SetFocus(GetDlgItem(hwnd, mbi->DefBtn));
        if(mbi->Timeout && (mbi->Timeout != (UINT)-1))
          SetTimer(hwnd, 0, mbi->Timeout, NULL);
      }
      return 0;

    case WM_COMMAND:
      switch (LOWORD(wParam))
      {
        case IDOK:
        case IDCANCEL:
        case IDABORT:
        case IDRETRY:
        case IDIGNORE:
        case IDYES:
        case IDNO:
        case IDTRYAGAIN:
        case IDCONTINUE:
          EndDialog(hwnd, wParam);
          return 0;
        case IDHELP:
          /* send WM_HELP message to messagebox window */
          hi.cbSize = sizeof(HELPINFO);
          hi.iContextType = HELPINFO_WINDOW;
          hi.iCtrlId = LOWORD(wParam);
          hi.hItemHandle = (HANDLE)lParam;
          hi.dwContextId = 0;
          GetCursorPos(&hi.MousePos);
          SendMessageW(hwnd, WM_HELP, 0, (LPARAM)&hi);
          return 0;
      }
      return 0;

    case WM_COPY:
        MessageBoxTextToClipboard(hwnd);
        return 0;

    case WM_HELP:
      mbi = (PMSGBOXINFO)GetPropW(hwnd, L"ROS_MSGBOX");
      if(!mbi)
        return 0;
      memcpy(&hi, (void *)lParam, sizeof(hi));
      hi.dwContextId = GetWindowContextHelpId(hwnd);

      if (mbi->lpfnMsgBoxCallback)
        mbi->lpfnMsgBoxCallback(&hi);
      else
      {
        owner = GetWindow(hwnd, GW_OWNER);
        if(owner)
          SendMessageW(GetWindow(hwnd, GW_OWNER), WM_HELP, 0, (LPARAM)&hi);
      }
      return 0;

    case WM_CLOSE:
      mbi = (PMSGBOXINFO)GetPropW(hwnd, L"ROS_MSGBOX");
      if(!mbi)
        return 0;
      switch(mbi->dwStyle & MB_TYPEMASK)
      {
        case MB_ABORTRETRYIGNORE:
        case MB_YESNO:
          return 1;
      }
      EndDialog(hwnd, IDCANCEL);
      return 1;

    case WM_TIMER:
      if(wParam == 0)
      {
        EndDialog(hwnd, 32000);
      }
      return 0;
  }
  return 0;
}