                      , double complex const           E[restrict PNLx][PNLy][PNLz]
                      , double complex                 F[restrict PNLx][PNLy][PNLz]
)
{
  const  double         A = *A_;
  double         const* b;
  double complex const* e;
  double complex      * f;

  int ix, iy, iz, n;

#ifdef ARTED_STENCIL_LOOP_BLOCKING
  int bx, by;
#endif

  __m512d at   = _mm512_set1_pd(A);
  __m512d HALF = _mm512_set1_pd(-0.5);
#ifdef TUNING_COMPLEX_MUL
  __m512i INV  = _mm512_set4_epi64(1LL << 63, 0, 1LL << 63, 0);
#else
  __m512d ZI   = _mm512_set_pd(-1, 0, -1, 0, -1, 0, -1, 0);
#endif

  __declspec(align(64)) double G[12];
  for(n = 0 ; n < 12 ; ++n)
    G[n] = C[n] * -0.5;

  __m512i nly = _mm512_set1_epi32(PNLy);
  __m512i nlz = _mm512_set1_epi32(PNLz);
#ifdef ARTED_DOMAIN_POWER_OF_TWO
  __m512i myx = _mm512_mask_blend_epi32(0xFF00, _mm512_set1_epi32(NLy - 1), _mm512_set1_epi32(NLx - 1));