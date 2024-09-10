void main()
  {
    int   i;
    unsigned int c;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      c = _mbctoupper( chars[ i ] );
      if( c > 0xff )
        printf( "%c%c", c>>8, c );
      else
        printf( "%c", c );
    }