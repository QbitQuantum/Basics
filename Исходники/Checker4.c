LRESULT CALLBACK ChildWndProc (HWND hwnd, UINT message, 
                               WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
     
     switch (message)
     {
     case WM_CREATE :
          SetWindowLong (hwnd, 0, 0) ;       // on/off flag
          return 0 ;

     case WM_KEYDOWN:
               // Send most key presses to the parent window
          
          if (wParam != VK_RETURN && wParam != VK_SPACE)
          {
               SendMessage (GetParent (hwnd), message, wParam, lParam) ;
               return 0 ;
          }
               // For Return and Space, fall through to toggle the square
          
     case WM_LBUTTONDOWN :
          SetWindowLong (hwnd, 0, 1 ^ GetWindowLong (hwnd, 0)) ;
          SetFocus (hwnd) ;
          InvalidateRect (hwnd, NULL, FALSE) ;
          return 0 ;

               // For focus messages, invalidate the window for repaint
          
     case WM_SETFOCUS:
          idFocus = GetWindowLong (hwnd, GWL_ID) ;

               // Fall through

     case WM_KILLFOCUS:
          InvalidateRect (hwnd, NULL, TRUE) ;
          return 0 ;
          
     case WM_PAINT :
          hdc = BeginPaint (hwnd, &ps) ;
          
          GetClientRect (hwnd, &rect) ;
          Rectangle (hdc, 0, 0, rect.right, rect.bottom) ;

               // Draw the "x" mark
          
          if (GetWindowLong (hwnd, 0))
          {
               MoveToEx (hdc, 0,          0, NULL) ;
               LineTo   (hdc, rect.right, rect.bottom) ;
               MoveToEx (hdc, 0,          rect.bottom, NULL) ;
               LineTo   (hdc, rect.right, 0) ;
          }

               // Draw the "focus" rectangle
          
          if (hwnd == GetFocus ())
          {
               rect.left   += rect.right / 10 ;
               rect.right  -= rect.left ;
               rect.top    += rect.bottom / 10 ;
               rect.bottom -= rect.top ;

               SelectObject (hdc, GetStockObject (NULL_BRUSH)) ;
               SelectObject (hdc, CreatePen (PS_DASH, 0, 0)) ;
               Rectangle (hdc, rect.left, rect.top, rect.right, rect.bottom) ;
               DeleteObject (SelectObject (hdc, GetStockObject (BLACK_PEN))) ;
          }

          EndPaint (hwnd, &ps) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}