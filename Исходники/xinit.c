/* 
   XBQuickWindow - Create an X window

   Input parameters:
.  mywindow - A pointer to an XBWindow structure that will be used to hold
              information on the window.  This should be acquired with
	      XBWinCreate.
.  host     - name of the display
.  name     - title (name) of the window
.  x,y      - coordinates of the upper left corner of the window.  If <0,
              use user-positioning (normally, the window manager will
	      ask the user where to put the window)
.  nx,ny    - width and height of the window

   Note:
   This creates a window with various defaults (visual, colormap, etc)

   A small modification to this routine would allow Black and White windows
   to be used on color displays; this would be useful for testing codes.
   */
int XBQuickWindow( XBWindow *mywindow, char *host, char *name, int x, int y, int nx, int ny ){
/* Just to be careful, clear mywindow */
    MEMSET( mywindow, 0, sizeof(XBWindow) );
    return XBiQuickWindow( mywindow, host, name, x, y, nx, ny, 0 );
}