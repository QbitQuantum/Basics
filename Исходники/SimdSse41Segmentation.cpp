 SIMD_INLINE bool ColsHasIndex(const uint8_t * mask, size_t stride, size_t size, __m128i index, uint8_t * cols)
 {
     __m128i _cols = _mm_setzero_si128();
     for (size_t row = 0; row < size; ++row)
     {
         _cols = _mm_or_si128(_cols, _mm_cmpeq_epi8(_mm_loadu_si128((__m128i*)mask), index));
         mask += stride;
     }
     _mm_storeu_si128((__m128i*)cols, _cols);
     return !_mm_testz_si128(_cols, K_INV_ZERO);
 }