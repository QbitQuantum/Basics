/* Blake2b compression function modified to do only one single round
 */
static inline void blake2round(blake2b_state* S, 
  const uint8_t block[BLAKE2B_BLOCKBYTES], unsigned ridx){
    __m128i row1l, row1h;
  __m128i row2l, row2h;
  __m128i row3l, row3h;
  __m128i row4l, row4h;
  __m128i b0, b1;
  __m128i t0, t1;
#if defined(HAVE_SSSE3) && !defined(HAVE_XOP)
  const __m128i r16 = _mm_setr_epi8( 2, 3, 4, 5, 6, 7, 0, 1, 10, 11, 12, 13, 14, 15, 8, 9 );
  const __m128i r24 = _mm_setr_epi8( 3, 4, 5, 6, 7, 0, 1, 2, 11, 12, 13, 14, 15, 8, 9, 10 );
#endif
#if defined(HAVE_SSE41)
  const __m128i m0 = LOADU( block + 00 );
  const __m128i m1 = LOADU( block + 16 );
  const __m128i m2 = LOADU( block + 32 );
  const __m128i m3 = LOADU( block + 48 );
  const __m128i m4 = LOADU( block + 64 );
  const __m128i m5 = LOADU( block + 80 );
  const __m128i m6 = LOADU( block + 96 );
  const __m128i m7 = LOADU( block + 112 );
#else
  const uint64_t  m0 = ( ( uint64_t * )block )[ 0];
  const uint64_t  m1 = ( ( uint64_t * )block )[ 1];
  const uint64_t  m2 = ( ( uint64_t * )block )[ 2];
  const uint64_t  m3 = ( ( uint64_t * )block )[ 3];
  const uint64_t  m4 = ( ( uint64_t * )block )[ 4];
  const uint64_t  m5 = ( ( uint64_t * )block )[ 5];
  const uint64_t  m6 = ( ( uint64_t * )block )[ 6];
  const uint64_t  m7 = ( ( uint64_t * )block )[ 7];
  const uint64_t  m8 = ( ( uint64_t * )block )[ 8];
  const uint64_t  m9 = ( ( uint64_t * )block )[ 9];
  const uint64_t m10 = ( ( uint64_t * )block )[10];
  const uint64_t m11 = ( ( uint64_t * )block )[11];
  const uint64_t m12 = ( ( uint64_t * )block )[12];
  const uint64_t m13 = ( ( uint64_t * )block )[13];
  const uint64_t m14 = ( ( uint64_t * )block )[14];
  const uint64_t m15 = ( ( uint64_t * )block )[15];
#endif
  row1l = LOAD( &S->h[0] );
  row1h = LOAD( &S->h[2] );
  row2l = LOAD( &S->h[4] );
  row2h = LOAD( &S->h[6] );
  row3l = LOAD( &blake2b_IV[0] );
  row3h = LOAD( &blake2b_IV[2] );
  row4l = _mm_xor_si128( LOAD( &blake2b_IV[4] ), LOAD( &S->t[0] ) );
  row4h = _mm_xor_si128( LOAD( &blake2b_IV[6] ), LOAD( &S->f[0] ) );

  switch(ridx){
    case 0:ROUND( 0 );break;
    case 1:ROUND( 1 );break;
    case 2:ROUND( 2 );break;
    case 3:ROUND( 3 );break;
    case 4:ROUND( 4 );break;
    case 5:ROUND( 5 );break;
    case 6:ROUND( 6 );break;
    case 7:ROUND( 7 );break;
    case 8:ROUND( 8 );break;
    case 9:ROUND( 9 );break;
    case 10:ROUND( 10 );break;
    case 11:ROUND( 11 );break;
  }
  
  row1l = _mm_xor_si128( row3l, row1l );
  row1h = _mm_xor_si128( row3h, row1h );
  STORE( &S->h[0], _mm_xor_si128( LOAD( &S->h[0] ), row1l ) );
  STORE( &S->h[2], _mm_xor_si128( LOAD( &S->h[2] ), row1h ) );
  row2l = _mm_xor_si128( row4l, row2l );
  row2h = _mm_xor_si128( row4h, row2h );
  STORE( &S->h[4], _mm_xor_si128( LOAD( &S->h[4] ), row2l ) );
  STORE( &S->h[6], _mm_xor_si128( LOAD( &S->h[6] ), row2h ) );
}