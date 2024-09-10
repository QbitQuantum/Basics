/**
 * See av1_wedge_sse_from_residuals_c
 */
uint64_t av1_wedge_sse_from_residuals_sse2(const int16_t *r1, const int16_t *d,
                                           const uint8_t *m, int N) {
  int n = -N;
  int n8 = n + 8;

  uint64_t csse;

  const __m128i v_mask_max_w = _mm_set1_epi16(MAX_MASK_VALUE);
  const __m128i v_zext_q = _mm_set_epi32(0, 0xffffffff, 0, 0xffffffff);

  __m128i v_acc0_q = _mm_setzero_si128();

  assert(N % 64 == 0);

  r1 += N;
  d += N;
  m += N;

  do {
    const __m128i v_r0_w = xx_load_128(r1 + n);
    const __m128i v_r1_w = xx_load_128(r1 + n8);
    const __m128i v_d0_w = xx_load_128(d + n);
    const __m128i v_d1_w = xx_load_128(d + n8);
    const __m128i v_m01_b = xx_load_128(m + n);

    const __m128i v_rd0l_w = _mm_unpacklo_epi16(v_d0_w, v_r0_w);
    const __m128i v_rd0h_w = _mm_unpackhi_epi16(v_d0_w, v_r0_w);
    const __m128i v_rd1l_w = _mm_unpacklo_epi16(v_d1_w, v_r1_w);
    const __m128i v_rd1h_w = _mm_unpackhi_epi16(v_d1_w, v_r1_w);
    const __m128i v_m0_w = _mm_unpacklo_epi8(v_m01_b, _mm_setzero_si128());
    const __m128i v_m1_w = _mm_unpackhi_epi8(v_m01_b, _mm_setzero_si128());

    const __m128i v_m0l_w = _mm_unpacklo_epi16(v_m0_w, v_mask_max_w);
    const __m128i v_m0h_w = _mm_unpackhi_epi16(v_m0_w, v_mask_max_w);
    const __m128i v_m1l_w = _mm_unpacklo_epi16(v_m1_w, v_mask_max_w);
    const __m128i v_m1h_w = _mm_unpackhi_epi16(v_m1_w, v_mask_max_w);

    const __m128i v_t0l_d = _mm_madd_epi16(v_rd0l_w, v_m0l_w);
    const __m128i v_t0h_d = _mm_madd_epi16(v_rd0h_w, v_m0h_w);
    const __m128i v_t1l_d = _mm_madd_epi16(v_rd1l_w, v_m1l_w);
    const __m128i v_t1h_d = _mm_madd_epi16(v_rd1h_w, v_m1h_w);

    const __m128i v_t0_w = _mm_packs_epi32(v_t0l_d, v_t0h_d);
    const __m128i v_t1_w = _mm_packs_epi32(v_t1l_d, v_t1h_d);

    const __m128i v_sq0_d = _mm_madd_epi16(v_t0_w, v_t0_w);
    const __m128i v_sq1_d = _mm_madd_epi16(v_t1_w, v_t1_w);

    const __m128i v_sum0_q = _mm_add_epi64(_mm_and_si128(v_sq0_d, v_zext_q),
                                           _mm_srli_epi64(v_sq0_d, 32));
    const __m128i v_sum1_q = _mm_add_epi64(_mm_and_si128(v_sq1_d, v_zext_q),
                                           _mm_srli_epi64(v_sq1_d, 32));

    v_acc0_q = _mm_add_epi64(v_acc0_q, v_sum0_q);
    v_acc0_q = _mm_add_epi64(v_acc0_q, v_sum1_q);

    n8 += 16;
    n += 16;
  } while (n);

  v_acc0_q = _mm_add_epi64(v_acc0_q, _mm_srli_si128(v_acc0_q, 8));

#if ARCH_X86_64
  csse = (uint64_t)_mm_cvtsi128_si64(v_acc0_q);
#else
  xx_storel_64(&csse, v_acc0_q);
#endif

  return ROUND_POWER_OF_TWO(csse, 2 * WEDGE_WEIGHT_BITS);
}