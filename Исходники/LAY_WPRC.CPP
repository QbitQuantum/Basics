LRESULT CALLBACK EXPORT AWFrameWndProc
  (
  HWND    hwnd,
  UINT    uMsg,
  WPARAM  wParam,
  LPARAM  lParam
  )

  {
  LRESULT lRet;
  BOOL    fHandled;
  Window* pWnd;

  switch (uMsg)
    {
    case WM_CREATE:
      pWnd = (Window*)(((CREATESTRUCT*)lParam)->lpCreateParams);
      SetWindowLong(hwnd, I_GWL_WINDOW, (long)pWnd);
      pWnd->FrameWndCreated(hwnd);
      fHandled = TRUE;
      lRet = 0L;
      break;

    case WM_SIZE:
      pWnd = (Window*)GetWindowLong(hwnd, I_GWL_WINDOW);
      I_ASSERT(pWnd);
      HANDLE_WM_SIZE(hwnd, wParam, lParam, pWnd->Size);
      fHandled = FALSE;
      break;

    case WM_MOVE:
      pWnd = (Window*)GetWindowLong(hwnd, I_GWL_WINDOW);
      I_ASSERT(pWnd);
      HANDLE_WM_MOVE(hwnd, wParam, lParam, pWnd->Move);
      fHandled = FALSE;
      break;

    case WM_GETMINMAXINFO:
      pWnd = (Window*)GetWindowLong(hwnd, I_GWL_WINDOW);
      if(!pWnd) // this comes before WM_CREATE ... thanks MicroSUCKS
        pWnd = g_pWnd;
      I_ASSERT(pWnd);
      pWnd->GetMinMaxInfo((MINMAXINFO*)lParam);
      fHandled = TRUE;
      lRet = 0L;
      break;

    case WM_KEYDOWN:
      pWnd = (Window*)GetWindowLong(hwnd, I_GWL_WINDOW);
      I_ASSERT(pWnd);
      pWnd->GetLayout()->Shapes()->KeyDown(pWnd, pWnd->ClientWnd(), (int)wParam, lParam);
      fHandled = TRUE;
      lRet = 0L;
      break;

    case WM_KEYUP:
      pWnd = (Window*)GetWindowLong(hwnd, I_GWL_WINDOW);
      I_ASSERT(pWnd);
      pWnd->GetLayout()->Shapes()->KeyUp(pWnd, pWnd->ClientWnd(), (int)wParam, lParam);
      fHandled = TRUE;
      lRet = 0L;
      break;

    case WM_INITMENUPOPUP:
      I_ASSERT(GetSystemMenu(hwnd, FALSE) == (HMENU)wParam);
      EnableMenuItem((HMENU)wParam, 3, MF_BYPOSITION | MF_GRAYED);
      EnableMenuItem((HMENU)wParam, 4, MF_BYPOSITION | MF_GRAYED);
      fHandled = TRUE;
      lRet = 0L;
      break;

    case WM_SYSCOMMAND:
      switch(wParam & 0xFFF0)
        {
        case SC_MAXIMIZE:
        case SC_MINIMIZE:
          fHandled = TRUE;
          lRet = 0L;
          break;

        default:
          fHandled = FALSE;
          break;
        }
      break;

    default:
      fHandled = FALSE;
      break;
    }

  return fHandled ? lRet : DefWindowProc(hwnd, uMsg, wParam, lParam);
  }