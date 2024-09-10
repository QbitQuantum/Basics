void main()
  {
    int   i;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      printf( "%#6.4x - %#6.4x\n",
              chars[ i ],
              _mbctokata( chars[ i ] ) );
    }
  }