void main()
  {
    int             i;
    unsigned int    c;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      c = _mbctombb( alphabet[ i ] );
      printf( "%c", c );
    }
    printf( "\n" );
  }