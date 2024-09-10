static void
winInitDialog (HWND hwndDlg)
{
  HWND hwndDesk; 
  RECT rc, rcDlg, rcDesk;
  HICON hIcon, hIconSmall;
 
  hwndDesk = GetParent (hwndDlg);
  if (!hwndDesk || IsIconic (hwndDesk))
    hwndDesk = GetDesktopWindow (); 
  
  /* Remove minimize and maximize buttons */
  SetWindowLongPtr(hwndDlg, GWL_STYLE,
                   GetWindowLongPtr(hwndDlg, GWL_STYLE)
                   & ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX));

  /* Set Window not to show in the task bar */
  SetWindowLongPtr(hwndDlg, GWL_EXSTYLE,
                   GetWindowLongPtr(hwndDlg, GWL_EXSTYLE) & ~WS_EX_APPWINDOW );

  /* Center dialog window in the screen. Not done for multi-monitor systems, where
   * it is likely to end up split across the screens. In that case, it appears
   * near the Tray icon.
   */
  if (GetSystemMetrics(SM_CMONITORS)>1) {
    /* Still need to refresh the frame change. */
    SetWindowPos (hwndDlg, HWND_TOPMOST, 0,0,0,0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
  } else {
    GetWindowRect (hwndDesk, &rcDesk);
    GetWindowRect (hwndDlg, &rcDlg);
    CopyRect (&rc, &rcDesk);

    OffsetRect (&rcDlg, -rcDlg.left, -rcDlg.top);
    OffsetRect (&rc, -rc.left, -rc.top);
    OffsetRect (&rc, -rcDlg.right, -rcDlg.bottom);

    SetWindowPos (hwndDlg,
		HWND_TOPMOST,
		rcDesk.left + (rc.right / 2),
		rcDesk.top + (rc.bottom / 2),
		0, 0,
		SWP_NOSIZE | SWP_FRAMECHANGED);
  }

#ifdef XWIN_MULTIWINDOW
  if (g_hIconX) hIcon=g_hIconX;
  else
#endif
  hIcon = LoadIcon (g_hInstance, MAKEINTRESOURCE(IDI_XWIN));

#ifdef XWIN_MULTIWINDOW
  if (g_hSmallIconX) hIconSmall=g_hSmallIconX;
  else
#endif
  hIconSmall = LoadImage (g_hInstance,
                        MAKEINTRESOURCE(IDI_XWIN), IMAGE_ICON,
                        GetSystemMetrics(SM_CXSMICON),
                        GetSystemMetrics(SM_CYSMICON),
                        LR_SHARED);

  PostMessage (hwndDlg, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
  PostMessage (hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIconSmall);
}