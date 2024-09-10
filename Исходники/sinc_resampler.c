static void process_sinc(rarch_sinc_resampler_t *resamp, float *out_buffer)
{
    unsigned i;
    __m256 sum_l             = _mm256_setzero_ps();
    __m256 sum_r             = _mm256_setzero_ps();

    const float *buffer_l    = resamp->buffer_l + resamp->ptr;
    const float *buffer_r    = resamp->buffer_r + resamp->ptr;

    unsigned taps            = resamp->taps;
    unsigned phase           = resamp->time >> SUBPHASE_BITS;
#if SINC_COEFF_LERP
    const float *phase_table = resamp->phase_table + phase * taps * 2;
    const float *delta_table = phase_table + taps;
    __m256 delta             = _mm256_set1_ps((float)
                               (resamp->time & SUBPHASE_MASK) * SUBPHASE_MOD);
#else
    const float *phase_table = resamp->phase_table + phase * taps;
#endif

    for (i = 0; i < taps; i += 8)
    {
        __m256 buf_l  = _mm256_loadu_ps(buffer_l + i);
        __m256 buf_r  = _mm256_loadu_ps(buffer_r + i);

#if SINC_COEFF_LERP
        __m256 deltas = _mm256_load_ps(delta_table + i);
        __m256 sinc   = _mm256_add_ps(_mm256_load_ps(phase_table + i),
                                      _mm256_mul_ps(deltas, delta));
#else
        __m256 sinc   = _mm256_load_ps(phase_table + i);
#endif
        sum_l         = _mm256_add_ps(sum_l, _mm256_mul_ps(buf_l, sinc));
        sum_r         = _mm256_add_ps(sum_r, _mm256_mul_ps(buf_r, sinc));
    }

    /* hadd on AVX is weird, and acts on low-lanes
     * and high-lanes separately. */
    __m256 res_l = _mm256_hadd_ps(sum_l, sum_l);
    __m256 res_r = _mm256_hadd_ps(sum_r, sum_r);
    res_l        = _mm256_hadd_ps(res_l, res_l);
    res_r        = _mm256_hadd_ps(res_r, res_r);
    res_l        = _mm256_add_ps(_mm256_permute2f128_ps(res_l, res_l, 1), res_l);
    res_r        = _mm256_add_ps(_mm256_permute2f128_ps(res_r, res_r, 1), res_r);

    /* This is optimized to mov %xmmN, [mem].
     * There doesn't seem to be any _mm256_store_ss intrinsic. */
    _mm_store_ss(out_buffer + 0, _mm256_extractf128_ps(res_l, 0));
    _mm_store_ss(out_buffer + 1, _mm256_extractf128_ps(res_r, 0));
}