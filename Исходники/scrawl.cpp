//-----------------------------------------------------------------------------
// Name: OnRightButtonUp()
// Desc: Pop up a context menu.
//-----------------------------------------------------------------------------
VOID OnRightButtonUp( HWND hWnd )
{
    // Place a popup menu where the mouse curent is
    POINT pt;
    pt.x = g_x;
    pt.y = g_y;
    ClientToScreen( hWnd, &pt );
    HMENU hMenuPopup = GetSystemMenu( hWnd, FALSE );

    // Hide the cursor while moving it so you don't get annoying flicker.
    ShowCursor( FALSE );
    InvalidateCursorRect( hWnd );

    // Unacquire the devices so the user can interact with the menu.
    g_bActive = FALSE;
    SetAcquire();

    // Put the Windows cursor at the same location as our virtual cursor.
    SetCursorPos( pt.x, pt.y );

    // Show the cursor now that it is moved 
    ShowCursor( TRUE );
    InvalidateCursorRect( hWnd );

    // Track the popup menu and return the menu item selected
    UINT iMenuID = TrackPopupMenuEx( hMenuPopup, TPM_RIGHTBUTTON|TPM_RETURNCMD,
                                     pt.x, pt.y, hWnd, 0 );

    if( 0 != iMenuID ) // If a menu item was selected
        PostMessage( hWnd, WM_SYSCOMMAND, iMenuID, 0L );
}