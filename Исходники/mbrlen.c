void main()
  {
    int         i, j, k;

    _setmbcp( 932 );
    j = 1;
    for( i = 0; j > 0; i += j ) {
      j = mbrlen( &chars[i], MB_CUR_MAX, NULL );
      printf( "%d bytes in character ", j );
      if( errno == EILSEQ ) {
        printf( " - illegal multibyte character\n" );
      } else {
        if( j == 0 ) {
          k = 0;
        } else if ( j == 1 ) {
          k = chars[i];
        } else if( j == 2 ) {
          k = chars[i]<<8 | chars[i+1];
        }
        printf( "(%#6.4x)\n", k );
      }
    }
  }