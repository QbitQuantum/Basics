void main()
  {
    int   i;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      printf( "%#6.4x is %sa valid "
            "JIS L1 character\n",
            chars[i],
            ( _ismbcl1( chars[i] ) ) ? "" : "not " );
    }
  }