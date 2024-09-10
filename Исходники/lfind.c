void main( int argc, const char *argv[] )
  {
    unsigned num = 5;
    int compare( const void *, const void * );

    if( argc <= 1 ) exit( EXIT_FAILURE );
    if( lfind( &argv[1], keywords, &num, sizeof(char **),
                    compare ) == NULL ) {
      printf( "'%s' is not a C keyword\n", argv[1] );
      exit( EXIT_FAILURE );
    } else {
      printf( "'%s' is a C keyword\n", argv[1] );
      exit( EXIT_SUCCESS );
    }
  }