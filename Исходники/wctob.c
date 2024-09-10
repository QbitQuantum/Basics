void main()
{
    int         i, j;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      j = wctob( wc[i] );
      if( j == EOF ) {
        printf( "%#6.4x EOF\n", wc[i] );
      } else {
        printf( "%#6.4x->%#6.4x\n", wc[i], j );
      }
    }
}