        q--;
    }

    d1x = ((3L * d1x) << (2 * bez_qual)) + ((3L * d2x) << bez_qual) + d3x;
    /* assert( d1x <=  0x5f408000 ); */
    /* assert( d1x >= -0x5f408000 ); */

    d3x = 6L*d3x;
    /* assert( d3x <=  0xbffe8 ); */
    /* assert( d3x >= -0xbffe8 ); */

    d2x = ((6L*d2x)<<bez_qual) + d3x;
    /* assert( d2x <=  0x2f6fa12 ); */
    /* assert( d2x >= -0x2f6fa12 ); */

    x0 = labs(array[0]);
    while( x0 >= (0x7fffffffL>>q) )
        q--, qd++;

    x0 = (((LONG)array[0]) << q) + (1L << (q - 1));

    for(i = 1 << bez_qual; i > 0; i--) {
        x = (WORD)(x0 >> q);
        *px = x;
        if ( x < *pmin )
            *pmin = x;
        if ( x > *pmax )
            *pmax = x;
        px+=2;

        if (labs( (x0 >> 1) + (d1x >> (qd + 1)) ) >= 0x3ffffffeL) {