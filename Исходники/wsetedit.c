bool WSetEditWithSINT32( HWND edit, int_32 val, int base )
{
    char temp[35];

    ltoa( val, temp, base );

    if( base == 16 ) {
        memmove( temp + 2, temp, 33 );
        temp[0] = '0';
        temp[1] = 'x';
    } else if( base == 8 ) {
        memmove( temp + 1, temp, 34 );
        temp[0] = '0';
    }

    return( WSetEditWithStr( edit, temp ) );
}