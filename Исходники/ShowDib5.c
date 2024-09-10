LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BITMAPINFO * pPackedDib ;
     static HPALETTE     hPalette ;
     static int          cxClient, cyClient ;
     static OPENFILENAME ofn ;
     static TCHAR        szFileName [MAX_PATH], szTitleName [MAX_PATH] ;
     static TCHAR        szFilter[] = TEXT ("Bitmap Files (*.BMP)\0*.bmp\0")
                                      TEXT ("All Files (*.*)\0*.*\0\0") ;
     HDC                 hdc ;
     PAINTSTRUCT         ps ;

     switch (message)
     {
     case WM_CREATE:
          ofn.lStructSize       = sizeof (OPENFILENAME) ;
          ofn.hwndOwner         = hwnd ;
          ofn.hInstance         = NULL ;
          ofn.lpstrFilter       = szFilter ;
          ofn.lpstrCustomFilter = NULL ;
          ofn.nMaxCustFilter    = 0 ;
          ofn.nFilterIndex      = 0 ;
          ofn.lpstrFile         = szFileName ;
          ofn.nMaxFile          = MAX_PATH ;
          ofn.lpstrFileTitle    = szTitleName ;
          ofn.nMaxFileTitle     = MAX_PATH ;
          ofn.lpstrInitialDir   = NULL ;
          ofn.lpstrTitle        = NULL ;
          ofn.Flags             = 0 ;
          ofn.nFileOffset       = 0 ;
          ofn.nFileExtension    = 0 ;
          ofn.lpstrDefExt       = TEXT ("bmp") ;
          ofn.lCustData         = 0 ;
          ofn.lpfnHook          = NULL ;
          ofn.lpTemplateName    = NULL ;

               // Create the All-Purpose Palette

          hdc = GetDC (hwnd) ;
          hPalette = CreateHalftonePalette (hdc) ;
          ReleaseDC (hwnd, hdc) ;
          return 0 ;

     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0 ;

     case WM_COMMAND:
          switch (LOWORD (wParam))
          {
          case IDM_FILE_OPEN:

                    // Show the File Open dialog box

               if (!GetOpenFileName (&ofn))
                    return 0 ;
               
                    // If there's an existing packed DIB, free the memory

               if (pPackedDib)
               {
                    free (pPackedDib) ;
                    pPackedDib = NULL ;
               }
               
                    // Load the packed DIB into memory

               SetCursor (LoadCursor (NULL, IDC_WAIT)) ;
               ShowCursor (TRUE) ;

               pPackedDib = PackedDibLoad (szFileName) ;

               ShowCursor (FALSE) ;
               SetCursor (LoadCursor (NULL, IDC_ARROW)) ;

               if (!pPackedDib)
               {
                    MessageBox (hwnd, TEXT ("Cannot load DIB file"), 
                                szAppName, 0) ;
               }
               InvalidateRect (hwnd, NULL, TRUE) ;
               return 0 ;
          }
          break ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          if (pPackedDib)
          {
                    // Set halftone stretch mode

               SetStretchBltMode (hdc, HALFTONE) ;
               SetBrushOrgEx (hdc, 0, 0, NULL) ;

                    // Select and realize halftone palette

               SelectPalette (hdc, hPalette, FALSE) ;
               RealizePalette (hdc) ;

                    // StretchDIBits rather than SetDIBitsToDevice
          
               StretchDIBits (hdc, 
                              0,   
                              0,   
                              PackedDibGetWidth (pPackedDib), 
                              PackedDibGetHeight (pPackedDib),
                              0,                            
                              0,                            
                              PackedDibGetWidth (pPackedDib),
                              PackedDibGetHeight (pPackedDib),  
                              PackedDibGetBitsPtr (pPackedDib), 
                              pPackedDib, 
                              DIB_RGB_COLORS, 
                              SRCCOPY) ;
          }
          EndPaint (hwnd, &ps) ;
          return 0 ;

     case WM_QUERYNEWPALETTE:
          hdc = GetDC (hwnd) ;
          SelectPalette (hdc, hPalette, FALSE) ;
          RealizePalette (hdc) ;
          InvalidateRect (hwnd, NULL, TRUE) ;

          ReleaseDC (hwnd, hdc) ;
          return TRUE ;

     case WM_PALETTECHANGED:
          if ((HWND) wParam != hwnd)

          hdc = GetDC (hwnd) ;
          SelectPalette (hdc, hPalette, FALSE) ;
          RealizePalette (hdc) ;
          UpdateColors (hdc) ;

          ReleaseDC (hwnd, hdc) ;
          break ;
          
     case WM_DESTROY:
          if (pPackedDib)
               free (pPackedDib) ;

          DeleteObject (hPalette) ;

          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}