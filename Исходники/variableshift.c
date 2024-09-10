size_t variablevectorshift(uint32_t *array, size_t length, int shiftamount) {
  size_t k = 0;
  __m256i * a = (__m256i *) array;
  __m256i s = _mm256_set1_epi32(shiftamount);
  for (; k  < length / 8 ; k ++, a++) {
    __m256i v = _mm256_loadu_si256(a);
    v = _mm256_srlv_epi32(v,s);
     _mm256_storeu_si256(a,v);
  }
  k *= 8;
  for (; k < length; ++k) {
    array[k] = array[k] >> shiftamount;
  }
  return 0;
}