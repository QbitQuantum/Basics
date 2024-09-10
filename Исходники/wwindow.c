static LRESULT CALLBACK window_callback(HWND hWnd, UINT message, 
    WPARAM wParam, LPARAM lParam)
{
   ALLEGRO_DISPLAY *d = NULL;
   ALLEGRO_DISPLAY_WIN *win_display = NULL;
   unsigned int i;
   ALLEGRO_EVENT_SOURCE *es = NULL;
   ALLEGRO_SYSTEM *system = al_get_system_driver();

   if (message == _al_win_msg_call_proc) {
      ((void (*)(void*))wParam) ((void*)lParam);
      return 0;
   }

   if (!system) {
      return DefWindowProc(hWnd,message,wParam,lParam); 
   }

   if (message == _al_win_msg_suicide && wParam) {
      win_display = (ALLEGRO_DISPLAY_WIN*)wParam;
      break_window_message_pump(win_display, hWnd);
      DestroyWindow(hWnd);
      return 0;
   }

   for (i = 0; i < system->displays._size; i++) {
      ALLEGRO_DISPLAY **dptr = _al_vector_ref(&system->displays, i);
      d = *dptr;
      win_display = (void*)d;
      if (win_display->window == hWnd) {
         es = &d->es;
         break;
      }
   }

   if (i == system->displays._size)
      return DefWindowProc(hWnd,message,wParam,lParam); 

   if (message == _al_win_msg_suicide) {
      break_window_message_pump(win_display, hWnd);
      DestroyWindow(hWnd);
      return 0;
   }

   switch (message) {
      case WM_INPUT: 
      {
         /* RAW Input is currently unused. */
          UINT dwSize;
          LPBYTE lpb;
          RAWINPUT* raw;

          /* We can't uninstall WM_INPUT mesages. */
          if (!al_is_mouse_installed())
             break;

          GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, 
                          sizeof(RAWINPUTHEADER));
          lpb = al_malloc(sizeof(BYTE)*dwSize);
          if (lpb == NULL) 
              break;

          GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
          raw = (RAWINPUT*)lpb;

          if (raw->header.dwType != RIM_TYPEMOUSE) {
             al_free(lpb); 
             break;
          }

       {
          RAWMOUSE *rm = &raw->data.mouse;
          int x = raw->data.mouse.lLastX;
          int y = raw->data.mouse.lLastY;
          bool abs = (rm->usFlags & (MOUSE_MOVE_ABSOLUTE
                                    | MOUSE_VIRTUAL_DESKTOP)) != 0;
          if (abs || x || y)
             _al_win_mouse_handle_move(x, y, abs, win_display);

          if (rm->usButtonFlags & RI_MOUSE_BUTTON_1_DOWN)
             _al_win_mouse_handle_button(1, true, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_1_UP)
             _al_win_mouse_handle_button(1, false, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_2_DOWN)
             _al_win_mouse_handle_button(2, true, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_2_UP)
             _al_win_mouse_handle_button(2, false, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_3_DOWN)
             _al_win_mouse_handle_button(3, true, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_3_UP)
             _al_win_mouse_handle_button(3, false, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_4_DOWN)
             _al_win_mouse_handle_button(4, true, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_4_UP)
             _al_win_mouse_handle_button(4, false, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_5_DOWN)
             _al_win_mouse_handle_button(5, true, x, y, abs, win_display);
          if (rm->usButtonFlags & RI_MOUSE_BUTTON_5_UP)
             _al_win_mouse_handle_button(5, false, x, y, abs, win_display);

          if (rm->usButtonFlags & RI_MOUSE_WHEEL) {
             SHORT z = (SHORT)rm->usButtonData;
             _al_win_mouse_handle_wheel(z / WHEEL_DELTA, false, win_display);
          }
       }

          al_free(lpb); 
          break;
      }
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP: {
         int mx = GET_X_LPARAM(lParam);
         int my = GET_Y_LPARAM(lParam);
         bool down = (message == WM_LBUTTONDOWN);
         _al_win_mouse_handle_button(1, down, mx, my, true, win_display);
         handle_mouse_capture(down, hWnd);
         break;
      }
      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP: {
         int mx = GET_X_LPARAM(lParam);
         int my = GET_Y_LPARAM(lParam);
         bool down = (message == WM_MBUTTONDOWN);
         _al_win_mouse_handle_button(3, down, mx, my, true, win_display);
         handle_mouse_capture(down, hWnd);
         break;
      }
      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP: {
         int mx = GET_X_LPARAM(lParam);
         int my = GET_Y_LPARAM(lParam);
         bool down = (message == WM_RBUTTONDOWN);
         _al_win_mouse_handle_button(2, down, mx, my, true, win_display);
         handle_mouse_capture(down, hWnd);
         break;
      }
      case WM_XBUTTONDOWN:
      case WM_XBUTTONUP: {
         int mx = GET_X_LPARAM(lParam);
         int my = GET_Y_LPARAM(lParam);
         int button = HIWORD(wParam);
         bool down = (message == WM_XBUTTONDOWN);
         if (button == XBUTTON1)
            _al_win_mouse_handle_button(4, down, mx, my, true, win_display);
         else if (button == XBUTTON2)
            _al_win_mouse_handle_button(5, down, mx, my, true, win_display);
         handle_mouse_capture(down, hWnd);
         return TRUE;
      }
      case WM_MOUSEWHEEL: {
         int d = GET_WHEEL_DELTA_WPARAM(wParam);
         _al_win_mouse_handle_wheel(d / WHEEL_DELTA, false, win_display);
         return TRUE;
      }
      case WM_MOUSEHWHEEL: {
         int d = GET_WHEEL_DELTA_WPARAM(wParam);
         _al_win_mouse_handle_hwheel(d / WHEEL_DELTA, false, win_display);
         return TRUE;
      }
      case WM_MOUSEMOVE: {
         TRACKMOUSEEVENT tme;
         int mx = GET_X_LPARAM(lParam);
         int my = GET_Y_LPARAM(lParam);

         if (win_display->mouse_cursor_shown && we_hid_the_mouse) {
            we_hid_the_mouse = false;
            win_display->display.vt->hide_mouse_cursor((void*)win_display);
         }

         _al_win_mouse_handle_move(mx, my, true, win_display);
         if (mx >= 0 && my >= 0 && mx < d->w && my < d->h) {
            tme.cbSize = sizeof(tme);
            tme.dwFlags = TME_QUERY;
            if (TrackMouseEvent(&tme) && !tme.hwndTrack) {
               tme.dwFlags = TME_LEAVE;
               tme.hwndTrack = hWnd;
               tme.dwHoverTime = 0;
               TrackMouseEvent(&tme);
               _al_win_mouse_handle_enter(win_display);
            }
         }

         /* WM_SETCURSOR messages are not received while the mouse is
          * captured.  We call SetCursor here so that changing the mouse
          * cursor has an effect while the user is holding down the mouse
          * button.
          */
         if (GetCapture() == hWnd && win_display->mouse_cursor_shown) {
            SetCursor(win_display->mouse_selected_hcursor);
         }

         break;
      }
      case WM_MOUSELEAVE: {
         _al_win_mouse_handle_leave(win_display);
         break;
      }
      case WM_CAPTURECHANGED: {
         if (al_is_mouse_installed()) {
            int i;
            ALLEGRO_MOUSE_STATE state;
            if (!lParam || (HWND)lParam == hWnd)
               break;
            al_get_mouse_state(&state);
            for (i = 1; i <= 5; i++) {
               if (al_mouse_button_down(&state, i))
                  _al_win_mouse_handle_button(i, 0, 0, 0, true, win_display);
            }
         }
         break;
      }
      case WM_NCMOUSEMOVE: {
         if (!win_display->mouse_cursor_shown) {
            we_hid_the_mouse = true;
            win_display->display.vt->show_mouse_cursor((void*)win_display);
         }
         break;
      }
      case WM_SYSKEYDOWN: {
         int vcode = wParam;
         bool extended = (lParam >> 24) & 0x1;
         bool repeated  = (lParam >> 30) & 0x1;
         _al_win_kbd_handle_key_press(0, vcode, extended, repeated, win_display);
         break;
      }
      case WM_KEYDOWN: {
         int vcode = wParam; 
         int scode = (lParam >> 16) & 0xff;
         bool extended = (lParam >> 24) & 0x1;
         bool repeated = (lParam >> 30) & 0x1;
         /* We can't use TranslateMessage() because we don't know if it will
            produce a WM_CHAR or not. */
         _al_win_kbd_handle_key_press(scode, vcode, extended, repeated, win_display);
         break;
      }
      case WM_SYSKEYUP:
      case WM_KEYUP: {
         int vcode = wParam;
         int scode = (lParam >> 16) & 0xff;
         bool extended = (lParam >> 24) & 0x1;
         _al_win_kbd_handle_key_release(scode, vcode, extended, win_display);
         break;
      }
      case WM_SYSCOMMAND: {
         if (_al_win_disable_screensaver &&
               ((wParam & 0xfff0) == SC_MONITORPOWER || (wParam & 0xfff0) == SC_SCREENSAVE)) {
            return 0;
         }
         else if ((wParam & 0xfff0) == SC_KEYMENU) {
            /* Prevent Windows from intercepting the ALT key.
               (Disables opening menus via the ALT key.) */
            return 0;
         }
         break;
      }
      case WM_PAINT: {
         if (win_display->display.flags & ALLEGRO_GENERATE_EXPOSE_EVENTS) {
            RECT r;
            HRGN hrgn;
            GetWindowRect(win_display->window, &r);
            hrgn = CreateRectRgn(r.left, r.top, r.right, r.bottom);
            if (GetUpdateRgn(win_display->window, hrgn, false) != ERROR) {
               PAINTSTRUCT ps;
               DWORD size;
               LPRGNDATA rgndata;
               int n;
               int i;
               RECT *rects;
               BeginPaint(win_display->window, &ps);
               size = GetRegionData(hrgn, 0, NULL);
               rgndata = al_malloc(size);
               GetRegionData(hrgn, size, rgndata);
               n = rgndata->rdh.nCount;
               rects = (RECT *)rgndata->Buffer;
               _al_event_source_lock(es);
               if (_al_event_source_needs_to_generate_event(es)) {
                  ALLEGRO_EVENT event;
                  event.display.type = ALLEGRO_EVENT_DISPLAY_EXPOSE;
                  event.display.timestamp = al_get_time();
                  for (i = 0; i < n; i++) {
                     event.display.x = rects[i].left;
                     event.display.y = rects[i].top;
                     event.display.width = rects[i].right - rects[i].left;
                     event.display.height = rects[i].bottom - rects[i].top;
                     _al_event_source_emit_event(es, &event);
                  }
               }
               _al_event_source_unlock(es);
               al_free(rgndata);
               EndPaint(win_display->window, &ps);
               DeleteObject(hrgn);
            }
            return 0;
         }
         break;
      }

      case WM_SETCURSOR:
         switch (LOWORD(lParam)) {
            case HTLEFT:
            case HTRIGHT:
               SetCursor(LoadCursor(NULL, IDC_SIZEWE));
               break;
            case HTBOTTOM:
            case HTTOP:
               SetCursor(LoadCursor(NULL, IDC_SIZENS));
               break;
            case HTBOTTOMLEFT:
            case HTTOPRIGHT:
               SetCursor(LoadCursor(NULL, IDC_SIZENESW));
               break;
            case HTBOTTOMRIGHT:
            case HTTOPLEFT:
               SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
               break;
            default:
               if (win_display->mouse_cursor_shown) {
                  SetCursor(win_display->mouse_selected_hcursor);
               }
               else {
                  SetCursor(NULL);
               }
               break;
         }
         return 1;
      case WM_ACTIVATE:
         if (HIWORD(wParam) && LOWORD(wParam) != WA_INACTIVE)
            break;

         if (HIWORD(wParam))
            d->flags |= ALLEGRO_MINIMIZED;
         else
            d->flags &= ~ALLEGRO_MINIMIZED;

         if (LOWORD(wParam) != WA_INACTIVE) {
            // Make fullscreen windows TOPMOST again
            if (d->flags & ALLEGRO_FULLSCREEN_WINDOW) {
               SetWindowPos(win_display->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            }
            if (d->vt->switch_in)
               d->vt->switch_in(d);
            _al_win_fix_modifiers();
            _al_event_source_lock(es);
            if (_al_event_source_needs_to_generate_event(es)) {
               ALLEGRO_EVENT event;
               memset(&event, 0, sizeof(event));
               event.display.type = ALLEGRO_EVENT_DISPLAY_SWITCH_IN;
               event.display.timestamp = al_get_time();
               _al_event_source_emit_event(es, &event);
            }
            _al_event_source_unlock(es);
            _al_win_grab_input(win_display);
            return 0;
         }
         else {
            // Remove TOPMOST flag from fullscreen windows so we can alt-tab. Also must raise the new activated window
            if (d->flags & ALLEGRO_FULLSCREEN_WINDOW) {
               SetWindowPos(win_display->window, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
               SetWindowPos(GetForegroundWindow(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            }
            // Show the taskbar in case we hid it
            SetWindowPos(FindWindow("Shell_traywnd", ""), 0, 0, 0, 0, 0, SWP_SHOWWINDOW);
            if (d->flags & ALLEGRO_FULLSCREEN) {
               d->vt->switch_out(d);
            }
            _al_event_source_lock(es);
            if (_al_event_source_needs_to_generate_event(es)) {
               ALLEGRO_EVENT event;
               memset(&event, 0, sizeof(event));
               event.display.type = ALLEGRO_EVENT_DISPLAY_SWITCH_OUT;
               event.display.timestamp = al_get_time();
               _al_event_source_emit_event(es, &event);
            }
            _al_event_source_unlock(es);
            return 0;
         }
         break;
      case WM_MENUCHAR :
         return (MNC_CLOSE << 16) | (wParam & 0xffff);
      case WM_CLOSE:
         _al_event_source_lock(es);
         if (_al_event_source_needs_to_generate_event(es)) {
            ALLEGRO_EVENT event;
            memset(&event, 0, sizeof(event));
            event.display.type = ALLEGRO_EVENT_DISPLAY_CLOSE;
            event.display.timestamp = al_get_time();
            _al_event_source_emit_event(es, &event);
         }
         _al_event_source_unlock(es);
         return 0;
      case WM_SIZE:
         if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED || wParam == SIZE_MINIMIZED) {
            /*
             * Delay the resize event so we don't get bogged down with them
             */
            if (!resize_postponed) {
               resize_postponed = true;
               _beginthread(postpone_thread_proc, 0, (void *)d);
            }
         }
         return 0;
      case WM_ENTERSIZEMOVE:
         /* DefWindowProc for WM_ENTERSIZEMOVE enters a modal loop, which also
          * ends up blocking the loop in d3d_display_thread_proc (which is
          * where we are called from, if using D3D).  Rather than batching up
          * intermediate resize events which the user cannot acknowledge in the
          * meantime anyway, make it so only a single resize event is generated
          * at WM_EXITSIZEMOVE.
          */
         if (d->flags & ALLEGRO_DIRECT3D) {
            resize_postponed = true;
         }
         break;
      case WM_EXITSIZEMOVE:
         if (resize_postponed) {
            win_generate_resize_event(win_display);
            win_display->ignore_resize = false;
            resize_postponed = false;
            win_display->can_acknowledge = true;
         }
         break;
   } 

   return DefWindowProc(hWnd,message,wParam,lParam); 
}