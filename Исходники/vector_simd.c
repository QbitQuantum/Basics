/* Modified from volk_32f_s32f_convert_16i_a_simd2. Removed clipping */
void srslte_vec_convert_fi_simd(float *x, int16_t *z, float scale, uint32_t len)
{
#ifdef LV_HAVE_SSE
  unsigned int number = 0;

  const unsigned int eighthPoints = len / 8;

  const float* inputVectorPtr = (const float*)x;
  int16_t* outputVectorPtr = z;

  __m128 vScalar = _mm_set_ps1(scale);
  __m128 inputVal1, inputVal2;
  __m128i intInputVal1, intInputVal2;
  __m128 ret1, ret2;

  for(;number < eighthPoints; number++){
    inputVal1 = _mm_load_ps(inputVectorPtr); inputVectorPtr += 4;
    inputVal2 = _mm_load_ps(inputVectorPtr); inputVectorPtr += 4;

    ret1 = _mm_mul_ps(inputVal1, vScalar);
    ret2 = _mm_mul_ps(inputVal2, vScalar);

    intInputVal1 = _mm_cvtps_epi32(ret1);
    intInputVal2 = _mm_cvtps_epi32(ret2);

    intInputVal1 = _mm_packs_epi32(intInputVal1, intInputVal2);

    _mm_store_si128((__m128i*)outputVectorPtr, intInputVal1);
    outputVectorPtr += 8;
  }

  number = eighthPoints * 8;
  for(; number < len; number++){
    z[number] = (int16_t) (x[number] * scale);
  }
#endif
}