void main()
  {
    int             i;
    unsigned short  c;

    _setmbcp( 932 );
    for( i = 0; i < sizeof( alphabet ) - 1; i++ ) {
      c = _mbbtombc( alphabet[ i ] );
      printf( "%c%c", c>>8, c );
    }
    printf( "\n" );
  }