// assume N is divisible by 4
uint32_t vectorsum(uint32_t * z, uint32_t N, uint32_t * accesses, uint32_t nmbr) {
  __m256i Nvec = _mm256_set1_epi32(N);
  __m128i sum = _mm_setzero_si128();
  for(uint32_t j = 0; j < nmbr ; j+=4) {
     __m256i fourints = _mm256_loadu_si256((const __m256i *)(accesses + j));
     __m256i four64bitsproducts =  _mm256_mul_epu32(fourints, Nvec);
     __m256i fourtop32ints = _mm256_srli_epi64(four64bitsproducts,32);
     __m128i four32ints = _mm256_i64gather_epi32 (z,fourtop32ints , 4);
     sum = _mm_add_epi32(sum, four32ints);
  }
  uint32_t buffer[4];
  _mm_storeu_si128((__m128i *)buffer,sum);
  return buffer[0] + buffer[1] + buffer[2] + buffer[3];
}