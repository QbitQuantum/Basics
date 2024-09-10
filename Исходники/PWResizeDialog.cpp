void CPWResizeDialog::SetControls(int cx, int cy)
{
  if (!m_bInitDone || !m_bStatusBarOK)
    return;

  if (m_pMainCtrl == NULL || !IsWindow(m_pMainCtrl->GetSafeHwnd()))
    return;

  CRect sbRect, mainCtrlRect, btnRect, dlgRect;
  CPoint pt_top;

  GetWindowRect(&dlgRect);

  // Allow ListCtrl to grow/shrink but leave room for the buttons underneath!
  m_pMainCtrl->GetWindowRect(&mainCtrlRect);

  pt_top.x = mainCtrlRect.left;
  pt_top.y = mainCtrlRect.top;
  ScreenToClient(&pt_top);

  m_pMainCtrl->MoveWindow(pt_top.x, pt_top.y,
                          cx - (2 * pt_top.x), cy - m_cyBSpace, TRUE);

  // Keep buttons in the bottom area
  int xleft, ytop;

  m_pMainCtrl->GetWindowRect(&mainCtrlRect);
  ScreenToClient(&mainCtrlRect);

  ytop = mainCtrlRect.bottom + m_ybuttondiff;

  CWnd *pwnd;
  for (int i = 1; i <= m_numbtns; i++) {
    pwnd = GetDlgItem(m_viBottomButtons[i - 1]);
    pwnd->GetWindowRect(&btnRect);
    xleft = (i * cx / (m_numbtns + 1)) - (btnRect.Width() / 2);
    pwnd->SetWindowPos(NULL, xleft, ytop, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
  }

  // Now move the status bar
  m_statusBar.GetWindowRect(&sbRect);
  pt_top.x = sbRect.left;
  pt_top.y = sbRect.top;
  ScreenToClient(&pt_top);

  m_statusBar.MoveWindow(pt_top.x, cy - sbRect.Height(),
                         cx - (2 * pt_top.x),
                         sbRect.Height(), TRUE);

  GetDlgItem(m_viBottomButtons[m_iFocus])->SetFocus();
}