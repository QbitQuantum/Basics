/***********************************************************************
 *           ICONTITLE_Paint
 */
static BOOL ICONTITLE_Paint( HWND hwnd, HWND owner, HDC hDC, BOOL bActive )
{
    RECT rect;
    HFONT hPrevFont;
    HBRUSH hBrush;
    COLORREF textColor = 0;

    if( bActive )
    {
	hBrush = GetSysColorBrush(COLOR_ACTIVECAPTION);
	textColor = GetSysColor(COLOR_CAPTIONTEXT);
    }
    else
    {
        if( GetWindowLongPtrA( hwnd, GWL_STYLE ) & WS_CHILD )
	{
	    hBrush = (HBRUSH) GetClassLongPtrW(hwnd, GCLP_HBRBACKGROUND);
	    if( hBrush )
	    {
		INT level;
		LOGBRUSH logBrush;
		GetObjectA( hBrush, sizeof(logBrush), &logBrush );
		level = GetRValue(logBrush.lbColor) +
			   GetGValue(logBrush.lbColor) +
			      GetBValue(logBrush.lbColor);
		if( level < (0x7F * 3) )
		    textColor = RGB( 0xFF, 0xFF, 0xFF );
	    }
	    else
		hBrush = GetStockObject( WHITE_BRUSH );
	}
	else
	{
	    hBrush = GetStockObject( BLACK_BRUSH );
	    textColor = RGB( 0xFF, 0xFF, 0xFF );
	}
    }

    GetClientRect( hwnd, &rect );
    DPtoLP( hDC, (LPPOINT)&rect, 2 );
    FillRect( hDC, &rect, hBrush );

    hPrevFont = SelectObject( hDC, hIconTitleFont );
    if( hPrevFont )
    {
	WCHAR buffer[80];

        INT length = GetWindowTextW( owner, buffer, sizeof(buffer)/sizeof(buffer[0]) );
        SetTextColor( hDC, textColor );
        SetBkMode( hDC, TRANSPARENT );

        DrawTextW( hDC, buffer, length, &rect, DT_CENTER | DT_NOPREFIX |
                   DT_WORDBREAK | ((bMultiLineTitle) ? 0 : DT_SINGLELINE) );

	SelectObject( hDC, hPrevFont );
    }
    return (hPrevFont != 0);
}