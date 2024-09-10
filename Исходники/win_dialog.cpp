void Dialog::SnapToEdges(LPWINDOWPOS window_pos) {
  if (!snap_gap_)
    return;

  RECT rc_monitor = {0};
  SystemParametersInfo(SPI_GETWORKAREA, 0, &rc_monitor, 0);
  if (GetSystemMetrics(SM_CMONITORS) > 1) {
    HMONITOR monitor = MonitorFromWindow(window_, MONITOR_DEFAULTTONEAREST);
    if (monitor) {
      MONITORINFO mi;
      mi.cbSize = sizeof(mi);
      GetMonitorInfo(monitor, &mi);
      rc_monitor = mi.rcWork;
    }
  }

  // Snap X axis
  if (abs(window_pos->x - rc_monitor.left) <= snap_gap_) {
    window_pos->x = rc_monitor.left;
  } else if (abs(window_pos->x + window_pos->cx - rc_monitor.right) <= snap_gap_) {
    window_pos->x = rc_monitor.right - window_pos->cx;
  }
  // Snap Y axis
  if (abs(window_pos->y - rc_monitor.top) <= snap_gap_) {
    window_pos->y = rc_monitor.top;
  } else if (abs(window_pos->y + window_pos->cy - rc_monitor.bottom) <= snap_gap_) {
    window_pos->y = rc_monitor.bottom - window_pos->cy;
  }
}