static int GetResidualCostSSE2(int ctx0, const VP8Residual* const res) {
  uint8_t levels[16], ctxs[16];
  uint16_t abs_levels[16];
  int n = res->first;
  // should be prob[VP8EncBands[n]], but it's equivalent for n=0 or 1
  const int p0 = res->prob[n][ctx0][0];
  CostArrayPtr const costs = res->costs;
  const uint16_t* t = costs[n][ctx0];
  // bit_cost(1, p0) is already incorporated in t[] tables, but only if ctx != 0
  // (as required by the syntax). For ctx0 == 0, we need to add it here or it'll
  // be missing during the loop.
  int cost = (ctx0 == 0) ? VP8BitCost(1, p0) : 0;

  if (res->last < 0) {
    return VP8BitCost(0, p0);
  }

  {   // precompute clamped levels and contexts, packed to 8b.
    const __m128i zero = _mm_setzero_si128();
    const __m128i kCst2 = _mm_set1_epi8(2);
    const __m128i kCst67 = _mm_set1_epi8(MAX_VARIABLE_LEVEL);
    const __m128i c0 = _mm_loadu_si128((const __m128i*)&res->coeffs[0]);
    const __m128i c1 = _mm_loadu_si128((const __m128i*)&res->coeffs[8]);
    const __m128i D0 = _mm_sub_epi16(zero, c0);
    const __m128i D1 = _mm_sub_epi16(zero, c1);
    const __m128i E0 = _mm_max_epi16(c0, D0);   // abs(v), 16b
    const __m128i E1 = _mm_max_epi16(c1, D1);
    const __m128i F = _mm_packs_epi16(E0, E1);
    const __m128i G = _mm_min_epu8(F, kCst2);    // context = 0,1,2
    const __m128i H = _mm_min_epu8(F, kCst67);   // clamp_level in [0..67]

    _mm_storeu_si128((__m128i*)&ctxs[0], G);
    _mm_storeu_si128((__m128i*)&levels[0], H);

    _mm_storeu_si128((__m128i*)&abs_levels[0], E0);
    _mm_storeu_si128((__m128i*)&abs_levels[8], E1);
  }
  for (; n < res->last; ++n) {
    const int ctx = ctxs[n];
    const int level = levels[n];
    const int flevel = abs_levels[n];   // full level
    cost += VP8LevelFixedCosts[flevel] + t[level];  // simplified VP8LevelCost()
    t = costs[n + 1][ctx];
  }
  // Last coefficient is always non-zero
  {
    const int level = levels[n];
    const int flevel = abs_levels[n];
    assert(flevel != 0);
    cost += VP8LevelFixedCosts[flevel] + t[level];
    if (n < 15) {
      const int b = VP8EncBands[n + 1];
      const int ctx = ctxs[n];
      const int last_p0 = res->prob[b][ctx][0];
      cost += VP8BitCost(0, last_p0);
    }
  }
  return cost;
}