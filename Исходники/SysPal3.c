LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HBITMAP hBitmap ;
     static int     cxClient, cyClient ;
     BYTE           bits [256] ;
     HDC            hdc, hdcMem ;
     int            i ;
     PAINTSTRUCT    ps ;

     switch (message)
     {
     case WM_CREATE:
          if (!CheckDisplay (hwnd))
               return -1 ;

          for (i = 0 ; i < 256 ; i++)
               bits [i] = i ;
          
          hBitmap = CreateBitmap (16, 16, 1, 8, &bits) ;
          return 0 ;
                                                        
     case WM_DISPLAYCHANGE:
          if (!CheckDisplay)
               DestroyWindow (hwnd) ;

          return 0 ;

     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          hdcMem = CreateCompatibleDC (hdc) ;
          SelectObject (hdcMem, hBitmap) ;

          StretchBlt (hdc,    0, 0, cxClient, cyClient,
                      hdcMem, 0, 0, 16, 16, SRCCOPY) ;

          DeleteDC (hdcMem) ;
          EndPaint (hwnd, &ps) ;
          return 0 ;

     case WM_DESTROY:
          DeleteObject (hBitmap) ;
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}