// This function handles the case when set_count = 2, in which we cannot
// unroll the set loop by 4 to meet the SSE requirement (4 elements).
static void InternalUnroll2Inv(
    const OMX_F32 *in,
    OMX_F32 *out,
    const OMX_F32 *twiddle,
    OMX_INT n) {
  OMX_INT i;
  OMX_INT n_by_2 = n >> 1;
  OMX_INT n_by_4 = n >> 2;
  OMX_INT n_mul_2 = n << 1;
  OMX_F32 *out0 = out;

  for (i = 0; i < n_by_2; i += 8) {
    const OMX_F32 *tw1  = twiddle + i;
    const OMX_F32 *tw2  = tw1 + i;
    const OMX_F32 *tw3  = tw2 + i;
    const OMX_F32 *tw1e = tw1 + 4;
    const OMX_F32 *tw2e = tw2 + 8;
    const OMX_F32 *tw3e = tw3 + 12;

    VC v_tw1;
    VC v_tw2;
    VC v_tw3;
    VC v_t0;
    VC v_t1;
    VC v_t2;
    VC v_t3;
    VC v_t4;
    VC v_t5;
    VC v_t6;
    VC v_t7;

    v_tw1.real = _mm_shuffle_ps(_mm_load_ss(tw1),
                                _mm_load_ss(tw1e),
                                _MM_SHUFFLE(0, 0, 0, 0));
    v_tw1.imag = _mm_shuffle_ps(_mm_load_ss(tw1 + n_mul_2),
                                _mm_load_ss(tw1e + n_mul_2),
                                _MM_SHUFFLE(0, 0, 0, 0));
    v_tw2.real = _mm_shuffle_ps(_mm_load_ss(tw2),
                                _mm_load_ss(tw2e),
                                _MM_SHUFFLE(0, 0, 0, 0));
    v_tw2.imag = _mm_shuffle_ps(_mm_load_ss(tw2 + n_mul_2),
                                _mm_load_ss(tw2e + n_mul_2),
                                _MM_SHUFFLE(0, 0, 0, 0));
    v_tw3.real = _mm_shuffle_ps(_mm_load_ss(tw3),
                                _mm_load_ss(tw3e),
                                _MM_SHUFFLE(0, 0, 0, 0));
    v_tw3.imag = _mm_shuffle_ps(_mm_load_ss(tw3 + n_mul_2),
                                _mm_load_ss(tw3e + n_mul_2),
                                _MM_SHUFFLE(0, 0, 0, 0));

    __m128 xmm0;
    __m128 xmm1;
    __m128 xmm2;
    __m128 xmm3;
    __m128 xmm4;
    __m128 xmm5;
    __m128 xmm6;
    __m128 xmm7;

    const OMX_F32 *in0 = in + (i << 1);
    xmm0 = _mm_load_ps(in0);
    xmm1 = _mm_load_ps(in0 + 4);
    xmm2 = _mm_load_ps(in0 + 8);
    xmm3 = _mm_load_ps(in0 + 12);
    v_t0.real = _mm_shuffle_ps(xmm0, xmm2, _MM_SHUFFLE(1, 0, 1, 0));
    v_t1.real = _mm_shuffle_ps(xmm0, xmm2, _MM_SHUFFLE(3, 2, 3, 2));
    v_t2.real = _mm_shuffle_ps(xmm1, xmm3, _MM_SHUFFLE(1, 0, 1, 0));
    v_t3.real = _mm_shuffle_ps(xmm1, xmm3, _MM_SHUFFLE(3, 2, 3, 2));

    xmm4 = _mm_load_ps(in0 + n);
    xmm5 = _mm_load_ps(in0 + n + 4);
    xmm6 = _mm_load_ps(in0 + n + 8);
    xmm7 = _mm_load_ps(in0 + n + 12);
    v_t0.imag = _mm_shuffle_ps(xmm4, xmm6, _MM_SHUFFLE(1, 0, 1, 0));
    v_t1.imag = _mm_shuffle_ps(xmm4, xmm6, _MM_SHUFFLE(3, 2, 3, 2));
    v_t2.imag = _mm_shuffle_ps(xmm5, xmm7, _MM_SHUFFLE(1, 0, 1, 0));
    v_t3.imag = _mm_shuffle_ps(xmm5, xmm7, _MM_SHUFFLE(3, 2, 3, 2));

    OMX_F32 *out1 = out0 + n_by_4;
    OMX_F32 *out2 = out1 + n_by_4;
    OMX_F32 *out3 = out2 + n_by_4;

    RADIX4_INV_BUTTERFLY(&v_t4, &v_t5, &v_t6, &v_t7,
                         &v_tw1, &v_tw2, &v_tw3,
                         &v_t0, &v_t1, &v_t2, &v_t3);

    RADIX4_INV_BUTTERFLY_STORE(out0, out1, out2, out3,
                               &v_t4, &v_t5, &v_t6, &v_t7, n);

    out0 += 4;
  }
}