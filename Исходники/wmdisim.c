/*
 * newChildPositions - handle re-location of a child window
 */
static void newChildPositions( void )
{
    mdi_data    *curr;
    RECT        r;
    RECT        orig;

    if( childrenMaximized ) {
        return;
    }

    curr = mdiHead;
    memset( &minChildRect, 0, sizeof( RECT ) );
    while( curr != NULL ) {
        _wpi_getwindowrect( curr->hwnd, &r );
        orig = minChildRect;
        UnionRect( &minChildRect, &orig, &r );
        haveMinChildRect = TRUE;
        curr = curr->next;
    }
    tryContainerScrollBars();

} /* newChildPositions */