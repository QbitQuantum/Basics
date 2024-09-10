LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HPALETTE hPalette ;
     static int      cxClient, cyClient ;
     HDC             hdc ;
     PAINTSTRUCT     ps ;

     switch (message)
     {
     case WM_CREATE:
          if (!CheckDisplay (hwnd))
               return -1 ;

          hPalette = CreateRoutine (hwnd) ;
          return 0 ;
     
     case WM_DISPLAYCHANGE:
          if (!CheckDisplay (hwnd))
               DestroyWindow (hwnd) ;

          return 0 ;

     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          SelectPalette (hdc, hPalette, FALSE) ;
          RealizePalette (hdc) ;

          PaintRoutine (hdc, cxClient, cyClient) ;

          EndPaint (hwnd, &ps) ;
          return 0 ;

     case WM_TIMER:
          hdc = GetDC (hwnd) ;

          SelectPalette (hdc, hPalette, FALSE) ;

          TimerRoutine (hdc, hPalette) ;

          ReleaseDC (hwnd, hdc) ;
          return 0 ;

     case WM_QUERYNEWPALETTE:
          if (!hPalette)
               return FALSE ;

          hdc = GetDC (hwnd) ;
          SelectPalette (hdc, hPalette, FALSE) ;
          RealizePalette (hdc) ;
          InvalidateRect (hwnd, NULL, TRUE) ;

          ReleaseDC (hwnd, hdc) ;
          return TRUE ;

     case WM_PALETTECHANGED:
          if (!hPalette || (HWND) wParam == hwnd)
               break ;

          hdc = GetDC (hwnd) ;
          SelectPalette (hdc, hPalette, FALSE) ;
          RealizePalette (hdc) ;
          UpdateColors (hdc) ;

          ReleaseDC (hwnd, hdc) ;
          break ;

     case WM_DESTROY:
          DestroyRoutine (hwnd, hPalette) ;
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}