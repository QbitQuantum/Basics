/*
 * EnumTaskWindowsFunc:
 *
 * enumerate all task windows, and then sub-class them to point
 * to SubClassProc
 *
 * NOTE: this has some problems, so instead of subclassing, we call
 * SubClassProc directly from the message loop we go into for the debugee.
 *
 */
static BOOL SubClassWindow( HWND hwnd, BOOL do_children )
{
    FARPROC     fp;
    char        buffer[80];

    if( hwnd == NULL ) {
        return( 0 );
    }
    buffer[0]=0;
    GetClassName( hwnd, buffer, sizeof( buffer ) );
    Out((OUT_SOFT,"--- Subclass (%s), id=%04x",buffer,hwnd));
    if( GetWindowWord( hwnd, GWW_HINSTANCE ) == (WORD)GetModuleHandle( "USER") ) {
        Out((OUT_SOFT,"--- Subclass IGNORED (USER)" ));
        return( 1 );
    }
    if( buffer[0] != '#' ) { // don't subclass predefined windows classes
        fp = (FARPROC)SetWindowLong( hwnd, GWL_WNDPROC, (LONG)DefaultProcInstance );
        SCWindows[ SCCount ].hwnd = hwnd;
        SCWindows[ SCCount ].oldproc = fp;
        SCCount++;
        if( do_children ) EnumChildWindows( hwnd, (WNDENUMPROC)EnumChildProcInstance, 0 );
    }
    return( 1 );

}