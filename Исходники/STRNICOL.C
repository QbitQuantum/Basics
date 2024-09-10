void main()
  {
    _setmbcp( 932 );
    if( _strnicoll( buffer, "Hello" ) < 0 ) {
        printf( "Less than\n" );
    }
  }