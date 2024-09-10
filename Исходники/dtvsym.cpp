bool DTViewSymbol::leftBttnDbl( int x, int y, WMouseKeyFlags )
//------------------------------------------------------------
{
    int prev = _descPaint->current();
    if( _descPaint->select( x, y ) ) {
        if( prev != _descPaint->current() ) {
            if( prev >= 0 ) {
                invalidateRect( _descPaint->partRect( prev ) );
            }
            invalidateRect( _descPaint->partRect( _descPaint->current() ) );
        }
        _descPaint->enterHit();
        return TRUE;
    }
    return FALSE;
}