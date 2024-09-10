int memcmp( const void *s1, const void *s2, size_t n )
/****************************************************/
{
    UINT *              dw1 = ROUND(s1);        /* round down to dword */
    UINT *              dw2 = ROUND(s2);        /* round down to dword */
    UINT                dword1, dword2, tmpdword1, tmpdword2;
    int                 tmpchar, shr1, shr2, shl1, shl2;

    if( n == 0 )  return( 0 );

    /*** Initialize locals ***/
    shr1 = OFFSET(s1) << 3;             /* shift right = offset * 8 */
    shr2 = OFFSET(s2) << 3;
    shl1 = INT_SIZE - shr1;             /* shift left = 32 - shift right */
    shl2 = INT_SIZE - shr2;

    if (shr1 != 0) {
        dword1 = *dw1++;
    }
    if (shr2 != 0) {
        dword2 = *dw2++;
    }

    /*** Scan in aligned 4-byte groups ***/
    for( ;; ) {
        /*** Extract the next few characters from each string ***/
        if( shr1 == 0 ) {
            tmpdword1 = *dw1++;
        } else {
            tmpdword1 = dword1 >> shr1;
            dword1 = *dw1++;
            tmpdword1 |= (dword1 << shl1);
        }
        if( shr2 == 0 ) {
            tmpdword2 = *dw2++;
        } else {
            tmpdword2 = dword2 >> shr2;
            dword2 = *dw2++;
            tmpdword2 |= (dword2 << shl2);
        }

        if( n < BYTES_PER_WORD )  break;

        /*** Are s1 and s2 still the same? ***/
        if( tmpdword1 != tmpdword2 ) {
            tmpchar = CHR1(tmpdword1) - CHR1(tmpdword2);
            if( tmpchar )  return( tmpchar );

            tmpchar = CHR2(tmpdword1) - CHR2(tmpdword2);
            if( tmpchar )  return( tmpchar );

            tmpchar = CHR3(tmpdword1) - CHR3(tmpdword2);
            if( tmpchar )  return( tmpchar );

            return( CHR4(tmpdword1) - CHR4(tmpdword2) );
        }
        n -= BYTES_PER_WORD;
    }

    /*** Scan the last byte(s) in the buffer ***/
    if( tmpdword1 == tmpdword2 )  return( 0 );
    if( n == 1 ) {
        return( CHR1(tmpdword1) - CHR1(tmpdword2) );
    } else if( n == 2 ) {
        tmpchar = CHR1(tmpdword1) - CHR1(tmpdword2);
        if( tmpchar )  return( tmpchar );
        return( CHR2(tmpdword1) - CHR2(tmpdword2) );
    } else if( n == 3 ) {
        tmpchar = CHR1(tmpdword1) - CHR1(tmpdword2);
        if( tmpchar )  return( tmpchar );
        tmpchar = CHR2(tmpdword1) - CHR2(tmpdword2);
        if( tmpchar )  return( tmpchar );
        return( CHR3(tmpdword1) - CHR3(tmpdword2) );
    }

    return( 0 );
}