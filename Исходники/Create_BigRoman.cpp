LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch( uMsg )
   {
      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        {
                           HDC   hDC;
                           HFONT hFont;

                           // Create a Times New Roman font.
                           //...............................
                           hFont = CreateFont( 24, 16, 0, 0, FW_NORMAL, 
                                               0, 0, 0, ANSI_CHARSET,
                                               OUT_DEFAULT_PRECIS,
                                               CLIP_DEFAULT_PRECIS,
                                               DEFAULT_QUALITY,
                                               DEFAULT_PITCH | FF_ROMAN,
                                               "Times New Roman" );

                           hDC   = GetDC( hWnd );

                           // Force exact font matching and select
                           // the font into the device context.
                           //.....................................
                           SetMapperFlags( hDC, 1 );
                           SelectObject( hDC, hFont );

                           TextOut( hDC, 10, 10, 
                                    "This is the roman font!", 23 );

                           ReleaseDC( hWnd, hDC );
                           DeleteObject( hFont );
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