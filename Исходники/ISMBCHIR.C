void main()
  {
    int   i;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      printf( "%#6.4x is %sa valid "
            "Hiragana character\n",
            chars[i],
            ( _ismbchira( chars[i] ) ) ? "" : "not " );
    }
  }