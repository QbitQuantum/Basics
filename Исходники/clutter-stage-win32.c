static void
get_fullscreen_rect (ClutterStageWin32 *stage_win32)
{
  HMONITOR monitor;
  MONITORINFO monitor_info;

  /* If we already have a window then try to use the same monitor that
     is already on */
  if (stage_win32->hwnd)
    monitor = MonitorFromWindow (stage_win32->hwnd, MONITOR_DEFAULTTONEAREST);
  else
    {
      /* Otherwise just guess that they will want the monitor where
	 the cursor is */
      POINT cursor;
      GetCursorPos (&cursor);
      monitor = MonitorFromPoint (cursor, MONITOR_DEFAULTTONEAREST);
    }

  monitor_info.cbSize = sizeof (monitor_info);
  GetMonitorInfoW (monitor, &monitor_info);
  stage_win32->fullscreen_rect = monitor_info.rcMonitor;
}