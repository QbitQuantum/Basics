BOOL TreeDlg::PreTranslateMessage(MSG *pMsg) {
  if(TranslateAccelerator(m_hWnd, m_accelTable, pMsg)) {
    return true;
  }

  switch(pMsg->message) {
  case WM_RBUTTONDOWN:
    { CTreeCtrl *ctrl = getTreeCtrl();
      CPoint     p    = pMsg->pt;
      ctrl->ScreenToClient(&p);
      HTREEITEM item = findTreeItemByPoint(ctrl, p);
      if(item != NULL) {
        const String derivation = getDerivation(ctrl, item, 160);
        showInformation(derivation);
        return TRUE;
      }
    }
    break;
  }
  return __super::PreTranslateMessage(pMsg);
}