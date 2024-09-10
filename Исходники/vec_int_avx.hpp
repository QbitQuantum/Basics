 __m256 convert_to_float(void) const
 {
     return _mm256_cvtepi32_ps(data_);
 }