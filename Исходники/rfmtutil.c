static  void    OutInt( uint width, uint min ) {
//==============================================

    char        *number;
    uint        length;
    uint        space;
    bool        minus;
    intstar4    iorslt;

    if( UndefIntRtn( width ) ) return;
    iorslt = IORslt.intstar4;
    if( ( iorslt == 0 ) && ( min == 0 ) ) {
        SendChar( ' ', width );
    } else {
        minus = ( iorslt < 0 );
        number = IOCB->buffer;
        if( minus ) {
            number++; // skip the minus sign
        }
        ltoa( iorslt, IOCB->buffer, 10 );
        length = strlen( number );
        if( length > min ) {
            min = length;
        }
        if( min <= width ) {
            space = width - min;
            if( minus || ( IOCB->flags & IOF_PLUS ) ) {
                if( space != 0 ) {
                    SendChar( ' ', space - 1 );
                    if( minus ) {
                        Drop( '-' );
                    } else {
                        Drop( '+' );
                    }
                    SendChar( '0', min - length );
                    SendStr( number, length );
                } else {
                    SendChar( '*', width );
                }
            } else {
                SendChar( ' ', space );
                SendChar( '0', min - length );
                SendStr( number, length );
            }
        } else {
            SendChar( '*', width );
        }
    }
}