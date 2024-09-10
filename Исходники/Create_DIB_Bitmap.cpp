LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch( uMsg )
   {
      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        {
                           BITMAPINFOHEADER  bi;
                           BITMAPINFOHEADER* lpbi;
                           HBITMAP           hBitmap;
                           HDC               hDC, hMemDC;
                           HANDLE            hDIB;

                           // Initialize the BITMAPINFOHEADER structure.
                           //...........................................
                           bi.biSize     = sizeof( BITMAPINFOHEADER );
                           bi.biWidth    = 50;
                           bi.biHeight   = 50;
                           bi.biPlanes   = 1;
                           bi.biBitCount = 4;
                           bi.biCompression   = BI_RGB;
                           bi.biSizeImage     = 0;
                           bi.biXPelsPerMeter = 0;
                           bi.biYPelsPerMeter = 0;
                           bi.biClrUsed       = 0;
                           bi.biClrImportant  = 0;

                           hDC = GetDC( hWnd );

                           // Create DIB.
                           //............
                           hBitmap = CreateDIBitmap( hDC, &bi, 0L, NULL, 
                                                     NULL, 0 );

                           // Allocate memory for BITMAPINFO structure.
                           //..........................................
                           hDIB    = GlobalAlloc( GHND, 
                                                  sizeof( BITMAPINFOHEADER )+
                                                  16 * sizeof( RGBQUAD ) );

                           lpbi = (BITMAPINFOHEADER*)GlobalLock( hDIB );

                           // Copy bi to top of BITMAPINFO structure.
                           //........................................
                           *lpbi = bi;

                           // Use GetDIBits() to init bi struct data.
                           //........................................
                           GetDIBits( hDC, hBitmap, 0, 50, NULL, 
                                      (LPBITMAPINFO)lpbi, DIB_RGB_COLORS );
                           GlobalUnlock( hDIB );

                           // Create a memory device context 
                           // and select the DIB into it.
                           //...............................
                           hMemDC = CreateCompatibleDC( hDC );
                           SelectObject( hMemDC, hBitmap );

                           // Paint on memory device context.
                           //................................
                           SelectObject( hMemDC, GetStockObject(BLACK_BRUSH));
                           Rectangle( hMemDC, 0, 0, 50, 50 );

                           SelectObject( hMemDC, GetStockObject(WHITE_BRUSH));
                           Ellipse( hMemDC, 0, 0, 50, 50 );
                           Ellipse( hMemDC, 10, 0, 40, 50 );
                           Ellipse( hMemDC, 20, 0, 30, 50 );

                           // Paint the bitmap on the display.
                           //.................................
                           BitBlt( hDC, 0, 0, 50, 50,
                                   hMemDC, 0, 0, SRCCOPY );

                           DeleteDC( hMemDC );
                           GlobalFree( hDIB );
                           ReleaseDC( hWnd, hDC );
                        }
                        break;

                 case IDM_ABOUT :
                        DialogBox( hInst, "AboutBox", hWnd, (DLGPROC)About );
                        break;

                 case IDM_EXIT :
                        DestroyWindow( hWnd );
                        break;
              }
              break;
      
      case WM_DESTROY :
              PostQuitMessage(0);
              break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}