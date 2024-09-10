/* 
** Free memory space for the child window's data. 
*/
void __far __pascal FreeChildWndData( HWND hWnd )
{
  HWNDDATA hWndData;

  
  /* get window data handle. */
  hWndData = (HWNDDATA) GetWindowWord( hWnd, 0 );
  
  /* Free memory. */
  GlobalFree( hWndData );
  
  /* Save handle in the window's extrabyte. */
  SetWindowWord( hWnd, 0, 0 );
}