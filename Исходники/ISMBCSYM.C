void main()
  {
    int   i;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      printf( "%#6.4x is %sa valid "
            "multibyte symbol character\n",
            chars[i],
            ( _ismbcsymbol( chars[i] ) ) ? "" : "not " );
    }
  }