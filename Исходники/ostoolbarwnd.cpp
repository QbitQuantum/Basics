int OSToolBarWnd::onLeftButtonUp(int x, int y) {
  OSTOOLBARWND_PARENT::onLeftButtonUp(x, y);
  if (m_hilite) {
    OSToolBarEntry *at = getEntryAt(x, y);
    if (m_hilite == at) {
      endCapture(); // in case event loads up a dialog ...
      if (!at->isDisabled()) {
        onClickIcon(at);
        at->onClicked();
        onLeaveIcon(at); // (for parity sake)
        beginCapture(); // ... we need to leave and restore icon states ...
        StdWnd::getMousePos(&x, &y);
        screenToClient(&x, &y);
        localMouseMove(x, y); // ... according to new mouse pos
      }
    }
  }

  m_down = 0;
  m_last_pushed = -1;

  return 1;
}