void DisplayCandStrings( 
    HWND hwnd, 
    LPCANDIDATELIST lpCandList )
{

    HDC         hdc;            // Storage for device context handle.
    LPSTR       lpStr;          // Storage for LP to a string.
    DWORD       dwNumPerPage;   // Storage for num per page
    DWORD       dwStartIndex;   // Storage for candidate index
    DWORD       dwEndIndex;     // Storage for candidate index
    RECT        rect;           // Storage for client rect.
    int         y = 0;          // 
    DWORD       dwBackColor;    // Storage for background color value
    DWORD       dwTextColor;

    //
    // Determine how many candidate strings per page.
    //

    dwNumPerPage = ( !lpCandList->dwPageSize ) ?
                     DEFAULT_CAND_NUM_PER_PAGE :
                     lpCandList->dwPageSize;

    //
    // Determine the dwStartIndex from which the candidate string will
    // start displaying.
    //

    dwStartIndex = lpCandList->dwPageStart;

    //
    // Determine the dwEndIndex which indicate the last candidate string
    // will be displayed.
    //

    dwEndIndex = dwStartIndex + dwNumPerPage;

    dwEndIndex = ( dwEndIndex >= lpCandList->dwCount ) ?
                 lpCandList->dwCount : dwEndIndex;
                 
    
    //
    // Dissplay candidate strings.
    // First paint background color.
    //

    hdc = GetDC( hwnd );

    dwBackColor = SetBkColor( hdc, RGB( 0xbf, 0xbf, 0xbf ) );

    GetClientRect( hwnd, &rect );

    ExtTextOut( hdc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, 0 );


    //
    // Set background color of selected candidate string to be blue.
    //

    rect.top = rect.top + 
               ( lpCandList->dwSelection - dwStartIndex ) * cyMetrics;

    rect.bottom = rect.top + cyMetrics;

    SetBkColor( hdc,RGB( 0x00, 0x00, 0xff ) );

    ExtTextOut( hdc, 0, rect.top, ETO_OPAQUE, &rect, NULL, 0, 0 );

    //
    // Display candidate strings. 
    //

    SetBkMode( hdc, TRANSPARENT );

    dwTextColor = GetTextColor( hdc );

    for ( ; dwStartIndex < dwEndIndex; dwStartIndex++, y++ )
    {

        lpStr = (LPSTR) lpCandList +
                lpCandList->dwOffset[ dwStartIndex ];

        if ( dwStartIndex == lpCandList->dwSelection )
            SetTextColor( hdc, RGB( 255, 255, 255 ) );
        else
            SetTextColor( hdc, dwTextColor );

        TextOut( hdc, 3, y * cyMetrics, lpStr, lstrlen( lpStr ) );
    }


    SetTextColor( hdc, dwTextColor );
    
    SetBkColor( hdc, dwBackColor );

    ReleaseDC( hwnd, hdc );

}