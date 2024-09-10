// only compute the necessary indices of su2_i = subgroup( U*staple^\dagger )
void
only_subgroup( GLU_complex *s0 ,
	       GLU_complex *s1 ,
	       double *scale ,
	       const GLU_complex U[ NCNC ] ,
	       const GLU_complex staple[ NCNC ] ,
	       const size_t su2_index )
{
  const __m128d *u = (const __m128d*)U ;
  const __m128d *s = (const __m128d*)staple ;

  register __m128d sm0 ; 
  register __m128d sm1 ;
#if NC == 3
  switch( su2_index%3 ) { // I don't like this
    // rotation 1
    //  |  s0   s1  0 |
    //  | -s1*  s0* 0 |
    //  |  0     0  1 |
  case 0 :
    sm0 = _mm_add_pd(
		     // temp0
		     _mm_add_pd( SSE2_MUL_CONJ( *( u + 0 ) , *( s + 0 ) ) ,
				 _mm_add_pd( SSE2_MUL_CONJ( *( u + 1 ) , *( s + 1 ) ) ,
					     SSE2_MUL_CONJ( *( u + 2 ) , *( s + 2 ) ) ) ) ,
		      // temp3^*
		     _mm_add_pd( SSE2_MULCONJ( *( u + 3 ) , *( s + 3 ) ) ,
				 _mm_add_pd( SSE2_MULCONJ( *( u + 4 ) , *( s + 4 ) ) ,
					     SSE2_MULCONJ( *( u + 5 ) , *( s + 5 ) ) ) ) ) ;
    sm1 = _mm_sub_pd( 
		     // temp1
		     _mm_add_pd( SSE2_MUL_CONJ( *( u + 0 ) , *( s + 3 ) ) ,
				 _mm_add_pd( SSE2_MUL_CONJ( *( u + 1 ) , *( s + 4 ) ) ,
					     SSE2_MUL_CONJ( *( u + 2 ) , *( s + 5 ) ) ) ) ,
		     // temp2^*
		     _mm_add_pd( SSE2_MULCONJ( *( u + 3 ) , *( s + 0 ) ) ,
				 _mm_add_pd( SSE2_MULCONJ( *( u + 4 ) , *( s + 1 ) ) ,
					     SSE2_MULCONJ( *( u + 5 ) , *( s + 2 ) ) ) ) ) ;
    break ;
  case 1 :
    // rotation 2
    //  |  1    0   0  |
    //  |  0   s0  s1  |
    //  |  0  -s1* s0* |
    sm0 = _mm_add_pd( 
		     // temp0
		     _mm_add_pd( SSE2_MUL_CONJ( *( u + 3 ) , *( s + 3 ) ) ,
				 _mm_add_pd( SSE2_MUL_CONJ( *( u + 4 ) , *( s + 4 ) ) ,
					     SSE2_MUL_CONJ( *( u + 5 ) , *( s + 5 ) ) ) ) ,
		     // temp3^*
		     _mm_add_pd( SSE2_MULCONJ( *( u + 6 ) , *( s + 6 ) ) ,
				 _mm_add_pd( SSE2_MULCONJ( *( u + 7 ) , *( s + 7 ) ) ,
					     SSE2_MULCONJ( *( u + 8 ) , *( s + 8 ) ) ) ) ) ;
    sm1 = _mm_sub_pd(
		     // temp1
		     _mm_add_pd( SSE2_MUL_CONJ( *( u + 3 ) , *( s + 6 ) ) ,
				 _mm_add_pd( SSE2_MUL_CONJ( *( u + 4 ) , *( s + 7 ) ) ,
					     SSE2_MUL_CONJ( *( u + 5 ) , *( s + 8 ) ) ) ) ,
		     // temp2^*
		     _mm_add_pd( SSE2_MULCONJ( *( u + 6 ) , *( s + 3 ) ) ,
				 _mm_add_pd( SSE2_MULCONJ( *( u + 7 ) , *( s + 4 ) ) ,
					     SSE2_MULCONJ( *( u + 8 ) , *( s + 5 ) ) ) ) ) ;
    break ;
  case 2 :
    // rotation 3
    //  | s0*  0  -s1 |
    //  |  0   1   0  |
    //  | s1   0  s0  |
    sm0 = _mm_add_pd( 
		     // temp3^*
		     _mm_add_pd( SSE2_MULCONJ( *( u + 0 ) , *( s + 0 ) ) ,
				 _mm_add_pd( SSE2_MULCONJ( *( u + 1 ) , *( s + 1 ) ) ,
					     SSE2_MULCONJ( *( u + 2 ) , *( s + 2 ) ) ) ) ,
		     // temp0
		     _mm_add_pd( SSE2_MUL_CONJ( *( u + 6 ) , *( s + 6 ) ) ,
				 _mm_add_pd( SSE2_MUL_CONJ( *( u + 7 ) , *( s + 7 ) ) ,
					     SSE2_MUL_CONJ( *( u + 8 ) , *( s + 8 ) ) ) ) ) ;
    sm1 = _mm_sub_pd(
		     // temp1
		     _mm_add_pd( SSE2_MUL_CONJ( *( u + 6 ) , *( s + 0 ) ) ,
				 _mm_add_pd( SSE2_MUL_CONJ( *( u + 7 ) , *( s + 1 ) ) ,
					     SSE2_MUL_CONJ( *( u + 8 ) , *( s + 2 ) ) ) ) ,
		     // temp2^*
		     _mm_add_pd( SSE2_MULCONJ( *( u + 0 ) , *( s + 6 ) ) ,
				 _mm_add_pd( SSE2_MULCONJ( *( u + 1 ) , *( s + 7 ) ) ,
					     SSE2_MULCONJ( *( u + 2 ) , *( s + 8 ) ) ) ) ) ;
    break ;
  }
#elif NC == 2
  sm0 = _mm_add_pd( 
		   // temp0
		   _mm_add_pd( SSE2_MUL_CONJ( *( u + 0 ) , *( s + 0 ) ) , 
			       SSE2_MUL_CONJ( *( u + 1 ) , *( s + 1 ) ) ) ,
		   // temp3^*
		   _mm_add_pd( SSE2_MULCONJ( *( u + 2 ) , *( s + 2 ) ) , 
			       SSE2_MULCONJ( *( u + 3 ) , *( s + 3 ) ) ) ) ;
  
  sm1 = _mm_sub_pd( 
		   // temp1
		   _mm_add_pd( SSE2_MUL_CONJ( *( u + 0 ) , *( s + 2 ) ) , 
			       SSE2_MUL_CONJ( *( u + 1 ) , *( s + 3 ) ) ) ,
		   // temp2^*
		   _mm_add_pd( SSE2_MULCONJ( *( u + 2 ) , *( s + 0 ) ) ,
			       SSE2_MULCONJ( *( u + 3 ) , *( s + 1 ) ) ) ) ;
#else
  // su(N) version
  const size_t row_a = Latt.su2_data[ su2_index ].idx_a / NC ;
  const size_t col_b = Latt.su2_data[ su2_index ].idx_b % NC ;

  // prefetch the staple & link indices
  const __m128d *S1 = ( s + NC * row_a ) , *S2 = ( s + NC * col_b ) ; 
  const __m128d *U1 = ( u + NC * row_a ) , *U2 = ( u + NC * col_b ) ; 

  // initialise to zero & perform multiplication
  sm0 = _mm_setzero_pd() ; sm1 = _mm_setzero_pd() ;

  size_t i ;
  for( i = 0 ; i < NC ; i++ ) {
    sm0 = _mm_add_pd( sm0 ,
		      _mm_add_pd( SSE2_MUL_CONJ( *U1 , *S1 ) ,
				  SSE2_MULCONJ( *U2 , *S2 ) ) ) ;
    sm1 = _mm_add_pd( sm1 ,
		      _mm_sub_pd( SSE2_MUL_CONJ( *U1 , *S2 ) ,
				  SSE2_MULCONJ( *U2 , *S1 ) ) ) ;
    // increment our pointers
    S1++ , S2++ , U1++ , U2++ ;
  }
#endif

  // puts the norm in both parts
  register __m128d z = SSE2_FMA( sm0 , sm0 , _mm_mul_pd( sm1 , sm1 ) ) ; 
  z = _mm_add_pd( z , _mm_shuffle_pd( z , z , 1 ) ) ;
  z = _mm_sqrt_pd( z ) ;
  z = _mm_div_pd( _mm_set1_pd( 1.0 ) , z ) ;
  sm0 = _mm_mul_pd( sm0 , z ) ;
  sm1 = _mm_mul_pd( sm1 , z ) ;

  // poke back into *s0 and *s1 and *scale
  _mm_store_pd( (void*)s0 , sm0 ) ; 
  _mm_store_pd( (void*)s1 , sm1 ) ; 
  _mm_store_sd( (void*)scale , z ) ;

  return ;
}