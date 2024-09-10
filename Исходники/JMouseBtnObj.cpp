void JMouseBtnObj::engine(int n, JLinkObj& link) {
  if (focusOn) return;
#if defined(WIN32)
  POINT pt;
  GetCursorPos(&pt);
  if (JComponent::getJComponent((int)WindowFromPoint(pt))) return;
  if (!n) {
    int click;
    link.access(JIntegerData(click));
    if (click && !state) {
      switch (type) {
        case LEFT:
          mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0L, 0L);
          mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0L, 0L);
	  break;
        case RIGHT:
          mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0L, 0L);
          mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0L, 0L);
	  break;
        case MIDDLE:
          mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0L, 0L);
          mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0L, 0L);
	  break;
      }
    }
  } else {
    int olds = state;
    link.access(JIntegerData(state));
    state = (state != 0) ? mask : 0;
    if (state != olds) {
      switch (type) {
        case LEFT:
          mouse_event(
	    (state) ? MOUSEEVENTF_LEFTDOWN : 
	    MOUSEEVENTF_LEFTUP, 
	    0, 0, 0L, 0L);
	  break;
        case RIGHT:
          mouse_event(
	    (state) ? MOUSEEVENTF_RIGHTDOWN : 
	    MOUSEEVENTF_RIGHTUP, 
	    0, 0, 0L, 0L);
	  break;
        case MIDDLE:
          mouse_event(
	    (state) ? MOUSEEVENTF_MIDDLEDOWN : 
	    MOUSEEVENTF_MIDDLEUP, 
	    0, 0, 0L, 0L);
	  break;
      }
    }
  }
#endif
}