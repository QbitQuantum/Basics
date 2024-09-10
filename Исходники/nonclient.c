LRESULT
DefWndNCLButtonDblClk(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
  ULONG Style;

  Style = GetWindowLongPtrW(hWnd, GWL_STYLE);
  switch(wParam)
  {
    case HTCAPTION:
    {
      /* Maximize/Restore the window */
      if((Style & WS_CAPTION) == WS_CAPTION && (Style & WS_MAXIMIZEBOX))
      {
        SendMessageW(hWnd, WM_SYSCOMMAND, ((Style & (WS_MINIMIZE | WS_MAXIMIZE)) ? SC_RESTORE : SC_MAXIMIZE), 0);
      }
      break;
    }
    case HTSYSMENU:
    {
      HMENU hSysMenu = GetSystemMenu(hWnd, FALSE);
      UINT state = GetMenuState(hSysMenu, SC_CLOSE, MF_BYCOMMAND);
                  
      /* If the close item of the sysmenu is disabled or not present do nothing */
      if ((state & (MF_DISABLED | MF_GRAYED)) || (state == 0xFFFFFFFF))
          break;

      SendMessageW(hWnd, WM_SYSCOMMAND, SC_CLOSE, lParam);
      break;
    }
    default:
      return DefWndNCLButtonDown(hWnd, wParam, lParam);
  }
  return(0);
}