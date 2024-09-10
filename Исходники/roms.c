static void
roms_init( HWND hwndDlg, LPARAM lParam )
{
  size_t i;
  struct callback_info *info;

  info = ( struct callback_info * ) lParam;
  
  for( i = 0; i < info->n; i++ ) add_rom( hwndDlg, info->start, i );

  /* Move the OK and Cancel buttons */
  RECT rect;

  rect.left = 25; rect.top = ( info->n * 30 ) + 5;
  rect.right = 25 + 50; rect.bottom = ( info->n * 30 ) + 5 + 14;
  MapDialogRect( hwndDlg, &rect );
  MoveWindow( GetDlgItem( hwndDlg, IDOK ),
              rect.left, rect.top,
              rect.right - rect.left, rect.bottom - rect.top,
              FALSE );

  rect.left = 85; rect.top = ( info->n * 30 ) + 5;
  rect.right = 85 + 50; rect.bottom = ( info->n * 30 ) + 5 + 14;
  MapDialogRect( hwndDlg, &rect );
  MoveWindow( GetDlgItem( hwndDlg, IDCANCEL ),
              rect.left, rect.top,
              rect.right - rect.left, rect.bottom - rect.top,
              FALSE );
              
  /* resize the dialog as needed */
  RECT window_rect, client_rect;
  
  GetWindowRect( hwndDlg, &window_rect );
  GetClientRect( hwndDlg, &client_rect );

  rect.left = 0; rect.top = 0;
  rect.right = 163; rect.bottom = ( info->n * 30 ) + 24;
  MapDialogRect( hwndDlg, &rect );
  
  /* rect now contains the size of the client area in pixels,
     now add window's absolute position on the screen */
  rect.left += window_rect.left;
  rect.top += window_rect.top;
  
  /* now just add the difference between client area and window area */
  rect.right += ( window_rect.right - window_rect.left )
              - ( client_rect.right - client_rect.left );
  rect.bottom += ( window_rect.bottom - window_rect.top )
               - ( client_rect.bottom - client_rect.top );
  
  /* MoveWindow doesn't really take rect, instead it's X, Y, sizeX and sizeY */
  MoveWindow( hwndDlg, rect.left, rect.top, rect.right, rect.bottom, FALSE );
}