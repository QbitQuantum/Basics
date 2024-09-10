VOID RestoreWndFromTray(HWND hWnd)
{
  // Show the window, and make sure we're the foreground window
  ShowWindow(hWnd, SW_SHOW);
  if(IsIconic(hWnd))
	  ShowWindow(hWnd, SW_SHOWNORMAL);
	  
  SetActiveWindow(hWnd);
  SetForegroundWindow(hWnd);
  ShowOwnedPopups(hWnd, TRUE);

  // Remove the tray icon. As described above, remove the icon after the
  // call to DrawAnimatedRects, or the taskbar will not refresh itself
  // properly until DAR finished
}