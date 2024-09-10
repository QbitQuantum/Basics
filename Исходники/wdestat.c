Bool WdeCreateStatusLine( HWND main, HINSTANCE inst )
{
    RECT                rect;
    LOGFONT             lf;
    TEXTMETRIC          tm;
    HFONT               old_font;
    HDC                 dc;
    status_block_desc   sbd;
    char                *status_font;
    char                *cp;
    int                 point_size;
    Bool                use_default;

    memset( &lf, 0, sizeof( LOGFONT ) );
    dc = GetDC( main );
    lf.lfWeight = FW_BOLD;
    use_default = TRUE;

    status_font = WdeAllocRCString( WDE_STATUSFONT );
    if( status_font != NULL ) {
        cp = (char *)_mbschr( (unsigned char *)status_font, '.' );
        if( cp != NULL ) {
            *cp = '\0';
            strcpy( lf.lfFaceName, status_font );
            cp++;
            point_size = atoi( cp );
            use_default = FALSE;
        }
        WdeFreeRCString( status_font );
    }

    if( use_default ) {
        strcpy( lf.lfFaceName, STATUS_FONTNAME );
        point_size = STATUS_POINTSIZE;
    }

    lf.lfHeight = -MulDiv( point_size, GetDeviceCaps( dc, LOGPIXELSY ), 72 );
    WdeStatusFont = CreateFontIndirect( &lf );
    old_font = SelectObject( dc, WdeStatusFont );
    GetTextMetrics( dc, &tm );
    SelectObject( dc, old_font );
    ReleaseDC( main, dc );

    GetClientRect( main, &rect );

    WdeStatusDepth = tm.tmHeight + STATUS_LINE_PAD + VERT_BORDER * 2;
    rect.top = rect.bottom - WdeStatusDepth;

    if( !StatusWndInit( inst, WdeStatusHookProc, 0, (HCURSOR)NULL ) ) {
        return( FALSE );
    }
    WdeStatusBar = StatusWndStart();

    sbd.separator_width = STATUS_LINE_PAD;
    sbd.width = STATUS1_WIDTH;
    sbd.width_is_percent = FALSE;
    sbd.width_is_pixels = TRUE;

    StatusWndSetSeparators( WdeStatusBar, 1, &sbd );

    WdeStatusWindow = StatusWndCreate( WdeStatusBar, main, &rect, inst, NULL );

    if( WdeStatusWindow == NULL ) {
        WdeDisplayErrorMsg( WDE_NOCREATESTATUS );
        return( FALSE );
    }

    /* set the text in the status window */
    WdeSetStatusReadyText();

    GetWindowRect( WdeStatusWindow, &rect );
    WdeStatusDepth = rect.bottom - rect.top;

    return( TRUE );
}