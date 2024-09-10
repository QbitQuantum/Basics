LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static int  nDspLines;
static int  nNumItems = 0;
static int  nCurPos   = 0;
static char szBuf[10];

   switch( uMsg )
   {
      case WM_CREATE :
              ShowScrollBar( hWnd, SB_VERT, TRUE );
              break;

         // Every time the window is sized, re-calculate the number of lines
         // the client area can display and set the scroll bar accordingly.
         //................................................................
      case WM_SIZE :
              {
                 RECT rect;
                 GetClientRect( hWnd, &rect );

                 nDspLines = rect.bottom / 20;

                 if ( nDspLines < nNumItems ) 
                 {
                    EnableScrollBar( hWnd, SB_VERT, ESB_ENABLE_BOTH );
                    SetScrollRange( hWnd, SB_VERT, 0, 
                                    nNumItems-nDspLines, FALSE );
                    SetScrollPos( hWnd, SB_VERT, nCurPos, FALSE );
                 }
                 else
                    EnableScrollBar( hWnd, SB_VERT, ESB_DISABLE_BOTH );
              }
              break;

      case WM_PAINT :
              {
                 PAINTSTRUCT ps;
                 int         i,j;
                 int         nNumPaint;

                 nNumPaint = min( nCurPos+nDspLines, nNumItems );

                 BeginPaint( hWnd, &ps );

                 for ( j=0,i=nCurPos; i<nNumPaint; i++,j++ )
                 {
                    itoa( i, szBuf, 10 );
                    TextOut( ps.hdc, 10, j*20, "Line of Text:", 13 );
                    TextOut( ps.hdc, 90, j*20, szBuf, strlen( szBuf ) );
                 }
                  
                 EndPaint( hWnd, &ps );
              }
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        if ( nDspLines == nNumItems ) 
                           EnableScrollBar( hWnd, SB_VERT, ESB_ENABLE_BOTH );

                        nNumItems++;
                        if ( nDspLines < nNumItems )
                           SetScrollRange( hWnd, SB_VERT, 0, 
                                           nNumItems-nDspLines, TRUE );

                        InvalidateRect( hWnd, NULL, FALSE );
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