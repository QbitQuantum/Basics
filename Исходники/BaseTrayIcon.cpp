LRESULT CALLBACK CBaseTrayIcon::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  CBaseTrayIcon *icon = (CBaseTrayIcon *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
  switch(uMsg) {
  case WM_DESTROY:
    Shell_NotifyIcon(NIM_DELETE, &icon->m_NotifyIconData);
    PostQuitMessage(0);
    break;
  case MSG_QUIT:
    DestroyWindow(hwnd);
    break;
  case MSG_TRAYICON:
    {
      UINT trayMsg = LOWORD(lParam);
      if (icon) {
        switch (trayMsg) {
        case WM_LBUTTONUP:
          if (!icon->m_bPropPageOpen) {
            icon->OpenPropPage();
          } else {
            EnumThreadWindows(GetCurrentThreadId(), enumWindowCallback, (LPARAM)icon->m_hWnd);
          }
          break;
        case WM_RBUTTONUP:
        case WM_CONTEXTMENU:
          if (icon->m_bPropPageOpen) {
            break;
          }
          HMENU hMenu = icon->GetPopupMenu();
          if (hMenu) {
            POINT p;
            GetCursorPos(&p);
            SetForegroundWindow(hwnd);
            int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, p.x, p.y, 0, hwnd, NULL);
            PostMessage(hwnd, WM_NULL, 0, 0);
            icon->ProcessMenuCommand(hMenu, cmd);
            DestroyMenu(hMenu);
          }
          break;
        }
      }
    }
    break;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}