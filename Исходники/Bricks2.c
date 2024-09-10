LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BITMAP  bitmap = { 0, 8, 8, 2, 1, 1 } ;
     static BYTE    bits [8][2] = { 0xFF, 0, 0x0C, 0, 0x0C, 0, 0x0C, 0,
                                    0xFF, 0, 0xC0, 0, 0xC0, 0, 0xC0, 0 } ;
     static HBITMAP hBitmap ;
     static int     cxClient, cyClient, cxSource, cySource ;
     HDC            hdc, hdcMem ;
     int            x, y ;
     PAINTSTRUCT    ps ;
     
     switch (message)
     {
     case WM_CREATE:
          bitmap.bmBits = bits ;
          hBitmap = CreateBitmapIndirect (&bitmap) ;
          cxSource = bitmap.bmWidth ;
          cySource = bitmap.bmHeight ;
          return 0 ;

     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          hdcMem = CreateCompatibleDC (hdc) ;
          SelectObject (hdcMem, hBitmap) ;

          for (y = 0 ; y < cyClient ; y += cySource)
          for (x = 0 ; x < cxClient ; x += cxSource)
          {
               BitBlt (hdc, x, y, cxSource, cySource, hdcMem, 0, 0, SRCCOPY) ;
          }

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