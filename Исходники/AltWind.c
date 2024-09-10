LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static POINT aptFigure [10] = { 10,70, 50,70, 50,10, 90,10, 90,50,
                                     30,50, 30,90, 70,90, 70,30, 10,30 };
     static int   cxClient, cyClient ;
     HDC          hdc ;
     int          i ;
     PAINTSTRUCT  ps ;
     POINT        apt[10] ;
     
     switch (message)
     {
     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          SelectObject (hdc, GetStockObject (GRAY_BRUSH)) ;

          for (i = 0 ; i < 10 ; i++)
          {
               apt[i].x = cxClient * aptFigure[i].x / 200 ;
               apt[i].y = cyClient * aptFigure[i].y / 100 ;
          }

          SetPolyFillMode (hdc, ALTERNATE) ;
          Polygon (hdc, apt, 10) ;

          for (i = 0 ; i < 10 ; i++)
          {
               apt[i].x += cxClient / 2 ;
          }

          SetPolyFillMode (hdc, WINDING) ;
          Polygon (hdc, apt, 10) ;
          
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}