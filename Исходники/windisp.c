/*
 * _DisplayLineInWindowWithColor - as it sounds!
 */
void _DisplayLineInWindowWithColor( LPWDATA w, int line, LPSTR text, int c1,
                        int c2, int extra, int startcol )
{
  #ifdef _MBCS
    LPBYTE          tmp;
  #else
    LPSTR           tmp;
  #endif
    char            buff[256];
    int             start,end,a,spend,cnt1,cnt2;
    WORD            i;
    HWND            hwnd;

    hwnd = w->hwnd;

    /*** Find dimensions of line ***/
  #ifdef _MBCS
    tmp = FAR_mbsninc( (LPBYTE)text, startcol );
    a = FAR_mbslen( tmp );
    if( line < 1 || line >= w->height )
        return;
    start = 0;
    spend = end = w->width - extra;
    if( end > a )
        end = a;
    cnt1 = FAR_mbsnbcnt( tmp, end - start );
    cnt2 = spend - end;
    FAR_mbsnbcpy( (LPBYTE)buff, tmp, cnt1 - start );
    FARmemset( buff + cnt1, ' ', cnt2 );
    tmp = FAR_mbsninc( (LPBYTE)buff, cnt1 + cnt2 );
    *tmp = '\0';
  #else
    tmp = text;
    tmp += startcol;
    a = FARstrlen( tmp );
    if( line < 1 || line >= w->height )
        return;
    start = 0;
    spend = end = w->width - extra;
    if( end > a )
        end = a;
    cnt1 = end - start;
    cnt2 = spend - end;
    FARmemcpy( buff, tmp, cnt1 );
    FARmemset( buff + cnt1, ' ', cnt2 );
    buff[cnt1 + cnt2] = 0;
  #endif
    line--;

#if defined( __OS2__ )
    {
        RECTL           rcl;
        HPS             ps;
        POINTL          ptl;
        POINTL          points[TXTBOX_COUNT];

        ptl.x = 0;
        ptl.y = (w->y2 - w->y1) - (line+1)*w->ychar + w->base_offset;
        ps = WinGetPS( hwnd );
        _SelectFont( ps );
        GpiQueryTextBox( ps, startcol, w->tmpbuff->data, TXTBOX_COUNT, points );
        rcl.xLeft = points[TXTBOX_BOTTOMRIGHT].x;
    #ifdef _MBCS
        GpiQueryTextBox( ps, __mbslen( (unsigned char *)buff ), buff, TXTBOX_COUNT, points );
    #else
        GpiQueryTextBox( ps, strlen( buff ), buff, TXTBOX_COUNT, points );
    #endif
        rcl.xRight = points[TXTBOX_BOTTOMRIGHT].x;
        rcl.yTop = (w->y2 - w->y1) - line*w->ychar;
        rcl.yBottom = rcl.yTop - w->ychar;
        WinFillRect( ps, &rcl, c1 );
        GpiSetColor( ps, c2 );
    #ifdef _MBCS
        GpiCharStringAt( ps, &ptl, _mbsnbcnt(buff,w->width), buff );
    #else
        GpiCharStringAt( ps, &ptl, w->width, buff );
    #endif
        WinReleasePS( ps );
    }
#else
    {
        HDC     dc;
//      SIZE    size;
//      RECT    rect;

        dc = GetDC( hwnd );
        _SetMyDC( dc, _ColorMap[c2], _ColorMap[c1] );
//      #ifdef __NT__
//          GetTextExtentPoint32( dc, buff, strlen(buff), &size );
//      #else
//          GetTextExtentPoint( dc, buff, strlen(buff), &size );
//      #endif
//
    #ifdef _MBCS
        TextOut( dc, 0, line * w->ychar, (LPSTR)buff, FAR_mbsnbcnt( (LPBYTE)buff, w->width ) );
    #else
        TextOut( dc, 0, line * w->ychar, buff, w->width );
    #endif

        /*** Clear to end of line to remove any residue ***/
//      GetClientRect( w->hwnd, &rect );
//      rect.top = line * w->ychar;
//      rect.bottom = (line+1) * w->ychar ;
//      rect.left = size.cx;
//      FillRect( dc, &rect, w->brush );
        ReleaseDC( hwnd, dc );
    }
#endif

    /*** Update the w->image array ***/
#ifdef _MBCS
    {
        mb_char         mbc;
        unsigned char   *curMbc;
        int             count;

        i = line * w->width + startcol;
        for( count = 0, curMbc = (unsigned char *)buff; count < w->width - startcol; count++ ) {
            mbc = _mbsnextc( curMbc );          /* get the character */
            curMbc = _mbsinc( curMbc );         /* point to next char */
            w->image[i + count] = mbc;          /* store it in w->image */
        }
    }
#else
    i = line * w->width + startcol;
    FARmemcpy( &w->image[i], buff, w->width - startcol );
#endif
} /* _DisplayLineInWindowWithColor */