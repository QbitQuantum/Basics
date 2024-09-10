long FAR PASCAL _export WndProc (HWND hwnd,
                                 UINT message,
                                 UINT wParam,
                                 LONG lParam)
   {
   static char    szTop[]     = "message            wParam    lParam",
                  szUnd[]     = "_______            ______    ______",
                  szFormat[]  = "%-16s%6X%8X-%04X",
                  szBuffer[50];
   static HWND    hwndButton[BUTTON_CNT];
   static RECT    rect;
   static int     cxChar, 
                  cyChar;
   HDC            hdc;
   PAINTSTRUCT    ps;
   int            i;
   static int     checkbox_state=0;                
   static int     three_state_state = 0;
   TEXTMETRIC     tm;

                  
//   TRACE_STR("ENTER WndProc");
   switch(message)
      {
//      case WM_CTLCOLOR :
//         {
//
//
//         
//         return 0;
//         }
      case WM_CREATE:
         {
         hdc = GetDC(hwnd);
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
         GetTextMetrics(hdc,&tm);
         cxChar = tm.tmAveCharWidth;
         cyChar = tm.tmHeight + tm.tmExternalLeading;
         ReleaseDC(hwnd,hdc);

         for(i = PUSHBUTTON_ID ; i <= OWNERDRAW_ID; i++)
            {
            hwndButton [i] = 
               // create some buttons...
               CreateWindow("button",
                            button[i].text,
                            WS_CHILD | WS_VISIBLE | button[i].style,
                            cxChar,
                            cyChar * (1 + (2 * i)),
                            20 * cxChar, 
                            7 * cyChar / 4,
                            hwnd,
                            i,
                            // since lParam is a Long pointer to the creation 
                            // structure, get the hInstance out so that this
                            // window properly points to its Parent...
                            ((LPCREATESTRUCT) lParam) -> hInstance,
                            NULL);
            }
         return 0;   
         }
      case WM_SIZE :
         {
         rect.left = 24 * cxChar;
         rect.top = 2 * cyChar;
         rect.right = LOWORD(lParam);
         rect.bottom = HIWORD(lParam);
         return 0;
         }
      case WM_PAINT :
         {
         InvalidateRect(hwnd, &rect, TRUE);
         
         hdc = BeginPaint(hwnd,&ps);
         
         // Default to windows stuff.
         SetBkColor(hdc,GetSysColor(COLOR_WINDOW));
         SetTextColor(hdc,GetSysColor(COLOR_WINDOWTEXT));
         
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
         SetBkMode(hdc,TRANSPARENT);

         TextOut( hdc, 
                  24*cxChar,
                  cyChar,
                  szTop,
                  sizeof szTop - 1);
         TextOut( hdc,
                  24*cxChar,
                  cyChar,
                  szUnd,
                  sizeof szUnd - 1);
                           
         EndPaint(hwnd,&ps);
         return 0;
         }
      case WM_COMMAND :
      case WM_DRAWITEM :
         {
         ScrollWindow(hwnd,
                      0,
                      -cyChar,
                      &rect,
                      &rect);
         hdc = GetDC(hwnd);
         
         SetBkColor(hdc,GetSysColor(COLOR_WINDOW));
         SetTextColor(hdc,GetSysColor(COLOR_WINDOWTEXT));
         
         SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
         TextOut(hdc, 
                 24*cxChar,
                 cyChar * (rect.bottom/cyChar-1),
                 szBuffer,
                 wsprintf(szBuffer,
                          szFormat,
                          (LPSTR) (message==WM_COMMAND ? "WM_COMMAND" : "WM_DRAWITEM"),
                          wParam,            //Child Window ID
                          HIWORD(lParam),    // Child Window Handle
                          LOWORD(lParam)));  // Notification Code
         // Extreee stuff to do...                 
         if (wParam == PUSHBUTTON_ID)
            {
            // Show DEFPUSHBUTTON as pressed
            SendMessage(hwndButton[DEFPUSHBUTTON_ID],BM_SETSTATE,1,0L);
            // Change text of button
            SetWindowText(hwndButton[DEFPUSHBUTTON_ID],"F**K YOU");
            // Show it as disabled
            EnableWindow(hwndButton[DEFPUSHBUTTON_ID],FALSE);
            }
         if (wParam == CHECKBOX_ID)
            {
            // change checkbox state...
            checkbox_state ^= 1;
            SendMessage(hwndButton[CHECKBOX_ID],BM_SETCHECK,checkbox_state,0L);
            
            // do our goofy fun-ness..
            // re-enable button
            EnableWindow(hwndButton[DEFPUSHBUTTON_ID],TRUE);
            // Show DEFPUSHBUTTON as not pressed
            SendMessage(hwndButton[DEFPUSHBUTTON_ID],BM_SETSTATE,0,0L);
            // set text to default text...
            SetWindowText(hwndButton[DEFPUSHBUTTON_ID],button[DEFPUSHBUTTON_ID].text);

            }                                                      
         if (wParam == RADIOBUTTON_ID)
            {
            // change checkbox state...
            
            SendMessage(hwndButton[RADIOBUTTON_ID],BM_SETCHECK,1,0L);
            
            }
         if (wParam == BUTTON_3STATE_ID)
            {
            // change checkbox state...
            three_state_state = (++three_state_state) % 3;
            
            SendMessage(hwndButton[BUTTON_3STATE_ID],BM_SETCHECK,three_state_state,0L);
            
            }
         ReleaseDC(hwnd,hdc);
         ValidateRect(hwnd,NULL);                

         return 0;
         }
         
      case WM_DESTROY :
         {
         // insert a WM_QUIT in the queue...
         TRACE_STR("WM_DESTROY..");
         PostQuitMessage (0);
         TRACE_STR("EXIT WndProc");
         return 0;            
         }
      }//switch
//   TRACE_STR("EXIT WndProc");
   // *********************extremely important!!! ******************      
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   return DefWindowProc (hwnd, message, wParam, lParam);            
   // **                   extremely important!!!                 **
   // **                   extremely important!!!                 **
   // *********************extremely important!!! ******************      
   } //WndProc