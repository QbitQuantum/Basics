        static void division( MLDiv const &x, MLDiv const &y,
                              MLDiv &q, MLDiv &r ) {
            UBIG m;
            UBIG n;
            UBIG y1;

            m = length( y );
            if( m == 1 ) {
                y1 = y.d[ m - 1 ];
                if( y1 > 0 ) {
                    quotient( q, x, y1 );
                    remainder( r, x, y1 );
                } else {
                    fatal( "divide by 0" );
                }
            } else {
                n = length( x );
                if( m > n ) {
                    zero( q );
                    r = x;
                } else {
                    assert( 2 <= m && m <= n && n <= w );
                    longdivide( x, y, q, r, n, m );
                }
            }
        }