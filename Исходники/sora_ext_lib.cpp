// Multiply the first source vector by the conjugate of the second source vector
// ie. re + j * im = a * conj(b)
//Return by reference for performance
FORCE_INLINE
int __ext_v_conj_mul_complex16(struct complex16* out, int lenout,
                struct complex16* x, int len1,
                struct complex16* y, int len2, int shift){
  const unum8 wlen = 4;// sizeof(vcs) / sizeof(complex16);
  const __m128i xmm6 = _mm_set1_epi32(0x0000FFFF);
  const __m128i xmm5 = _mm_set1_epi32(0xFFFF0000);
  const __m128i xmm4 = _mm_set1_epi32(0x00010000);

  __m128i* Xs = (__m128i*) x;
  __m128i* Ys = (__m128i*) y;
  __m128i* Outs = (__m128i*) out;
  for (int i = 0; i < len1 / wlen; i++){
    __m128i mx = _mm_loadu_si128(&Xs[i]);
    __m128i my = _mm_loadu_si128(&Ys[i]);

    __m128i ms2 = _mm_xor_si128(my, xmm5);
    ms2 = _mm_add_epi32(ms2, xmm4);

    ms2 = _mm_shufflehi_epi16(ms2, _MM_SHUFFLE(2, 3, 0, 1));
    ms2 = _mm_shufflelo_epi16(ms2, _MM_SHUFFLE(2, 3, 0, 1));

    __m128i mre = _mm_srai_epi32(_mm_madd_epi16(my, mx), shift);
    __m128i mim = _mm_srai_epi32(_mm_madd_epi16(ms2, mx), shift);

    mre = _mm_and_si128(mre, xmm6);
    mim = _mm_and_si128(mim, xmm6);

    mim = _mm_slli_epi32(mim, 0x10);

    _mm_storeu_si128(&Outs[i], _mm_or_si128(mre, mim));
  }

  for (int i = (len1 / wlen) * wlen; i < len1; i++){
    out[i].re = (x[i].re * y[i].re + x[i].im * y[i].im) >> shift;
    out[i].im = (x[i].im * y[i].re - x[i].re * y[i].im) >> shift;
  }

  return 0;
}