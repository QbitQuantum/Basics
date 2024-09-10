LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     static HMENU       hMenu ;
     static PAINTSTRUCT ps;
     static int         cxClient, cyClient;
     static int         first;
     static RECT        rect;

     switch (iMsg)
          {
          case WM_CREATE:

               // Initialize program vars
               sys_error.hwnd = (int) hwnd;
               graphics.logicalunit = (int) hwnd;
               strcpy (sys_error.sys_szClientClass, szAppName);
               strcpy (graphics.device, "sys-scn");
               strcpy (sys_error.program_type, "sys");
               sys_error.next_graph = 0; // draw first picture
               first = TRUE;

               return 0;

          case WM_SIZE:

               // Resize screen
               cxClient = LOWORD (lParam);
               cyClient = HIWORD (lParam);
               if (!first) {
                  sys_error.next_graph = 1; // On resize - we want to redraw current picture
               }

               return 0;


          case WM_COMMAND :
               hMenu = GetMenu (hwnd) ;

               switch (LOWORD (wParam))
                    {
                    case IDM_NEW :

                         // Draw next picture
                         sys_error.next_graph = 1;
                         SendMessage (hwnd, WM_PAINT, 0, 0L);
                         return 0 ;

                    case IDM_REDRAW :

                         // Re-Draw current
                         sys_error.next_graph = 2;
                         SendMessage (hwnd, WM_PAINT, 0, 0L);
                         return 0 ;

                    case IDM_GO :

                         // GO
                         sys_error.next_graph = 3;
                         SendMessage (hwnd, WM_PAINT, 0, 0L);
                         return 0 ;

                    case IDM_PRINT:

                         // Print request
                         sys_error.next_graph = 4;
                         SendMessage (hwnd, WM_PAINT, 0, 0L);
                         return 0;

                    case IDM_OPT1:

                         // Option 1
                         sys_error.next_graph = 5;
                         SendMessage (hwnd, WM_PAINT, 0, 0L);
                         return 0;

                    case IDM_OPT2:

                         // Option 2
                         sys_error.next_graph = 6;
                         SendMessage (hwnd, WM_PAINT, 0, 0L);
                         return 0;

                    case IDM_EXIT :
                         SendMessage (hwnd, WM_CLOSE, 0, 0L) ;
                         return 0 ;


                    case IDM_HELP :
                         MessageBox (hwnd, "Help not yet implemented!",
                                     szAppName, MB_ICONEXCLAMATION | MB_OK) ;
                         return 0 ;

                    case IDM_ABOUT :
                         MessageBox (hwnd, "Windows Graphic Driver Version 1.00.",
                                     szAppName, MB_ICONINFORMATION | MB_OK) ;
                         return 0 ;
                    }
               break ;

     case WM_PAINT:
      if (sys_error.next_graph != 4) InvalidateRect (hwnd, NULL, TRUE);

      hdc = BeginPaint (hwnd, &ps);
                graphics.hdc = hdc;

      SetGraphicsMode (graphics.hdc, GM_ADVANCED);
      ModifyWorldTransform (graphics.hdc, NULL, MWT_IDENTITY);

      SetRect (&rect, 0, 0, cxClient, cyClient);

      fordrive ();

      if (first) {
         first = FALSE;
      }
      EndPaint (hwnd, &ps);

      return 0;

          case WM_DESTROY :
               PostQuitMessage (0) ;
               return 0 ;
          }
     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
     }