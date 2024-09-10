static int
gauss_jordan( GLU_complex M_1[ NCNC ] , 
	      const GLU_complex M[ NCNC ] )
{
  __m128d a[ NCNC ] GLUalign ; // temporary space to overwrite matrix
  register __m128d best , attempt , m1 , fac ;
  size_t i , j , piv ;

  // equate the necessary parts into double complex precision
  for( i = 0 ; i < NCNC ; i++ ) {
    a[ i ] = _mm_setr_pd( creal( M[i] ) , cimag( M[i] ) ) ;
    M_1[ i ] = ( i%(NC+1) ) ? 0.0 :1.0 ;
  }

  // set these pointers, pB will be the inverse
  __m128d *pB = (__m128d*)M_1 , *pA = (__m128d*)a ;
  
  // loop over diagonal of the square matrix M
  for( i = 0 ; i < NC-1 ; i++ ) {

    // column pivot by selecting the largest in magnitude value
    piv = i ;
    best = absfac( *( pA + i*(NC+1) ) ) ;
    for( j = i+1 ; j < NC ; j++ ) {
       attempt = absfac( *( pB + i + j*NC ) ) ;
      if( _mm_ucomilt_sd( best , attempt ) ) { 
	piv = j ; 
	best = attempt ; 
      }
    }

    // if we must pivot then we do
    if( piv != i ) {
      swap_rows( pA , pB , piv , i ) ;
    }
  
    // perform gaussian elimination to obtain the upper triangular
    fac = _mm_div_pd( SSE2_CONJ( *( pA + i*(NC+1) ) ) , best ) ;
    for( j = NC-1 ; j > i ; j-- ) { // go up in other columns
      eliminate_column( pA , pB , fac , i , j ) ;
    }
  }

  // a is upper triangular, do the same for the upper half
  // no pivoting to be done here
  for( i = NC-1 ; i > 0 ; i-- ) {
    fac = SSE2_inverse( *( pA + i*(NC+1) ) ) ;
    for( j = 0 ; j < i ; j++ ) {
      eliminate_column( pA , pB , fac , i , j ) ;
    }
  }

  // multiply each row by its M_1 diagonal
  for( j = 0 ; j < NC ; j++ ) {
    m1 = SSE2_inverse( *pA ) ;
    for( i = 0 ; i < NC ; i++ ) {
      *pB = SSE2_MUL( *pB , m1 ) ;
      pB++ ;
    }
    pA += NC+1 ;
  }

  return GLU_SUCCESS ;
}