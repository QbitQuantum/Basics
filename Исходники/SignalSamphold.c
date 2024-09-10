hv_size_t sSamphold_init(SignalSamphold *o) {
#if HV_SIMD_AVX
    o->s = _mm256_setzero_ps();
#elif HV_SIMD_SSE
    o->s = _mm_setzero_ps();
#elif HV_SIMD_NEON
    o->s = vdupq_n_f32(0.0f);
#else
    o->s = 0.0f;
#endif
    return 0;
}