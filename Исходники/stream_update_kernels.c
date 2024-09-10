LIBXSMM_EXTERN_C LIBXSMM_RETARGETABLE
void stream_vector_compscale( const double* i_a,
                              const double* i_b,
                              double*       io_c,
                              const int     i_length) {
  int l_n = 0;
  int l_trip_prolog = 0;
  int l_trip_stream = 0;
  
  /* init the trip counts */
  stream_init( i_length, (size_t)io_c, &l_trip_prolog, &l_trip_stream );

  /* run the prologue */
  for ( ; l_n < l_trip_prolog;  l_n++ ) {
    io_c[l_n] = i_a[l_n]*i_b[l_n];
  }
  /* run the bulk, hopefully using streaming stores */
#if defined(__SSE3__) && defined(__AVX__) && !defined(__AVX512F__)
  {
    /* we need manual unrolling as the compiler otherwise generates 
       too many dependencies */
    for ( ; l_n < l_trip_stream;  l_n+=8 ) {
      __m256d vec_a_1, vec_b_1;
      __m256d vec_a_2, vec_b_2;

      vec_a_1 = _mm256_loadu_pd(&(i_a[l_n]));
      vec_a_2 = _mm256_loadu_pd(&(i_a[l_n+4]));
      vec_b_1 = _mm256_loadu_pd(&(i_b[l_n]));
      vec_b_2 = _mm256_loadu_pd(&(i_b[l_n+4]));

#ifdef DISABLE_NONTEMPORAL_STORES
      _mm256_store_pd(  &(io_c[l_n]),   _mm256_mul_pd( vec_a_1, vec_b_1 ) );
      _mm256_store_pd(  &(io_c[l_n+4]), _mm256_mul_pd( vec_a_2, vec_b_2 ) );
#else
      _mm256_stream_pd( &(io_c[l_n]),   _mm256_mul_pd( vec_a_1, vec_b_1 ) );
      _mm256_stream_pd( &(io_c[l_n+4]), _mm256_mul_pd( vec_a_2, vec_b_2 ) );
#endif
    }
  }
#elif defined(__SSE3__) && defined(__AVX__) && defined(__AVX512F__)
  {
    for ( ; l_n < l_trip_stream;  l_n+=8 ) {
      __m512d vec_a, vec_b;

      vec_a = _mm512_loadu_pd(&(i_a[l_n]));
      vec_b = _mm512_loadu_pd(&(i_b[l_n]));

#ifdef DISABLE_NONTEMPORAL_STORES
      _mm512_store_pd(  &(io_c[l_n]), _mm512_mul_pd( vec_a, vec_b ) );
#else
      _mm512_stream_pd( &(io_c[l_n]), _mm512_mul_pd( vec_a, vec_b ) );
#endif
    }
  }
#else
  for ( ; l_n < l_trip_stream;  l_n++ ) {
    io_c[l_n] = i_a[l_n]*i_b[l_n];
  }
#endif
  /* run the epilogue */
  for ( ; l_n < i_length;  l_n++ ) {
    io_c[l_n] = i_a[l_n]*i_b[l_n];
  }
}