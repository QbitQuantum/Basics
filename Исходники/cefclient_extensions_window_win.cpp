void ResizeTo(HWND hwnd, int width, int height) {
	 HWND root_wnd = ::GetAncestor(hwnd, GA_ROOT);

  // Retrieve current window placement information.
  WINDOWPLACEMENT placement;
  ::GetWindowPlacement(root_wnd, &placement);

  if(placement.showCmd == SW_MAXIMIZE)
	  return;

  HMONITOR monitor = MonitorFromRect(&placement.rcNormalPosition,
                                     MONITOR_DEFAULTTONEAREST);
  MONITORINFO info;
  info.cbSize = sizeof(info);
  GetMonitorInfo(monitor, &info);

  if (width < 100)
    width = 100;
  else if (width > info.rcWork.right - info.rcWork.left)
	  width = info.rcWork.right - info.rcWork.left;
  if (height < 100)
	  height = 100;
  else if (height > info.rcWork.bottom - info.rcWork.top)
    height = info.rcWork.bottom - info.rcWork.top;

  ::SetWindowPos(root_wnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
  if (placement.showCmd == SW_MINIMIZE)
    ::ShowWindow(root_wnd, SW_RESTORE);
}