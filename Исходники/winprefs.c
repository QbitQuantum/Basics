/*
 * Callback routine that is executed once per window class.
 * Removes or creates custom window settings depending on LPARAM
 */
static wBOOL CALLBACK
ReloadEnumWindowsProc (HWND hwnd, LPARAM lParam)
{
  HICON   hicon;
  Window  wid;

  if (!hwnd) {
    ErrorF("ReloadEnumWindowsProc: hwnd==NULL!\n");
    return FALSE;
  }

  /* It's our baby, either clean or dirty it */
  if (lParam==FALSE) 
    {
      /* Reset the window's icon to undefined. */
      hicon = (HICON)SendMessage(hwnd, WM_SETICON, ICON_BIG, 0);

      /* If the old icon is generated on-the-fly, get rid of it, will regen */
      winDestroyIcon (hicon);

      /* Same for the small icon */
      hicon = (HICON)SendMessage(hwnd, WM_SETICON, ICON_SMALL, 0);
      winDestroyIcon (hicon);

      /* Remove any menu additions; bRevert=TRUE destroys any modified menus */
      GetSystemMenu (hwnd, TRUE);
      
      /* This window is now clean of our taint (but with undefined icons) */
    }
  else
    {
      /* winUpdateIcon() will set the icon default, dynamic, or from xwinrc */
      wid = (Window)GetProp (hwnd, WIN_WID_PROP);
      if (wid)
	winUpdateIcon (wid);

      /* Update the system menu for this window */
      SetupSysMenu ((unsigned long)hwnd);

      /* That was easy... */
    }

  return TRUE;
}