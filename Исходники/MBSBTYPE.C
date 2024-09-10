void main()
  {
    int     i;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ )
      printf( "%s\n", types[ 1+_mbsbtype( chars, i ) ] );
  }