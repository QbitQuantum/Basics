long FAR PASCAL _export ChildWndProc(HWND hwnd, 
                                     UINT message, 
                                     UINT wParam,
                                     LONG lParam)
   {
   HDC         hdc;
   PAINTSTRUCT ps;                                     
   RECT        rect;

   switch (message)
      {
      case WM_CREATE :
         {
         SetWindowWord(hwnd, 0,0);
         return 0;
         }
      case WM_LBUTTONDOWN :
         {
         SetWindowWord(hwnd, 0, 1 ^ GetWindowWord(hwnd,0));
         InvalidateRect(hwnd,NULL,FALSE);
         return 0;
         }  
   
      case WM_PAINT :
         {
         TRACE_STR("WM_PAINT..");
         //get the device context handle for use in painting the sucker...
         hdc = BeginPaint(hwnd, &ps);

         GetClientRect(hwnd, &rect);
         Rectangle(hdc,
                   0,
                   0,
                   rect.right,
                   rect.bottom);
         // draw an X if true!          
         if (GetWindowWord(hwnd,0))
            {
            MoveTo(hdc,0         ,0          );
            LineTo(hdc,rect.right,rect.bottom);
            MoveTo(hdc,0         ,rect.bottom);
            LineTo(hdc,rect.right,0          );
            }
         
         EndPaint (hwnd, &ps);
         TRACE_STR("EXIT WM_PAINT...");
         TRACE_STR("EXIT WndProc");
         return 0;      
         }
      }   // switch
   // *********************extremely important!!! ******************      
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   return DefWindowProc(hwnd,message,wParam,lParam);                
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   // *********************extremely important!!! ******************      
   }                                                                