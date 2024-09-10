__m256 exp_256(
  const __m256& x) {

  //! Clip the value
  __m256 y = _mm256_max_ps(_mm256_min_ps(x, _mm256_set1_ps(88.3762626647949f)),
                                            _mm256_set1_ps(-88.3762626647949f));

  //! Express exp(x) as exp(g + n * log(2))
  __m256 fx = y * _mm256_set1_ps(1.44269504088896341) + _mm256_set1_ps(0.5f);

  //! Floor
  const __m256 tmp = _mm256_round_ps(fx, _MM_FROUND_TO_ZERO);

  //! If greater, substract 1
  const __m256 mask = _mm256_and_ps(_mm256_cmp_ps(tmp, fx, _CMP_GT_OS),
                                    _mm256_set1_ps(1.f));
  fx = tmp - mask;

  y -= fx * _mm256_set1_ps(0.693359375 - 2.12194440e-4);
  const __m256 z = y * y;


  const __m256 t = (((((_mm256_set1_ps(1.9875691500E-4)  * y +
                        _mm256_set1_ps(1.3981999507E-3)) * y +
                        _mm256_set1_ps(8.3334519073E-3)) * y +
                        _mm256_set1_ps(4.1665795894E-2)) * y +
                        _mm256_set1_ps(1.6666665459E-1)) * y +
                        _mm256_set1_ps(5.0000001201E-1)) * z + y +
                        _mm256_set1_ps(1.f);

  //! Build 2^n (split it into two SSE array, since AVX2 equivalent functions
  //! aren't available.
  const __m128i emm0 = _mm_add_epi32(_mm_cvttps_epi32(_mm256_castps256_ps128(fx)), _mm_set1_epi32(0x7f));
  const __m128i emm1 = _mm_add_epi32(_mm_cvttps_epi32(_mm256_extractf128_ps(fx, 1)), _mm_set1_epi32(0x7f));

  fx = _mm256_castps128_ps256(_mm_castsi128_ps(_mm_slli_epi32(emm0, 23)));
  fx = _mm256_insertf128_ps(fx, _mm_castsi128_ps(_mm_slli_epi32(emm1, 23)), 1);

  //! Return the result
  return t * fx;
}