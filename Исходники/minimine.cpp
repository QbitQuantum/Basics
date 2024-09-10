/* Builds the individual elements of the GUI.
 ******************************************************************************/
void BuildGUI()
{
  int i, j;

  // minimize button
  hMinButton = CreateWindow( "BUTTON", "M", WS_VISIBLE | WS_CHILD |
                               BS_OWNERDRAW, 227, 3, 7, 7, hWnd,
                               ( HMENU )IDB_MIN, hInstance, NULL );

  // close button
  hCloseButton = CreateWindow( "BUTTON", "C", WS_VISIBLE | WS_CHILD |
                                 BS_OWNERDRAW, 235, 3, 7, 7, hWnd,
                                 ( HMENU )IDB_CLOSE, hInstance, NULL );

  // new game button
  hNewButton = CreateWindow( "BUTTON", "N", WS_VISIBLE | WS_CHILD |
                               BS_OWNERDRAW, 131, 3, 7, 7, hWnd,
                               ( HMENU )IDB_NEW, hInstance, NULL );

  // number of mines left display
  for( i = 0; i < 2; i++ )
    hScore[ i ] = CreateWindow( "STATIC", "0", WS_VISIBLE | WS_CHILD |
                                SS_BITMAP, 117 - ( 5 * i ), 3, 7, 7, hWnd,
                                ( HMENU )( IDS_SCORE + i ), hInstance, NULL );

  // timer display
  for( i = 0; i < 3; i++ )
    hTime[ i ] = CreateWindow( "STATIC", "0", WS_VISIBLE | WS_CHILD |
                                SS_BITMAP, 155 - ( 5 * i ), 3, 7, 7, hWnd,
                                ( HMENU )( IDS_TIME + i ), hInstance, NULL );

  // subclassed minefield position buttons
  for( i = 0; i < COLS; i++ )
    for( j = 0; j < ROWS; j++ )
    {
      hField[ i ][ j ] = CreateWindow( "BUTTON", "x", WS_VISIBLE |
                                       WS_CHILD | BS_OWNERDRAW,
                                       ( 3 + 8 * i ), ( 14 + 8 * j ), 7, 7,
                                       hWnd,
                                       ( HMENU )( IDB_MINE + i + COLS * j ),
                                       hInstance, NULL );
      mainProc = ( WNDPROC )SetWindowLongPtr( hField[ i ][ j ], GWLP_WNDPROC,
                   PtrToLong( BtnSubclassProc ) );
    }

  SkinBmpa = LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_WINDOW ) );
  ButtonBmpa = LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_ELEMENTS ) );
}