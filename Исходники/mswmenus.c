int StMObPopup(LVAL menu, int left, int top, LVAL window)
{
  HMENU theMenu;
  HWND w;
  POINT pt;

  if (window == NIL || (w = GETWINDOWADDRESS(window)) == 0)
    w = hWndFrame;

  pt.x = left; pt.y = top;
  ClientToScreen((HWND) w, &pt);
  left = pt.x; top = pt.y;

  InPopup = TRUE;
  PopupItem = 0;
  StMObAllocate(menu);
  theMenu = get_menu_address(menu);
  if (TrackPopupMenu((HMENU) theMenu, 0, left, top, 0, (HWND) w, NULL)) {
    MSG msg;
    extern HWND hWndClient;
    extern HACCEL hAccel;
    if (PeekMessage(&msg, w, WM_COMMAND, WM_COMMAND, PM_REMOVE) &&
        ! TranslateMDISysAccel(hWndClient, &msg) &&
        ! TranslateAccelerator(hWndFrame, hAccel, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  StMObDispose(menu);
  InPopup = FALSE;

  return(PopupItem);
}