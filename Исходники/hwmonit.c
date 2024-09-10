/*
 * PaintMonitor - redraw the monitor window
 */
static void PaintMonitor( HWND hwnd, HDC dc, LocalMonInfo *info ) {

    RECT        area;
    WORD        i;
    char        buf[80];
    WORD        xpos, ypos;
    HBRUSH      white;

    SaveDC( dc );
    GetClientRect( hwnd, &area );
    white = GetStockObject( WHITE_BRUSH );
    FillRect( dc, &area, white );
    SetMapMode( dc, MM_ANISOTROPIC );
    SetWindowOrg( dc, 0, 0 );
    SetWindowExt( dc, MONITOR_WIDTH, MONITOR_HITE );
    SetViewportOrg( dc, 0, 0 );
    SetViewportExt( dc, area.right, area.bottom );

    area.top = BAR_HITE;
    area.bottom = 2 * BAR_HITE;
    area.left = BAR_XPOS;
    for( i=0; i < SIZE_CNT; i++ ) {
        if( info->sizes[i] == 0 ) continue;
        area.right = area.left + SECTION_WIDTH( info->sizes[i],
                                                info->total_size );
        FillRect( dc, &area, Brushes.brush[i] );

        xpos = ( area.left + area.right ) / 2;
        MoveTo( dc, xpos, area.bottom );
        ypos = area.bottom + TEXT_SPACE + ( SIZE_CNT - i ) * TEXT_HITE;
        LineTo( dc, xpos, ypos );
        xpos += TICK_LENGTH;
        LineTo( dc, xpos, ypos );
        if( i == STACK_SIZE ) {
            sprintf( buf, MonitorLabels[i], info->sizes[i],
                     info->stack_used );
        } else {
            sprintf( buf, MonitorLabels[i], info->sizes[i] );
        }
        TextOut( dc, xpos, ypos, buf, strlen( buf ) );
        area.left = area.right;
    }

    area.left = BAR_XPOS;
    area.right = area.left + BAR_LENGTH;
    MoveTo( dc, area.left, area.top );
    LineTo( dc, area.right, area.top );
    LineTo( dc, area.right, area.bottom );
    LineTo( dc, area.left, area.bottom );
    LineTo( dc, area.left, area.top );

    TextOut( dc, 0, BAR_HITE, "0", 1 );
    sprintf( buf, "%u", info->total_size );
    TextOut( dc, area.right + area.left, BAR_HITE, buf, strlen( buf ) );
    RestoreDC( dc, -1 );
}