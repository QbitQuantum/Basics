int OSDockWnd::onLeftButtonDown(int x, int y) {
  OSDOCKWND_PARENT::onLeftButtonDown(x, y);
  POINT pt={x,y};
  if (PtInRect(&m_snapbtn, pt)) {
    m_snap_bdown = 1;
    m_snap_inarea = 1;
    beginCapture();
    invalidateRect(&m_snapbtn);
    UpdateWindow(gethWnd());
  }
  return 1;
}