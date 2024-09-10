void OpenGLDisplayDevice::do_reposition_window(int xpos, int ypos) {
  RECT rcClient, rcWindow;
  GetClientRect(glwsrv.hWnd, &rcClient);
  GetWindowRect(glwsrv.hWnd, &rcWindow);
  MoveWindow(glwsrv.hWnd, xpos, ypos, rcWindow.right-rcWindow.left, rcWindow.bottom-rcWindow.top, TRUE);
}