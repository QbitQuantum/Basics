void main( int argc, const char *argv[] )
  {
    int i;
    unsigned num = 0;
    char **array = (char **)calloc( argc, sizeof(char **) );
    int compare( const void *, const void * );

    for( i = 1; i < argc; ++i ) {
      lsearch( &argv[i], array, &num, sizeof(char **),
                  compare );
    }
    for( i = 0; i < num; ++i ) {
      printf( "%s\n", array[i] );
    }
  }