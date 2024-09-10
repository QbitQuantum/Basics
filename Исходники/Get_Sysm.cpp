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
                           RECT  rect;
                           int   i;

                           // Figure out the position and size of the first
                           // block in the pattern.
                           //..............................................
                           rect.top     = GetSystemMetrics( SM_CYSIZEFRAME );
                           rect.left    = GetSystemMetrics( SM_CXSIZEFRAME );
                           rect.left   += GetSystemMetrics( SM_CXSMICON )+100;
                           rect.bottom  = rect.top + 
                                          GetSystemMetrics( SM_CYCAPTION )-1;
                           rect.right   = rect.left+5;

                           hDC = GetWindowDC( hWnd );

                           // Paint 10 blocks in the caption of the window.
                           //..............................................
                           for ( i = 0; i < 10; i++ )
                           {
                              FillRect( hDC, &rect, 
                                        GetStockObject( WHITE_BRUSH ) );
                              rect.left  += 10;
                              rect.right += 10;
                           }
                           
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