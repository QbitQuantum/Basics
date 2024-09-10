    LRESULT CALLBACK WndProc (HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam)
    {
      switch (message)
      {
        case WM_CREATE:
            return 0;
        case WM_CLOSE:
            PostQuitMessage (0);
            return 0;

        case WM_DESTROY:
            return 0;

        case WM_SIZE:
            return 0;

        case WM_SETCURSOR:
            SetCursor(LoadCursor(NULL, currentCursor));
            return 0;

        case WM_KEYDOWN:
            last_keybdstatus[wParam]=keybdstatus[wParam];
            keybdstatus[wParam]=1;
            return 0;

        case WM_KEYUP:
            last_keybdstatus[wParam]=keybdstatus[wParam];
            keybdstatus[wParam]=0;
            return 0;

        case WM_SYSKEYDOWN:
            last_keybdstatus[wParam]=keybdstatus[wParam];
            keybdstatus[wParam]=1;
            if (wParam!=18)
            {
              if ((lParam&(1<<29))>0)
                   last_keybdstatus[18]=keybdstatus[18], keybdstatus[18]=1;
              else last_keybdstatus[18]=keybdstatus[18], keybdstatus[18]=0;
            }
            return 0;

        case WM_SYSKEYUP:
            last_keybdstatus[wParam]=keybdstatus[wParam];
            keybdstatus[wParam]=0;
            if (wParam!=(unsigned int)18)
            {
              if ((lParam&(1<<29))>0)
                   last_keybdstatus[18]=keybdstatus[18], keybdstatus[18]=0;
              else last_keybdstatus[18]=keybdstatus[18], keybdstatus[18]=1;
            }
            return 0;

        case WM_MOUSEWHEEL:
             vdeltadelta += (int)HIWORD(wParam);
             mouse_vscrolls += vdeltadelta / WHEEL_DELTA;
             vdeltadelta %= WHEEL_DELTA;
             return 0;

        case WM_MOUSEHWHEEL:
             hdeltadelta += (int)HIWORD(wParam);
             mouse_hscrolls += hdeltadelta / WHEEL_DELTA;
             hdeltadelta %= WHEEL_DELTA;
             return 0;

        case WM_LBUTTONUP:   mousestatus[0]=0; return 0;
        case WM_LBUTTONDOWN: mousestatus[0]=1; return 0;
        case WM_RBUTTONUP:   mousestatus[1]=0; return 0;
        case WM_RBUTTONDOWN: mousestatus[1]=1; return 0;
        case WM_MBUTTONUP:   mousestatus[2]=0; return 0;
        case WM_MBUTTONDOWN: mousestatus[2]=1; return 0;

        default:
            return DefWindowProc (hWnd, message, wParam, lParam);
      }
    }