void OSMDIChildWnd::setWindowFlags() {
  #ifdef WIN32
  SetWindowLong(gethWnd(), GWL_STYLE, WS_CHILDWINDOW | WS_OVERLAPPED | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | (isVisible(1) ? WS_VISIBLE : 0));
  SetWindowLong(gethWnd(), GWL_EXSTYLE, WS_EX_MDICHILD | WS_EX_WINDOWEDGE);
  SetWindowRgn(gethWnd(), NULL, TRUE);
  #endif
}