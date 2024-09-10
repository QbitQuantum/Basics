static void cftmdl_128_SSE2(float* a) {
  const int l = 8;
  const __m128 mm_swap_sign = _mm_load_ps(k_swap_sign);
  int j0;

  __m128 wk1rv = _mm_load_ps(cftmdl_wk1r);
  for (j0 = 0; j0 < l; j0 += 2) {
    const __m128i a_00 = _mm_loadl_epi64((__m128i*)&a[j0 + 0]);
    const __m128i a_08 = _mm_loadl_epi64((__m128i*)&a[j0 + 8]);
    const __m128i a_32 = _mm_loadl_epi64((__m128i*)&a[j0 + 32]);
    const __m128i a_40 = _mm_loadl_epi64((__m128i*)&a[j0 + 40]);
    const __m128 a_00_32 = _mm_shuffle_ps(_mm_castsi128_ps(a_00),
                                          _mm_castsi128_ps(a_32),
                                          _MM_SHUFFLE(1, 0, 1, 0));
    const __m128 a_08_40 = _mm_shuffle_ps(_mm_castsi128_ps(a_08),
                                          _mm_castsi128_ps(a_40),
                                          _MM_SHUFFLE(1, 0, 1, 0));
    __m128 x0r0_0i0_0r1_x0i1 = _mm_add_ps(a_00_32, a_08_40);
    const __m128 x1r0_1i0_1r1_x1i1 = _mm_sub_ps(a_00_32, a_08_40);

    const __m128i a_16 = _mm_loadl_epi64((__m128i*)&a[j0 + 16]);
    const __m128i a_24 = _mm_loadl_epi64((__m128i*)&a[j0 + 24]);
    const __m128i a_48 = _mm_loadl_epi64((__m128i*)&a[j0 + 48]);
    const __m128i a_56 = _mm_loadl_epi64((__m128i*)&a[j0 + 56]);
    const __m128 a_16_48 = _mm_shuffle_ps(_mm_castsi128_ps(a_16),
                                          _mm_castsi128_ps(a_48),
                                          _MM_SHUFFLE(1, 0, 1, 0));
    const __m128 a_24_56 = _mm_shuffle_ps(_mm_castsi128_ps(a_24),
                                          _mm_castsi128_ps(a_56),
                                          _MM_SHUFFLE(1, 0, 1, 0));
    const __m128 x2r0_2i0_2r1_x2i1 = _mm_add_ps(a_16_48, a_24_56);
    const __m128 x3r0_3i0_3r1_x3i1 = _mm_sub_ps(a_16_48, a_24_56);

    const __m128 xx0 = _mm_add_ps(x0r0_0i0_0r1_x0i1, x2r0_2i0_2r1_x2i1);
    const __m128 xx1 = _mm_sub_ps(x0r0_0i0_0r1_x0i1, x2r0_2i0_2r1_x2i1);

    const __m128 x3i0_3r0_3i1_x3r1 = _mm_castsi128_ps(_mm_shuffle_epi32(
        _mm_castps_si128(x3r0_3i0_3r1_x3i1), _MM_SHUFFLE(2, 3, 0, 1)));
    const __m128 x3_swapped = _mm_mul_ps(mm_swap_sign, x3i0_3r0_3i1_x3r1);
    const __m128 x1_x3_add = _mm_add_ps(x1r0_1i0_1r1_x1i1, x3_swapped);
    const __m128 x1_x3_sub = _mm_sub_ps(x1r0_1i0_1r1_x1i1, x3_swapped);

    const __m128 yy0 =
        _mm_shuffle_ps(x1_x3_add, x1_x3_sub, _MM_SHUFFLE(2, 2, 2, 2));
    const __m128 yy1 =
        _mm_shuffle_ps(x1_x3_add, x1_x3_sub, _MM_SHUFFLE(3, 3, 3, 3));
    const __m128 yy2 = _mm_mul_ps(mm_swap_sign, yy1);
    const __m128 yy3 = _mm_add_ps(yy0, yy2);
    const __m128 yy4 = _mm_mul_ps(wk1rv, yy3);

    _mm_storel_epi64((__m128i*)&a[j0 + 0], _mm_castps_si128(xx0));
    _mm_storel_epi64(
        (__m128i*)&a[j0 + 32],
        _mm_shuffle_epi32(_mm_castps_si128(xx0), _MM_SHUFFLE(3, 2, 3, 2)));

    _mm_storel_epi64((__m128i*)&a[j0 + 16], _mm_castps_si128(xx1));
    _mm_storel_epi64(
        (__m128i*)&a[j0 + 48],
        _mm_shuffle_epi32(_mm_castps_si128(xx1), _MM_SHUFFLE(2, 3, 2, 3)));
    a[j0 + 48] = -a[j0 + 48];

    _mm_storel_epi64((__m128i*)&a[j0 + 8], _mm_castps_si128(x1_x3_add));
    _mm_storel_epi64((__m128i*)&a[j0 + 24], _mm_castps_si128(x1_x3_sub));

    _mm_storel_epi64((__m128i*)&a[j0 + 40], _mm_castps_si128(yy4));
    _mm_storel_epi64(
        (__m128i*)&a[j0 + 56],
        _mm_shuffle_epi32(_mm_castps_si128(yy4), _MM_SHUFFLE(2, 3, 2, 3)));
  }

  {
    int k = 64;
    int k1 = 2;
    int k2 = 2 * k1;
    const __m128 wk2rv = _mm_load_ps(&rdft_wk2r[k2 + 0]);
    const __m128 wk2iv = _mm_load_ps(&rdft_wk2i[k2 + 0]);
    const __m128 wk1iv = _mm_load_ps(&rdft_wk1i[k2 + 0]);
    const __m128 wk3rv = _mm_load_ps(&rdft_wk3r[k2 + 0]);
    const __m128 wk3iv = _mm_load_ps(&rdft_wk3i[k2 + 0]);
    wk1rv = _mm_load_ps(&rdft_wk1r[k2 + 0]);
    for (j0 = k; j0 < l + k; j0 += 2) {
      const __m128i a_00 = _mm_loadl_epi64((__m128i*)&a[j0 + 0]);
      const __m128i a_08 = _mm_loadl_epi64((__m128i*)&a[j0 + 8]);
      const __m128i a_32 = _mm_loadl_epi64((__m128i*)&a[j0 + 32]);
      const __m128i a_40 = _mm_loadl_epi64((__m128i*)&a[j0 + 40]);
      const __m128 a_00_32 = _mm_shuffle_ps(_mm_castsi128_ps(a_00),
                                            _mm_castsi128_ps(a_32),
                                            _MM_SHUFFLE(1, 0, 1, 0));
      const __m128 a_08_40 = _mm_shuffle_ps(_mm_castsi128_ps(a_08),
                                            _mm_castsi128_ps(a_40),
                                            _MM_SHUFFLE(1, 0, 1, 0));
      __m128 x0r0_0i0_0r1_x0i1 = _mm_add_ps(a_00_32, a_08_40);
      const __m128 x1r0_1i0_1r1_x1i1 = _mm_sub_ps(a_00_32, a_08_40);

      const __m128i a_16 = _mm_loadl_epi64((__m128i*)&a[j0 + 16]);
      const __m128i a_24 = _mm_loadl_epi64((__m128i*)&a[j0 + 24]);
      const __m128i a_48 = _mm_loadl_epi64((__m128i*)&a[j0 + 48]);
      const __m128i a_56 = _mm_loadl_epi64((__m128i*)&a[j0 + 56]);
      const __m128 a_16_48 = _mm_shuffle_ps(_mm_castsi128_ps(a_16),
                                            _mm_castsi128_ps(a_48),
                                            _MM_SHUFFLE(1, 0, 1, 0));
      const __m128 a_24_56 = _mm_shuffle_ps(_mm_castsi128_ps(a_24),
                                            _mm_castsi128_ps(a_56),
                                            _MM_SHUFFLE(1, 0, 1, 0));
      const __m128 x2r0_2i0_2r1_x2i1 = _mm_add_ps(a_16_48, a_24_56);
      const __m128 x3r0_3i0_3r1_x3i1 = _mm_sub_ps(a_16_48, a_24_56);

      const __m128 xx = _mm_add_ps(x0r0_0i0_0r1_x0i1, x2r0_2i0_2r1_x2i1);
      const __m128 xx1 = _mm_sub_ps(x0r0_0i0_0r1_x0i1, x2r0_2i0_2r1_x2i1);
      const __m128 xx2 = _mm_mul_ps(xx1, wk2rv);
      const __m128 xx3 =
          _mm_mul_ps(wk2iv,
                     _mm_castsi128_ps(_mm_shuffle_epi32(
                         _mm_castps_si128(xx1), _MM_SHUFFLE(2, 3, 0, 1))));
      const __m128 xx4 = _mm_add_ps(xx2, xx3);

      const __m128 x3i0_3r0_3i1_x3r1 = _mm_castsi128_ps(_mm_shuffle_epi32(
          _mm_castps_si128(x3r0_3i0_3r1_x3i1), _MM_SHUFFLE(2, 3, 0, 1)));
      const __m128 x3_swapped = _mm_mul_ps(mm_swap_sign, x3i0_3r0_3i1_x3r1);
      const __m128 x1_x3_add = _mm_add_ps(x1r0_1i0_1r1_x1i1, x3_swapped);
      const __m128 x1_x3_sub = _mm_sub_ps(x1r0_1i0_1r1_x1i1, x3_swapped);

      const __m128 xx10 = _mm_mul_ps(x1_x3_add, wk1rv);
      const __m128 xx11 = _mm_mul_ps(
          wk1iv,
          _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(x1_x3_add),
                                             _MM_SHUFFLE(2, 3, 0, 1))));
      const __m128 xx12 = _mm_add_ps(xx10, xx11);

      const __m128 xx20 = _mm_mul_ps(x1_x3_sub, wk3rv);
      const __m128 xx21 = _mm_mul_ps(
          wk3iv,
          _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(x1_x3_sub),
                                             _MM_SHUFFLE(2, 3, 0, 1))));
      const __m128 xx22 = _mm_add_ps(xx20, xx21);

      _mm_storel_epi64((__m128i*)&a[j0 + 0], _mm_castps_si128(xx));
      _mm_storel_epi64(
          (__m128i*)&a[j0 + 32],
          _mm_shuffle_epi32(_mm_castps_si128(xx), _MM_SHUFFLE(3, 2, 3, 2)));

      _mm_storel_epi64((__m128i*)&a[j0 + 16], _mm_castps_si128(xx4));
      _mm_storel_epi64(
          (__m128i*)&a[j0 + 48],
          _mm_shuffle_epi32(_mm_castps_si128(xx4), _MM_SHUFFLE(3, 2, 3, 2)));

      _mm_storel_epi64((__m128i*)&a[j0 + 8], _mm_castps_si128(xx12));
      _mm_storel_epi64(
          (__m128i*)&a[j0 + 40],
          _mm_shuffle_epi32(_mm_castps_si128(xx12), _MM_SHUFFLE(3, 2, 3, 2)));

      _mm_storel_epi64((__m128i*)&a[j0 + 24], _mm_castps_si128(xx22));
      _mm_storel_epi64(
          (__m128i*)&a[j0 + 56],
          _mm_shuffle_epi32(_mm_castps_si128(xx22), _MM_SHUFFLE(3, 2, 3, 2)));
    }
  }
}