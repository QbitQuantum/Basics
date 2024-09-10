//
// STATE: Log in.
//
StateLogin::StateLogin(const CString& username,
                       const CString& password)
  :
  pWaitDlg_(0),
  retry_   (2),
  ticks_   (0)

{
  CMainWnd* pWnd = CMainWnd::Instance();
  ASSERT(pWnd);
/*
  pWaitDlg_ = new CWaitDlg(pWnd);
  pWaitDlg_->Create(IDD_LOGGINGIN, pWnd);
  pWaitDlg_->ShowWindow(SW_SHOW);
*/
  // XXX Disable main window!
  pWnd->EnableWindow(FALSE);

  // DPP::SendLoginPDU(username_, password_);
}