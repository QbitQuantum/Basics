void main()
  {
    int   i;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      printf( "%#6.4x is %sa valid "
            "multibyte uppercase character\n",
            chars[i],
            ( _ismbcupper( chars[i] ) ) ? "" : "not " );
    }
  }