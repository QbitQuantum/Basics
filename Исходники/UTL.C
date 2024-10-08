void nDrawConcaveFrame( HDC hDestDC, RECT rc )
{
#ifdef DEBUGGING
// the below two statements are for debugging on my mono monitor.
    static LOGPEN lpLtGray = { PS_SOLID, 1, 1, clrBLACK },
                  lpWhite  = { PS_SOLID, 1, 1, clrBLACK };
#else
    static LOGPEN lpLtGray = { PS_SOLID, 1, 1, clrDKGRAY },
                  lpWhite  = { PS_SOLID, 1, 1, clrWHITE };
#endif

    HPEN hLtGray, hWhite;

    hLtGray = CreatePenIndirect( &lpLtGray );
    hWhite  = CreatePenIndirect( &lpWhite );

    MoveTo( hDestDC, rc.right, rc.top );

    // Paint the top and left side lines, light gray.
    SelectObject( hDestDC, hLtGray );
    LineTo( hDestDC, rc.left, rc.top );
    LineTo( hDestDC, rc.left, rc.bottom );

    // Paint the bottom and right side lines, white.
    SelectObject( hDestDC, hWhite );
    LineTo( hDestDC, rc.right, rc.bottom );
    LineTo( hDestDC, rc.right, rc.top );

    DeleteObject( hLtGray );
    DeleteObject( hWhite );

    // Rectangle( hDestDC, rc.left, rc.top, rc.right, rc.bottom );

}