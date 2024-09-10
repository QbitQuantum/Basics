INT_PTR
PluginHangUIChild::HangUIDlgProc(HWND aDlgHandle, UINT aMsgCode, WPARAM aWParam,
                                 LPARAM aLParam)
{
  mDlgHandle = aDlgHandle;
  switch (aMsgCode) {
    case WM_INITDIALOG: {
      // Register a wait on the Firefox process so that we will be informed
      // if it dies while the dialog is showing
      RegisterWaitForSingleObject(&mRegWaitProcess,
                                  mParentProcess,
                                  &SOnParentProcessExit,
                                  this,
                                  INFINITE,
                                  WT_EXECUTEDEFAULT | WT_EXECUTEONLYONCE);
      SetWindowText(aDlgHandle, mWindowTitle);
      SetDlgItemText(aDlgHandle, IDC_MSG, mMessageText);
      SetDlgItemText(aDlgHandle, IDC_NOFUTURE, mNoFutureText);
      SetDlgItemText(aDlgHandle, IDC_CONTINUE, mWaitBtnText);
      SetDlgItemText(aDlgHandle, IDC_STOP, mKillBtnText);
      ResizeButtons();
      HANDLE icon = LoadImage(NULL, IDI_QUESTION, IMAGE_ICON, 0, 0,
                              LR_DEFAULTSIZE | LR_SHARED);
      if (icon) {
        SendDlgItemMessage(aDlgHandle, IDC_DLGICON, STM_SETICON, (WPARAM)icon, 0);
      }
      EnableWindow(mParentWindow, FALSE);
      return TRUE;
    }
    case WM_CLOSE: {
      mResponseBits |= HANGUI_USER_RESPONSE_CANCEL;
      EndDialog(aDlgHandle, 0);
      SetWindowLongPtr(aDlgHandle, DWLP_MSGRESULT, 0);
      return TRUE;
    }
    case WM_COMMAND: {
      switch (LOWORD(aWParam)) {
        case IDC_CONTINUE:
          if (HIWORD(aWParam) == BN_CLICKED) {
            mResponseBits |= HANGUI_USER_RESPONSE_CONTINUE;
            EndDialog(aDlgHandle, 1);
            SetWindowLongPtr(aDlgHandle, DWLP_MSGRESULT, 0);
            return TRUE;
          }
          break;
        case IDC_STOP:
          if (HIWORD(aWParam) == BN_CLICKED) {
            mResponseBits |= HANGUI_USER_RESPONSE_STOP;
            EndDialog(aDlgHandle, 1);
            SetWindowLongPtr(aDlgHandle, DWLP_MSGRESULT, 0);
            return TRUE;
          }
          break;
        case IDC_NOFUTURE:
          if (HIWORD(aWParam) == BN_CLICKED) {
            if (Button_GetCheck(GetDlgItem(aDlgHandle,
                                           IDC_NOFUTURE)) == BST_CHECKED) {
              mResponseBits |= HANGUI_USER_RESPONSE_DONT_SHOW_AGAIN;
            } else {
              mResponseBits &=
                ~static_cast<DWORD>(HANGUI_USER_RESPONSE_DONT_SHOW_AGAIN);
            }
            SetWindowLongPtr(aDlgHandle, DWLP_MSGRESULT, 0);
            return TRUE;
          }
          break;
        default:
          break;
      }
      break;
    }
    case WM_DESTROY: {
      EnableWindow(mParentWindow, TRUE);
      break;
    }
    default:
      break;
  }
  return FALSE;
}