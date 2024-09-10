void n2e_ScintillaDPIInit(const HWND hwnd)
{
  if (!IsWindowsVistaOrGreater())
  {
    return;
  }
  RECT rc = { 0 };
  GetWindowRect(hwnd, &rc);
  const POINT pt = { rc.left, rc.top };
  SciCall_SetDPI(GetDPIFromMonitor(MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY), hwnd));
}