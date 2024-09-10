static LRESULT CALLBACK _window_proc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {    
  TRACKMOUSEEVENT tme = {0};

  switch ( msg ) {
    case APP_WINDOW_CREATE: {
      RECT rect;
      GetClientRect(hwnd, &rect);
      window.w = rect.right-rect.left;
      window.h = rect.bottom-rect.top;
      window.created = 1;
      pushL_windowevent("create");      
      return 0;
                            }

    case WM_ACTIVATEAPP:
      if ( wparam ) {
        window.activated = 1;
        SetForegroundWindow(hwnd);
        LockSetForegroundWindow( LSFW_LOCK );
        InvalidateRect(hwnd, 0, 0);
        if (window.created) pushL_windowevent("activate");
      }
      else {
        window.activated = 0;
        if (window.created) pushL_windowevent("deactivate");
      }          
      return 0;

    case APP_TICK:  
	  window.timerposted = 0;
      pushL_tick();      
      return 0;

    case WM_DESTROY:      
      PostQuitMessage(0);
      return 0;

    case WM_SHOWWINDOW:
      if (wparam) {
        if (window.created) pushL_windowevent("show");
      } 
      else {
        if (window.created) pushL_windowevent("hide");
      }
      return 0;

    case WM_MOVE:
      if ( !IsIconic( hwnd ) ) {
        window.x = (int)(short)LOWORD( lparam );
        window.y = (int)(short)HIWORD( lparam );
        if (window.created) pushL_windowevent("move");        
      }
      return 0;    

    case WM_SIZE:
      if ( SIZE_MAXIMIZED == wparam || SIZE_RESTORED == wparam ) {
        window.w = LOWORD( lparam );
        window.h = HIWORD( lparam );
        if (window.created) {
          pushL_windowevent("resize");              
          pushL_draw();        
          SwapBuffers(window.hdc);  
        }
      }
      return 0;

    case WM_ERASEBKGND:
      return 1;

    case WM_PAINT:
      if ( GetUpdateRect(hwnd, 0, FALSE) ) {
        ValidateRect(hwnd, 0 );
        pushL_draw();        
        SwapBuffers(window.hdc);  
      }
      return 0;

    case WM_APPCOMMAND:
      switch ( GET_APPCOMMAND_LPARAM( lparam ) ) {
        case APPCOMMAND_COPY: 
          pushL_command("copy");
          break;
        case APPCOMMAND_CUT:   
          pushL_command("cut");
          break;
        case APPCOMMAND_PASTE: 
          pushL_command("paste");
          break;
        default:
          return DefWindowProc(hwnd, msg, wparam, lparam);
      }
      return 1;
    
    case WM_MBUTTONDBLCLK:
      pushL_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_LBUTTONDBLCLK:
      pushL_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_RBUTTONDBLCLK:
      pushL_mousedblclick(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_MBUTTONDOWN:
      SetCapture( hwnd );
      pushL_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_LBUTTONDOWN:
      SetCapture( hwnd );
      pushL_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_RBUTTONDOWN:
      SetCapture( hwnd );
      pushL_mousedown(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;

    case WM_MBUTTONUP:
      ReleaseCapture();
      pushL_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "middle", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;  

    case WM_LBUTTONUP:
      ReleaseCapture();
      pushL_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "left", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;  

    case WM_RBUTTONUP:    
      ReleaseCapture();
      pushL_mouseup(GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), "right", 
        GetKeyState( VK_MENU ) & 0x8000, 
        GetKeyState( VK_CONTROL ) & 0x8000, 
        GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;    

    case WM_CHAR:
	
      if ( ( 32 <= ( wparam & 0xFF ) )) {
		pushL_char(wparam);  
      }	  
      return 0;    

    case WM_MOUSELEAVE:
      window.tracking = 0;
      pushL_mouseexit();
      return 0;

    case WM_MOUSEMOVE:
      SetCursor( window.hcursor );
      if ( !window.tracking ) {
        window.tracking = 1;

        tme.cbSize = sizeof( TRACKMOUSEEVENT );
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;
        tme.dwHoverTime = HOVER_DEFAULT;

        TrackMouseEvent( &tme );

        pushL_mouseenter();
      }

      pushL_mousemove(GET_X_LPARAM(lparam ), GET_Y_LPARAM(lparam ), 
        GetKeyState( VK_MENU ) & 0x8000,
        GetKeyState( VK_CONTROL ) & 0x8000,
        GetKeyState( VK_SHIFT ) & 0x8000);      
      return 0;

    case WM_MOUSEWHEEL:
      {
        POINT pt;
        UINT step;
        SystemParametersInfo( SPI_GETWHEELSCROLLLINES, 0, &step, 0 );

        pt.x = GET_X_LPARAM( lparam );
        pt.y = GET_Y_LPARAM( lparam );
        ScreenToClient(hwnd, &pt);
        pushL_mousewheel(pt.x, pt.y, 
          GET_WHEEL_DELTA_WPARAM( wparam ) / WHEEL_DELTA,
          step,
          GetKeyState( VK_MENU ) & 0x8000,
          GetKeyState( VK_CONTROL ) & 0x8000,
          GetKeyState( VK_SHIFT ) & 0x8000);        
      }  
      return 0;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      if ( KF_REPEAT & HIWORD( lparam ) ) {
        pushL_keypress(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      }
      else {
        pushL_keydown(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      }
      if ( GetKeyState( VK_CONTROL ) & 0x8000 ) {
        switch ( wparam ) {
          case 0x43:
            pushL_command("copy");
            break;
          case 0x58:
            pushL_command("cut");            
            break;
          case 0x56:
            pushL_command("paste");            
            break;         
        }        
      }
      return 0;

    case WM_KEYUP:
    case WM_SYSKEYUP:  
      pushL_keyup(_translate_keyboard_key( wparam ),
          GetKeyState( VK_MENU ) & 0x8000, 
          GetKeyState( VK_CONTROL ) & 0x8000, 
          GetKeyState( VK_SHIFT ) & 0x8000);
      return 0;
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}