__attribute__((noinline)) float dot512fma2(float *x1, float *x2, size_t len) {
  assert(len % 32 == 0);
  __m512 sum = _mm512_setzero_ps();
  if (len > 31) {
    size_t limit = len - 31;
    for (size_t i = 0; i < limit; i += 32) {

      __m512 v11 = _mm512_loadu_ps(x1 + i);
      __m512 v21 = _mm512_loadu_ps(x2 + i);
      __m512 v12 = _mm512_loadu_ps(x1 + i + 16);
      __m512 v22 = _mm512_loadu_ps(x2 + i + 16);
      sum = _mm512_fmadd_ps(v11, v21, sum);
      sum = _mm512_fmadd_ps(v12, v22, sum);
    }
  }
  float buffer[16];
  _mm512_storeu_ps(buffer, sum);
  return buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] +
         buffer[6] + buffer[7] + buffer[8] + buffer[9] + buffer[10] +
         buffer[11] + buffer[12] + buffer[13] + buffer[14] + buffer[15];
}