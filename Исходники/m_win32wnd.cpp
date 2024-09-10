LRESULT CALLBACK Win32ScreenDevice::WindowProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
  STRICT_REQUIRE ( g_win32ScreenDev != 0 );
  switch ( Msg )
  {
  case XEVENT:
    break;
  case WM_SIZE:
    if ( g_win32ScreenDev->attached_ ) g_win32ScreenDev->OnResize();
    break;
  case WM_CREATE:
    mouse_locked = false;
    ReleaseCapture();
    break;
  case WM_ACTIVATE:
    if ( LOWORD(wParam) != WA_INACTIVE )
      g_win32ScreenDev->isActive_ = true;
    else
      g_win32ScreenDev->isActive_ = false;
    g_win32ScreenDev->EnqueEvent(EVENT::MakeWindowActive(g_win32ScreenDev->isActive_));
    break;
  case WM_CLOSE:
    if (!g_win32ScreenDev->attached_)
    {
      PostMessage(hWnd,XCLOSE,0,0);
      return 0;
    }
    break;
  case WM_SETCURSOR:
    if(HTCLIENT == LOWORD(lParam))
    {
      if ( g_win32ScreenDev->enableCursor_ )
        SetCursor(g_win32ScreenDev->cursor_);
      else
        SetCursor(0);
      return TRUE;
    }
    break;
  case WM_PAINT:
    g_win32ScreenDev->MakeRubbish();
    if ( g_win32ScreenDev->attached_ )
      g_win32ScreenDev->OnPaint();
    break;
  case WM_GETDLGCODE:
    {
      if ( lParam && ((MSG*)lParam)->message == WM_KEYDOWN )
      {
        EVENT e = g_win32ScreenDev->ProcessMessage(*(MSG*)lParam);
        if ( e.type != EVENT::NONE )
          g_win32ScreenDev->EnqueEvent(e);
        return DLGC_WANTALLKEYS;
      }
      else
        return DLGC_WANTALLKEYS;
    }

  default:
    {
      MSG msg;
      msg.message = Msg;
      msg.lParam  = lParam;
      msg.wParam  = wParam;
      EVENT e = g_win32ScreenDev->ProcessMessage(msg);
      if ( e.type != EVENT::NONE )
        g_win32ScreenDev->EnqueEvent(e);
    }
  }
  return
    (defproc_ ? defproc_ : DefWindowProc)(hWnd,Msg,wParam,lParam);
}