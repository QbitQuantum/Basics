BOOL CLoungeDlg::PreTranslateMessage(MSG* pMsg) 
{
  BOOL rc = FALSE;

  // If focus is in some other than a button, eat ENTER and ESC
  // so the app won't exit accidentally
  if (pMsg->message == WM_KEYDOWN &&
      pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
  {
    // Eat ESC always
    if (pMsg->wParam == VK_ESCAPE)
      return TRUE;

    CWnd* pWnd = GetFocus();
    if (pWnd)
    {
      int ctrlID = pWnd->GetDlgCtrlID();
      if (!isButton(ctrlID))
        return TRUE; // Ignore
    }
  }

  rc = CDialog::PreTranslateMessage(pMsg);

  return rc;
}