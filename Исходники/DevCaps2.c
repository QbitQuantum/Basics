LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static TCHAR            szDevice[32], szWindowText[64] ;
     static int              cxChar, cyChar, nCurrentDevice = IDM_SCREEN,
                                             nCurrentInfo   = IDM_BASIC ;
     static DWORD            dwNeeded, dwReturned ;
     static PRINTER_INFO_4 * pinfo4 ;
     static PRINTER_INFO_5 * pinfo5 ;
     DWORD                   i ;
     HDC                     hdc, hdcInfo ;
     HMENU                   hMenu ;
     HANDLE                  hPrint ;
     PAINTSTRUCT             ps ;
     TEXTMETRIC              tm ;
     
     switch (message)
     {
     case WM_CREATE :
          hdc = GetDC (hwnd) ;
          SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;
          GetTextMetrics (hdc, &tm) ;
          cxChar = tm.tmAveCharWidth ;
          cyChar = tm.tmHeight + tm.tmExternalLeading ;
          ReleaseDC (hwnd, hdc) ;
                                           // fall through
     case WM_SETTINGCHANGE:
          hMenu = GetSubMenu (GetMenu (hwnd), 0) ;
          
          while (GetMenuItemCount (hMenu) > 1)
               DeleteMenu (hMenu, 1, MF_BYPOSITION) ;

               // Get a list of all local and remote printers
               // 
               // First, find out how large an array we need; this
               //   call will fail, leaving the required size in dwNeeded
               //
               // Next, allocate space for the info array and fill it
               // 
               // Put the printer names on the menu.

          if (GetVersion () & 0x80000000)         // Windows 98
          {
               EnumPrinters (PRINTER_ENUM_LOCAL, NULL, 5, NULL, 
                             0, &dwNeeded, &dwReturned) ;

               pinfo5 = malloc (dwNeeded) ;

               EnumPrinters (PRINTER_ENUM_LOCAL, NULL, 5, (PBYTE) pinfo5,
                             dwNeeded, &dwNeeded, &dwReturned) ;

               for (i = 0 ; i < dwReturned ; i++)
               {
                    AppendMenu (hMenu, (i+1) % 16 ? 0 : MF_MENUBARBREAK, i + 1, 
                                pinfo5[i].pPrinterName) ;
               }
               free (pinfo5) ;
          }
          else                                    // Windows NT
          {
               EnumPrinters (PRINTER_ENUM_LOCAL, NULL, 4, NULL, 
                             0, &dwNeeded, &dwReturned) ;

               pinfo4 = malloc (dwNeeded) ;

               EnumPrinters (PRINTER_ENUM_LOCAL, NULL, 4, (PBYTE) pinfo4,
                             dwNeeded, &dwNeeded, &dwReturned) ;

               for (i = 0 ; i < dwReturned ; i++)
               {
                    AppendMenu (hMenu, (i+1) % 16 ? 0 : MF_MENUBARBREAK, i + 1, 
                                pinfo4[i].pPrinterName) ;
               }
               free (pinfo4) ;
          }
          
          AppendMenu (hMenu, MF_SEPARATOR, 0, NULL) ;
          AppendMenu (hMenu, 0, IDM_DEVMODE, TEXT ("Properties")) ;
          
          wParam = IDM_SCREEN ;
                                             // fall through
     case WM_COMMAND :
          hMenu = GetMenu (hwnd) ;
          
          if (LOWORD (wParam) == IDM_SCREEN ||         // IDM_SCREEN & Printers
              LOWORD (wParam) < IDM_DEVMODE)       
          {
               CheckMenuItem (hMenu, nCurrentDevice, MF_UNCHECKED) ;
               nCurrentDevice = LOWORD (wParam) ;
               CheckMenuItem (hMenu, nCurrentDevice, MF_CHECKED) ;
          }
          else if (LOWORD (wParam) == IDM_DEVMODE)     // Properties selection
          {
               GetMenuString (hMenu, nCurrentDevice, szDevice,
                              sizeof (szDevice) / sizeof (TCHAR), MF_BYCOMMAND);
               
               if (OpenPrinter (szDevice, &hPrint, NULL))
               {
                    PrinterProperties (hwnd, hPrint) ;
                    ClosePrinter (hPrint) ;
               }
          }
          else                               // info menu items
          {
               CheckMenuItem (hMenu, nCurrentInfo, MF_UNCHECKED) ;
               nCurrentInfo = LOWORD (wParam) ;
               CheckMenuItem (hMenu, nCurrentInfo, MF_CHECKED) ;
          }
          InvalidateRect (hwnd, NULL, TRUE) ;
          return 0 ;
          
     case WM_INITMENUPOPUP :
          if (lParam == 0)
               EnableMenuItem (GetMenu (hwnd), IDM_DEVMODE,
                    nCurrentDevice == IDM_SCREEN ? MF_GRAYED : MF_ENABLED) ;
          return 0 ;
          
     case WM_PAINT :
          lstrcpy (szWindowText, TEXT ("Device Capabilities: ")) ;
          
          if (nCurrentDevice == IDM_SCREEN)
          {
               lstrcpy (szDevice, TEXT ("DISPLAY")) ;
               hdcInfo = CreateIC (szDevice, NULL, NULL, NULL) ;
          }
          else
          {
               hMenu = GetMenu (hwnd) ;
               GetMenuString (hMenu, nCurrentDevice, szDevice,
                              sizeof (szDevice), MF_BYCOMMAND) ;
               hdcInfo = CreateIC (NULL, szDevice, NULL, NULL) ;
          }
          
          lstrcat (szWindowText, szDevice) ;
          SetWindowText (hwnd, szWindowText) ;
          
          hdc = BeginPaint (hwnd, &ps) ;
          SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;
          
          if (hdcInfo)
          {
               switch (nCurrentInfo)
               {
               case IDM_BASIC :
                    DoBasicInfo (hdc, hdcInfo, cxChar, cyChar) ;
                    break ;
                    
               case IDM_OTHER :
                    DoOtherInfo (hdc, hdcInfo, cxChar, cyChar) ;
                    break ;
                    
               case IDM_CURVE :
               case IDM_LINE :
               case IDM_POLY :
               case IDM_TEXT :
                    DoBitCodedCaps (hdc, hdcInfo, cxChar, cyChar,
                                    nCurrentInfo - IDM_CURVE) ;
                    break ;
               }
               DeleteDC (hdcInfo) ;
          }
          
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}