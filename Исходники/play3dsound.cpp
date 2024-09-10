//-----------------------------------------------------------------------------
// Name: UpdateGrid()
// Desc: Draws a red dot in the dialog's grid bitmap at the x,y coordinate.
//-----------------------------------------------------------------------------
VOID UpdateGrid( HWND hDlg, FLOAT x, FLOAT y )
{
    static LONG s_lPixel[5] = { CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID,CLR_INVALID };
    static LONG s_lX = 0;
    static LONG s_lY = 0;

    HWND hWndGrid = GetDlgItem( hDlg, IDC_RENDER_WINDOW );
    HDC  hDC      = GetDC( hWndGrid );
    RECT rc;

    // Don't update the grid if a WM_PAINT will be called soon
    BOOL bUpdateInProgress = GetUpdateRect(hDlg,NULL,FALSE);
    if( bUpdateInProgress )
        return;

    if( s_lPixel[0] != CLR_INVALID ) 
    {
        // Replace pixels from that were overdrawn last time
        SetPixel( hDC, s_lX-1, s_lY+0, s_lPixel[0] );
        SetPixel( hDC, s_lX+0, s_lY-1, s_lPixel[1] );
        SetPixel( hDC, s_lX+0, s_lY+0, s_lPixel[2] );
        SetPixel( hDC, s_lX+0, s_lY+1, s_lPixel[3] );
        SetPixel( hDC, s_lX+1, s_lY+0, s_lPixel[4] );   
    }

    // Convert the world space x,y coordinates to pixel coordinates
    GetClientRect( hWndGrid, &rc );
    s_lX = (LONG)( ( x/ORBIT_MAX_RADIUS + 1 ) * ( rc.left + rc.right ) / 2 );
    s_lY = (LONG)( (-y/ORBIT_MAX_RADIUS + 1 ) * ( rc.top + rc.bottom ) / 2 );

    // Save the pixels before drawing the cross hair
    s_lPixel[0] = GetPixel( hDC, s_lX-1, s_lY+0 );
    s_lPixel[1] = GetPixel( hDC, s_lX+0, s_lY-1 );
    s_lPixel[2] = GetPixel( hDC, s_lX+0, s_lY+0 );
    s_lPixel[3] = GetPixel( hDC, s_lX+0, s_lY+1 );
    s_lPixel[4] = GetPixel( hDC, s_lX+1, s_lY+0 );

    // Draw a crosshair object in red pixels
    SetPixel( hDC, s_lX-1, s_lY+0, 0x000000ff );
    SetPixel( hDC, s_lX+0, s_lY-1, 0x000000ff );
    SetPixel( hDC, s_lX+0, s_lY+0, 0x000000ff );
    SetPixel( hDC, s_lX+0, s_lY+1, 0x000000ff );
    SetPixel( hDC, s_lX+1, s_lY+0, 0x000000ff );

    ReleaseDC( hWndGrid, hDC );
}