void sEnv_process(HvBase *_c, SignalEnvelope *o, hv_bInf_t bIn,
		void (*sendMessage)(HvBase *, int, const HvMessage *)) {
#if HV_SIMD_AVX
  _mm256_stream_ps(o->buffer+o->numSamplesInBuffer, _mm256_mul_ps(bIn,bIn)); // store bIn^2, no need to cache block
  o->numSamplesInBuffer += HV_N_SIMD;

  if (o->numSamplesInBuffer >= o->windowSize) {
    int n4 = o->windowSize & ~HV_N_SIMD_MASK;
    __m256 sum = _mm256_setzero_ps();
    while (n4) {
      __m256 x = _mm256_load_ps(o->buffer + n4 - HV_N_SIMD);
      __m256 h = _mm256_load_ps(o->hanningWeights + n4 - HV_N_SIMD);
      x = _mm256_mul_ps(x, h);
      sum = _mm256_add_ps(sum, x);
      n4 -= HV_N_SIMD;
    }
    sum = _mm256_hadd_ps(sum,sum); // horizontal sum
    sum = _mm256_hadd_ps(sum,sum);
    sEnv_sendMessage(_c, o, sum[0]+sum[4], sendMessage); // updates numSamplesInBuffer
  }
#elif HV_SIMD_SSE
  _mm_stream_ps(o->buffer+o->numSamplesInBuffer, _mm_mul_ps(bIn,bIn)); // store bIn^2, no need to cache block
  o->numSamplesInBuffer += HV_N_SIMD;

  if (o->numSamplesInBuffer >= o->windowSize) {
    int n4 = o->windowSize & ~HV_N_SIMD_MASK;
    __m128 sum = _mm_setzero_ps();
    while (n4) {
      __m128 x = _mm_load_ps(o->buffer + n4 - HV_N_SIMD);
      __m128 h = _mm_load_ps(o->hanningWeights + n4 - HV_N_SIMD);
      x = _mm_mul_ps(x, h);
      sum = _mm_add_ps(sum, x);
      n4 -= HV_N_SIMD;
    }
    sum = _mm_hadd_ps(sum,sum); // horizontal sum
    sum = _mm_hadd_ps(sum,sum);
    sEnv_sendMessage(_c, o, sum[0], sendMessage);
  }
#elif HV_SIMD_NEON
  vst1q_f32(o->buffer+o->numSamplesInBuffer, vmulq_f32(bIn,bIn)); // store bIn^2, no need to cache block
  o->numSamplesInBuffer += HV_N_SIMD;

  if (o->numSamplesInBuffer >= o->windowSize) {
    int n4 = o->windowSize & ~HV_N_SIMD_MASK;
    float32x4_t sum = vdupq_n_f32(0.0f);
    while (n4) {
      float32x4_t x = vld1q_f32(o->buffer + n4 - HV_N_SIMD);
      float32x4_t h = vld1q_f32(o->hanningWeights + n4 - HV_N_SIMD);
      x = vmulq_f32(x, h);
      sum = vaddq_f32(sum, x);
      n4 -= HV_N_SIMD;
    }
    sEnv_sendMessage(_c, o, sum[0]+sum[1]+sum[2]+sum[3], sendMessage);
  }
#else // HV_SIMD_NONE
  o->buffer[o->numSamplesInBuffer] = (bIn*bIn);
  o->numSamplesInBuffer += HV_N_SIMD;

  if (o->numSamplesInBuffer >= o->windowSize) {
    float sum = 0.0f;
    for (int i = 0; i < o->windowSize; ++i) {
      sum += (o->hanningWeights[i] * o->buffer[i]);
    }
    sEnv_sendMessage(_c, o, sum, sendMessage);
  }
#endif
}