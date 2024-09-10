void sDel1_onMessage(HvBase *_c, SignalDel1 *o, int letIn, const HvMessage *m) {
  if (letIn == 2) {
    if (msg_compareSymbol(m, 0, "clear")) {
#if HV_SIMD_AVX
      o->x = _mm256_setzero_ps();
#elif HV_SIMD_SSE
      o->x = _mm_setzero_ps();
#elif HV_SIMD_NEON
      o->x = vdupq_n_f32(0.0f);
#else
      o->x = 0.0f;
#endif
    }
  }
}