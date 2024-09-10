void main()
  {
    int   i;

    _setmbcp( 932 );
    for( i = 0; i < SIZE; i++ ) {
      printf( "%#6.4x is %sa valid "
            "multibyte print character\n",
            chars[i],
            ( _ismbcprint( chars[i] ) ) ? "" : "not " );
    }
  }