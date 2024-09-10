    MEMALIGN(16, __m128i mod_mask);
    MEMALIGN(16, __m128 res);
    MEMALIGN(16, static const unsigned int mult  [4]) = {214013, 17405, 214013, 69069};
    MEMALIGN(16, static const unsigned int gadd  [4]) = {2531011, 10395331, 13737667, 1};
    MEMALIGN(16, static const unsigned int mask  [4]) = {0xFFFFFFFF, 0, 0xFFFFFFFF, 0};

    adder          = _mm_load_si128((__m128i*)gadd);
    multiplier     = _mm_load_si128((__m128i*)mult);
    mod_mask       = _mm_load_si128((__m128i*)mask);
    cur_seed_split = _mm_shuffle_epi32(m_sseSeed, _MM_SHUFFLE(2, 3, 0, 1));

    m_sseSeed      = _mm_mul_epu32(m_sseSeed, multiplier);
    multiplier     = _mm_shuffle_epi32(multiplier, _MM_SHUFFLE(2, 3, 0, 1));
    cur_seed_split = _mm_mul_epu32(cur_seed_split, multiplier);

    m_sseSeed      = _mm_and_si128(m_sseSeed, mod_mask);
    cur_seed_split = _mm_and_si128(cur_seed_split, mod_mask);
    cur_seed_split = _mm_shuffle_epi32(cur_seed_split, _MM_SHUFFLE(2, 3, 0, 1));
    m_sseSeed      = _mm_or_si128(m_sseSeed, cur_seed_split);
    m_sseSeed      = _mm_add_epi32(m_sseSeed, adder);

    /* adjust the value to the range requested */
    res = _mm_cvtepi32_ps(m_sseSeed);
    if (sseresult)
      *sseresult = _mm_mul_ps(res, f);
    else
    {
      res = _mm_mul_ps(res, f);
      _mm_storeu_ps(result, res);

      /* returning a float array, so cleanup */