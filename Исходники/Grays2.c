LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HPALETTE hPalette ;
     static int      cxClient, cyClient ;
     HBRUSH          hBrush ;
     HDC             hdc ;
     int             i ;
     LOGPALETTE    * plp ;
     PAINTSTRUCT     ps ;
     RECT            rect ;
     
     switch (message)
     {
     case WM_CREATE:
               // Set up a LOGPALETTE structure and create a palette

          plp = malloc (sizeof (LOGPALETTE) + 64 * sizeof (PALETTEENTRY)) ;

          plp->palVersion    = 0x0300 ;
          plp->palNumEntries = 65 ;

          for (i = 0 ; i < 65 ; i++)
          {
               plp->palPalEntry[i].peRed   = (BYTE) min (255, 4 * i) ;
               plp->palPalEntry[i].peGreen = (BYTE) min (255, 4 * i) ;
               plp->palPalEntry[i].peBlue  = (BYTE) min (255, 4 * i) ;
               plp->palPalEntry[i].peFlags = 0 ;
          }
          hPalette = CreatePalette (plp) ;
          free (plp) ;
          return 0 ;

     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;
          
     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

               // Select and realize the palette in the device context

          SelectPalette (hdc, hPalette, FALSE) ;
          RealizePalette (hdc) ;

               // Draw the fountain of grays

          for (i = 0 ; i < 65 ; i++)
          {
               rect.left   = i * cxClient / 64 ;
               rect.top    = 0 ;
               rect.right  = (i + 1) * cxClient / 64 ;
               rect.bottom = cyClient ;

               hBrush = CreateSolidBrush (PALETTERGB (min (255, 4 * i), 
                                                      min (255, 4 * i), 
                                                      min (255, 4 * i))) ;
               FillRect (hdc, &rect, hBrush) ;
               DeleteObject (hBrush) ;
          }
          EndPaint (hwnd, &ps) ;
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
          DeleteObject (hPalette) ;
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}