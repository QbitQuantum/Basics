LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BOOL  fBlocking, fValidBox ;
     static POINT ptBeg, ptEnd, ptBoxBeg, ptBoxEnd ;
     HDC          hdc ;
     PAINTSTRUCT  ps ;
     
     switch (message)
     {
     case WM_LBUTTONDOWN :
          ptBeg.x = ptEnd.x = LOWORD (lParam) ;
          ptBeg.y = ptEnd.y = HIWORD (lParam) ;
          
          DrawBoxOutline (hwnd, ptBeg, ptEnd) ;
          
          SetCursor (LoadCursor (NULL, IDC_CROSS)) ;
          
          fBlocking = TRUE ;
          return 0 ;
          
     case WM_MOUSEMOVE :
          if (fBlocking)
          {
               SetCursor (LoadCursor (NULL, IDC_CROSS)) ;
               
               DrawBoxOutline (hwnd, ptBeg, ptEnd) ;
               
               ptEnd.x = LOWORD (lParam) ;
               ptEnd.y = HIWORD (lParam) ;
               
               DrawBoxOutline (hwnd, ptBeg, ptEnd) ;
          }
          return 0 ;
          
     case WM_LBUTTONUP :
          if (fBlocking)
          {
               DrawBoxOutline (hwnd, ptBeg, ptEnd) ;
               
               ptBoxBeg   = ptBeg ;
               ptBoxEnd.x = LOWORD (lParam) ;
               ptBoxEnd.y = HIWORD (lParam) ;
               
               SetCursor (LoadCursor (NULL, IDC_ARROW)) ;
               
               fBlocking = FALSE ;
               fValidBox  = TRUE ;
               
               InvalidateRect (hwnd, NULL, TRUE) ;
          }
          return 0 ;
          
     case WM_CHAR :
          if (fBlocking & (wParam == '\x1B'))     // i.e., Escape
          {
               DrawBoxOutline (hwnd, ptBeg, ptEnd) ;
               
               SetCursor (LoadCursor (NULL, IDC_ARROW)) ;
               
               fBlocking = FALSE ;
          }
          return 0 ;
          
     case WM_PAINT :
          hdc = BeginPaint (hwnd, &ps) ;
          
          if (fValidBox)
          {
               SelectObject (hdc, GetStockObject (BLACK_BRUSH)) ;
               Rectangle (hdc, ptBoxBeg.x, ptBoxBeg.y,
                    ptBoxEnd.x, ptBoxEnd.y) ;
          }
          
          if (fBlocking)
          {
               SetROP2 (hdc, R2_NOT) ;
               SelectObject (hdc, GetStockObject (NULL_BRUSH)) ;
               Rectangle (hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y) ;
          }
          
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}