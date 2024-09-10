static LRESULT CALLBACK window_callback(HWND hWnd, UINT message, 
    WPARAM wParam, LPARAM lParam)
{
   ALLEGRO_DISPLAY *d = NULL;
   ALLEGRO_DISPLAY_WIN *win_display = NULL;
   WINDOWINFO wi;
   int w;
   int h;
   int x;
   int y;
   unsigned int i;
   ALLEGRO_EVENT_SOURCE *es = NULL;
   ALLEGRO_SYSTEM *system = al_get_system_driver();

   wi.cbSize = sizeof(WINDOWINFO);

   if (message == _al_win_msg_call_proc) {
      ((void (*)(void*))wParam) ((void*)lParam);
      return 0;
   }

   if (!system) {
      return DefWindowProc(hWnd,message,wParam,lParam); 
   }

   if (message == _al_win_msg_suicide && wParam) {
      win_display = (ALLEGRO_DISPLAY_WIN*)wParam;
      win_display->end_thread = true;
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
      win_display->end_thread = true;
      DestroyWindow(hWnd);
      return 0;
   }

   switch (message) {
      case WM_INPUT: 
      {
          UINT dwSize;
          LPBYTE lpb;
          RAWINPUT* raw;

          /* We can't uninstall WM_INPUT mesages. */
          if (!al_is_mouse_installed())
             break;

          GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, 
                          sizeof(RAWINPUTHEADER));
          lpb = malloc(sizeof(BYTE)*dwSize);
          if (lpb == NULL) 
              break;

          GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
          raw = (RAWINPUT*)lpb;

          if (raw->header.dwType != RIM_TYPEMOUSE) {
             free(lpb); 
             break;
          }

       {
          RAWMOUSE *rm = &raw->data.mouse;
          int x = raw->data.mouse.lLastX;
          int y = raw->data.mouse.lLastY;
          bool abs = rm->usFlags & (MOUSE_MOVE_ABSOLUTE
                                 || MOUSE_VIRTUAL_DESKTOP);
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

          free(lpb); 
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

         break;
      }
      case WM_MOUSELEAVE: {
          _al_win_mouse_handle_leave(win_display);
          break;
      }
      case WM_CAPTURECHANGED: if (al_is_mouse_installed()) {
         int i;
         ALLEGRO_MOUSE_STATE state;
         if (!lParam || (HWND)lParam == hWnd)
            break;
         al_get_mouse_state(&state);
         for (i = 1; i <= 5; i++) {
            if (al_mouse_button_down(&state, i))
               _al_win_mouse_handle_button(i, 0, 0, 0, true, win_display);
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
         bool repeated  = (lParam >> 30) & 0x1;
         _al_win_kbd_handle_key_press(0, vcode, repeated, win_display);
         break;
      }
      case WM_KEYDOWN: {
         int vcode = wParam; 
         int scode = (lParam >> 16) & 0xff;
         bool repeated  = (lParam >> 30) & 0x1;
         /* We can't use TranslateMessage() because we don't know if it will
            produce a WM_CHAR or not. */
         _al_win_kbd_handle_key_press(scode, vcode, repeated, win_display);
         break;
      }
      case WM_SYSKEYUP:
      case WM_KEYUP: {
         int vcode = wParam;
         _al_win_kbd_handle_key_release(vcode, win_display);
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
         if ((win_display->display.flags & ALLEGRO_GENERATE_EXPOSE_EVENTS) &&
                  _al_event_source_needs_to_generate_event(es)) {
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
               rgndata = _AL_MALLOC(size);
               GetRegionData(hrgn, size, rgndata);
               n = rgndata->rdh.nCount;
               rects = (RECT *)rgndata->Buffer;
               //GetWindowInfo(win_display->window, &wi);
               _al_event_source_lock(es);
               for (i = 0; i < n; i++) {
                  ALLEGRO_EVENT event;
                  event.display.type = ALLEGRO_EVENT_DISPLAY_EXPOSE;
                  event.display.timestamp = al_current_time();
                  event.display.x = rects[i].left;
                  event.display.y = rects[i].top;
                  event.display.width = rects[i].right - rects[i].left;
                  event.display.height = rects[i].bottom - rects[i].top;
                  _al_event_source_emit_event(es, &event);
               }
               _al_event_source_unlock(es);
               _AL_FREE(rgndata);
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
         if (LOWORD(wParam) != WA_INACTIVE) {
            /* This SetWindowPos is for faux-fullscreen windows that lost focus
             * so they can get placed back on top
             */
             // FIXME: this doesn't seem to work
            //SetWindowPos(win_display->window, HWND_TOP, 0, 0, 0, 0,
            //   SWP_NOMOVE | SWP_NOSIZE);
            if (d->vt->switch_in)
            	  d->vt->switch_in(d);
            _al_event_source_lock(es);
            if (_al_event_source_needs_to_generate_event(es)) {
               ALLEGRO_EVENT event;
               event.display.type = ALLEGRO_EVENT_DISPLAY_SWITCH_IN;
               event.display.timestamp = al_current_time();
               _al_event_source_emit_event(es, &event);
            }
            _al_event_source_unlock(es);
            _al_win_grab_input(win_display);
            return 0;
         }
         else {
            if (d->flags & ALLEGRO_FULLSCREEN) {
               d->vt->switch_out(d);
            }
            _al_event_source_lock(es);
            if (_al_event_source_needs_to_generate_event(es)) {
               ALLEGRO_EVENT event;
               event.display.type = ALLEGRO_EVENT_DISPLAY_SWITCH_OUT;
               event.display.timestamp = al_current_time();
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
            event.display.type = ALLEGRO_EVENT_DISPLAY_CLOSE;
            event.display.timestamp = al_current_time();
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
               postpone_resize(win_display->window);
            }
         }
         return 0;
      case WM_USER+0:
         /* Generate a resize event if the size has changed. We cannot asynchronously
          * change the display size here yet, since the user will only know about a
          * changed size after receiving the resize event. Here we merely add the
          * event to the queue.
          */
         GetWindowInfo(win_display->window, &wi);
         x = wi.rcClient.left;
         y = wi.rcClient.top;
         w = wi.rcClient.right - wi.rcClient.left;
         h = wi.rcClient.bottom - wi.rcClient.top;
         if (d->w != w || d->h != h) {
            _al_event_source_lock(es);
            if (_al_event_source_needs_to_generate_event(es)) {
               ALLEGRO_EVENT event;
               event.display.type = ALLEGRO_EVENT_DISPLAY_RESIZE;
               event.display.timestamp = al_current_time();
               event.display.x = x;
               event.display.y = y;
               event.display.width = w;
               event.display.height = h;
               _al_event_source_emit_event(es, &event);
            }

            /* Generate an expose event. */
            if (_al_event_source_needs_to_generate_event(es)) {
               ALLEGRO_EVENT event;
               event.display.type = ALLEGRO_EVENT_DISPLAY_EXPOSE;
               event.display.timestamp = al_current_time();
               event.display.x = x;
               event.display.y = y;
               event.display.width = w;
               event.display.height = h;
               _al_event_source_emit_event(es, &event);
            }
            _al_event_source_unlock(es);
         }
         resize_postponed = false;
         win_display->can_acknowledge = true;
         return 0;
   } 

   return DefWindowProc(hWnd,message,wParam,lParam); 
}