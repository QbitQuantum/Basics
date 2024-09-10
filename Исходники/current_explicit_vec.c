                     , double complex const* restrict E
                     , double              * restrict F
                     , double              * restrict G
                     , double              * restrict H
) {
#if defined(__KNC__) || defined(__AVX512F__)
/* Hand-Code Vector processing for Xeon Phi */
  double complex const* e;

  int ix, iy, iz, n;

#ifdef ARTED_STENCIL_LOOP_BLOCKING
  int bx, by;
#endif

  __m512d CONJ = _mm512_set_pd(-1, 1, -1, 1, -1, 1, -1, 1);

  __m512d tt[3];
  for(n = 0 ; n < 3 ; ++n)
    tt[n] = _mm512_setzero_pd();

  __m512d wm[4];
  __m512d wp[4];
  __m512d v1, v2, v3;

  __m512i nly = _mm512_set1_epi32(NLy);
  __m512i nlz = _mm512_set1_epi32(NLz);
  __m512i nyx = _mm512_mask_blend_epi32(0xFF00, _mm512_set1_epi32(NLy    ), _mm512_set1_epi32(NLx    ));
#ifdef ARTED_DOMAIN_POWER_OF_TWO
  __m512i myx = _mm512_mask_blend_epi32(0xFF00, _mm512_set1_epi32(NLy - 1), _mm512_set1_epi32(NLx - 1));
#endif