void cStream::allocateArrays()
{
  if( mArraysAreAllocated )
  {
#ifdef vs2005
    a = (double*)_aligned_realloc( a, N * sizeof(double), 16 );
    b = (double*)_aligned_realloc( b, N * sizeof(double), 16 );
    c = (double*)_aligned_realloc( c, N * sizeof(double), 16 );
#else
    free( a );
    free( b );
    free( c );
  #ifdef windowos
    a = (double*)malloc( N * sizeof(double) );
    b = (double*)malloc( N * sizeof(double) );
    c = (double*)malloc( N * sizeof(double) );
  #else
    a = (double*)valloc( N * sizeof(double) );
    b = (double*)valloc( N * sizeof(double) );
    c = (double*)valloc( N * sizeof(double) );
  #endif
#endif
  } else
  {
#ifdef vs2005
    // allocate memory from heap for arrays
    a = (double*)_aligned_malloc( N * sizeof(double), 16 );
    b = (double*)_aligned_malloc( N * sizeof(double), 16 );
    c = (double*)_aligned_malloc( N * sizeof(double), 16 );
    bytes = (double*)_aligned_malloc( 4 * sizeof(double), 16 );
#else
    // obtain clock update frequency:
    freq = CLOCKS_PER_SEC;
    // allocate memory from heap for arrays
    #ifdef windowsos
     a = (double*)malloc( N * sizeof(double) );
     b = (double*)malloc( N * sizeof(double) );
     c = (double*)malloc( N * sizeof(double) );
     bytes = (double*)_malloc( 4 * sizeof(double) );
    #else
     a = (double*)valloc( N * sizeof(double) );
     b = (double*)valloc( N * sizeof(double) );
     c = (double*)valloc( N * sizeof(double) );
     bytes = (double*)valloc( 4 * sizeof(double) );
    #endif
#endif
  }
  bytes[ eCopy  ] = 2 * sizeof(double) * N;
  bytes[ eScale ] = 2 * sizeof(double) * N;
  bytes[ eAdd   ] = 3 * sizeof(double) * N;
  bytes[ eTriad ] = 3 * sizeof(double) * N;
  mArraysAreAllocated = true;
} // void cStream::allocateArrays()