void avg (int simd, uint8_t *src , uint8_t *src2, uint8_t *dst) {
  if (simd) {
    (*(__m128i*)dst) = _mm_avg_epu8((*(__m128i*)src), (*(__m128i*)src2));
  }
  else {
    int size = 16;
    while (size) {
      *dst = ((*src)+(*src2))/2;
      src++; src2++; dst++; size--;
    }
  }
}