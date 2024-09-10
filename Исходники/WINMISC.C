/*
 * _DisplayCursor - show the current cursor position
 */
void _DisplayCursor( LPWDATA w )
{
    HDC                 dc;
    SIZE                size;

    dc = GetDC( w->hwnd );
    SelectObject( dc, _FixedFont );
    #ifdef _MBCS
        #ifdef __NT__
            GetTextExtentPoint32( dc, w->tmpbuff->data,
                                  FAR_mbsnbcnt( (LPBYTE)w->tmpbuff->data,w->buffoff+w->curr_pos),
                                  &size );
        #else
            GetTextExtentPoint( dc, w->tmpbuff->data,
                                FAR_mbsnbcnt( (LPBYTE)w->tmpbuff->data, w->buffoff + w->curr_pos),
                                &size );
        #endif
    #else
        #ifdef __NT__
            GetTextExtentPoint32( dc, w->tmpbuff->data, w->buffoff+w->curr_pos,
                                  &size );
        #else
            GetTextExtentPoint( dc, w->tmpbuff->data, w->buffoff+w->curr_pos,
                                &size );
        #endif
    #endif
    SetCaretPos( size.cx+1, (w->LastLineNumber-w->TopLineNumber)*w->ychar );
    ReleaseDC( w->hwnd, dc );
    ShowCaret( w->hwnd );

} /* _DisplayCursor */