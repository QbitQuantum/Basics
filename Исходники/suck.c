BOOL CopyCheck(
    CHAR        *pchPath,
    FILENAME    *fnCurrent
) {
    WORD        wFatDate;
    WORD        wFatTime;
    WORD        wDATFatDate;
    WORD        wDATFatTime;
    BOOL        b;

    if ( fnCurrent->dwDATFileSizeLow != fnCurrent->dwFileSizeLow ) {
        return( TRUE );
    }
    if ( fnCurrent->dwDATFileSizeHigh != fnCurrent->dwFileSizeHigh ) {
        return( TRUE );
    }
    b = FileTimeToDosDateTime( &fnCurrent->ftDATFileTime, &wDATFatDate, &wDATFatTime );
    if ( !b ) {
        return( TRUE );
    }
    b = FileTimeToDosDateTime( &fnCurrent->ftFileTime, &wFatDate, &wFatTime );
    if ( !b ) {
        return( TRUE );
    }

    if ( wDATFatTime != wFatTime ) {
        return( TRUE );
    }
    if ( wDATFatDate != wFatDate ) {
        return( TRUE );
    }
    return( FALSE );
}