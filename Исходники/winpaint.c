void _RepaintWindow( LPWDATA w, PRECT rcPaint, HDC ph )
#endif
{
    WORD                i;
    WORD                ptop, pbot, pleft, pright, poff, pdown;
    WORD                width;
#ifdef _MBCS
    mb_char _WCI86FAR   *image;
    unsigned char       mbc[MB_CUR_MAX + 1];
#else
    LPSTR               image;
#endif
#if !defined( __OS2__ )
    HFONT               oldfont;
#endif

    /*
     * get area to redraw
     */
    ptop = rcPaint->top / w->ychar;
    if( ptop > 0 && ( rcPaint->top % w->ychar ) != 0 )
        ptop--;
    pbot = rcPaint->bottom / w->ychar ;
    if( pbot == 0 )
        return;
    if( pbot >= w->height )
        pbot = w->height - 1;
    if( ( rcPaint->bottom % w->ychar ) == 0 )
        pbot--;
    pleft = 0;
    pright = w->width - 1;
    width = w->width;
    poff = pleft * w->xchar;
    pdown = ptop * w->ychar;

    /*
     * draw all lines
     */
#if defined( __OS2__ )
#else
    oldfont = SelectObject( (HDC)ph, _FixedFont );
#endif
    for( i = ptop; i <= pbot; i++ ) {
        image = &w->image[i * w->width];
#if defined( __OS2__ )
        {
            POINTL      ptl;

            ptl.x = poff;
            ptl.y = ( w->y2 - w->y1 ) - ( pdown + w->ychar ) + w->base_offset;
    #ifdef _MBCS
            {
                WORD        count;
                LPSTR       buff;

                buff = FARmalloc( sizeof( mb_char ) * ( width + 1 ) );
                if( buff == NULL )
                    _OutOfMemoryExit();
                *buff = '\0';
                for( count = 0; count < width; count++ ) {
                    _mbvtop( image[pleft + count], mbc );
                    mbc[_mbclen( mbc )] = '\0';
                    FARstrcat( buff, (char *)mbc );
                }
                GpiCharStringAt( (HPS)ph, &ptl, FAR_mbsnbcnt( (PBYTE)buff, width ), buff );
                FARfree( buff );
            }
    #else
            GpiCharStringAt( (HPS)ph, &ptl, width, &image[pleft] );
    #endif
        }
#else
        SetBkColor( (HDC)ph, _ColorMap[w->background_color] );
        SetTextColor( (HDC)ph, _ColorMap[w->text_color] );
    #ifdef _MBCS
        {
            WORD        count;
            size_t      bytes;
            LPSTR       buff;

            buff = FARmalloc( sizeof( mb_char ) * ( width + 1 ) );
            if( buff == NULL )
                _OutOfMemoryExit();
            *buff = '\0';
            for( count = 0; count < width; count++ ) {
                _mbvtop( image[pleft + count], mbc );
                mbc[_mbclen( mbc )] = '\0';
                FARstrcat( buff, (LPSTR)mbc );
            }
            bytes = FARstrlen( buff );
            TextOut( (HDC)ph, poff, pdown, buff, bytes );
            FARfree( buff );
        }
    #else
        TextOut( (HDC)ph, poff, pdown, &image[pleft], width );
    #endif
#endif
        pdown += w->ychar;
    }
#if !defined( __OS2__ )
    SelectObject( (HDC)ph, oldfont );
#endif

} /* _RepaintWindow */