INLINE void    _mm256_maskstore_ps (float *ptr, __m256i mask, __m256 data) {
  _mm256_maskstore_ps(ptr, _mm256_castsi256_ps(mask), data);
}