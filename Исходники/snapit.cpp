LRESULT CALLBACK fproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
  if(msg == WMU_TRAYICON)
  {
    switch(lp)
    {
    case WM_LBUTTONUP:
      ShowWindow(hwnd, SW_SHOW);
      SetForegroundWindow(hwnd);
      break;
    case WM_RBUTTONUP:
      POINT point;
      GetCursorPos(&point);

      switch(TrackPopupMenu(g_menu, TPM_RETURNCMD | TPM_NONOTIFY, point.x, point.y, 0, hwnd, NULL))
      {
      case ID_MENU_INSTALL:
        hook_install_();
        break;
      case ID_MENU_UNINSTALL:
        hook_uninstall_();
        break;
      case ID_MENU_HIDE:
        Shell_NotifyIcon(NIM_DELETE, &g_idata);
        break;
      case ID_MENU_EXIT:
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        break;
      }
      break;
    }
    return 0;
  }

  switch(msg)
  {
  case WM_CREATE:
    g_hwndEdit = CreateWindow("edit", "",
      WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
      0, 0, 0, 0,
      hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
    );
    SendMessage(g_hwndEdit, WM_SETFONT, (WPARAM)GetStockObject(SYSTEM_FIXED_FONT), 0);
    SendMessage(g_hwndEdit, EM_LIMITTEXT, 1024 * 1024 * 1024, 0);
    break;
  case WM_SIZE:
    MoveWindow(g_hwndEdit, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
    break;
  case WM_SYSCOMMAND:
    switch(wp & 0xFFF0)
    {
    case SC_MINIMIZE:
      Shell_NotifyIcon(NIM_ADD, &g_idata);
      ShowWindow(hwnd, SW_HIDE);
      return 0; break;
    }
    break;
  case WM_CLOSE:
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_COPYDATA:
//    if(IsWindowVisible(hwnd))
    {
      PCOPYDATASTRUCT data = (PCOPYDATASTRUCT)lp;
      int n = GetWindowTextLength(g_hwndEdit);
      SendMessage(g_hwndEdit, EM_SETSEL, n, n);
      SendMessage(g_hwndEdit, EM_REPLACESEL, 0, (LPARAM)data->lpData);
    }
    break;
  }

  return DefWindowProc(hwnd, msg, wp, lp);
}