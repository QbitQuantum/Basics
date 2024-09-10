void CGameParamsSheet::InitButtons()
{
  // Calculate the height of 7 dialog units
  CRect rectUnits(0, 0, 0, 7);

  //mmf vc8 does not like two arguments, below was commented out, I uncommented it - Imago made them co-exist
#if _MSC_VER >= 1400
  MapDialogRect(rectUnits);
#else
  MapDialogRect(GetSafeHwnd(), rectUnits); 
#endif


  // Get the OK and cancel buttons
  CWnd* pwndOK     = GetDlgItem(IDOK);
  CWnd* pwndCancel = GetDlgItem(IDCANCEL);
  CWnd* pwndHelp   = GetDlgItem(IDHELP);

  // Get the window rectangles of the buttons
  CRect rectOK, rectCancel, rectHelp;
  pwndOK->GetWindowRect(rectOK);
  pwndCancel->GetWindowRect(rectCancel);
  pwndHelp->GetWindowRect(rectHelp);
  ScreenToClient(rectOK);
  ScreenToClient(rectCancel);
  ScreenToClient(rectHelp);

  // Compute the offset to position these buttons flush-right
  int cxOffset = rectHelp.right - rectCancel.right;

  // Move the buttons into place
  rectOK.OffsetRect(cxOffset, 0);
  rectCancel.OffsetRect(cxOffset, 0);
  pwndOK->MoveWindow(rectOK);
  pwndCancel->MoveWindow(rectCancel);

  // Hide the Apply and Help buttons
  GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);
  GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);

  // Show the OK and Cancel buttons
  GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
  GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);

  // Enable the OK and Cancel buttons
  GetDlgItem(IDOK)->EnableWindow(true);
  GetDlgItem(IDCANCEL)->EnableWindow(true);
}