LRESULT CFileManagerDlg::OnNcHitTest(CPoint point)
{
  LRESULT hit = CDialogEx::OnNcHitTest(point);
  if (/*!m_bMaximized &&*/ hit == HTCLIENT) {
    CRect rtSysMenu;
    GetSysMenuRect(&rtSysMenu);
    if (rtSysMenu.PtInRect(point))
      hit = HTSYSMENU;
    else {
      CWnd *pChild = GetWindow(GW_CHILD);
      while (pChild) {
        CRect rtChild;
        pChild->GetWindowRect(&rtChild);
        if (rtChild.PtInRect(point))
          return hit;
        pChild = pChild->GetWindow(GW_HWNDNEXT);
      }
      hit = HTCAPTION;
      CRect rtClient;
      GetClientRect(&rtClient);
      ClientToScreen(&rtClient);
      CRect rtWindow;
      GetWindowRect(&rtWindow);
      if (point.x + point.y >= rtClient.right + rtClient.bottom - 10)
        hit = HTBOTTOMRIGHT;
//       else if (point.x >= rtClient.right - 5)
//         hit = HTRIGHT;

    }
  }
  return hit;
}