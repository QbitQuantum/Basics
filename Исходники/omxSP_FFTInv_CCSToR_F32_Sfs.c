// Sse version of RevbinPermuteInv function.
static void RevbinPermuteInvSse(const OMX_F32 *in,
                                OMX_F32 *out,
                                const OMX_F32 *twiddle,
                                OMX_INT n) {
  OMX_INT i;
  OMX_INT j;
  OMX_INT n_by_2 = n >> 1;
  OMX_INT n_by_4 = n >> 2;
  const OMX_F32 *tw;
  const OMX_F32 *pi;
  const OMX_F32 *pj;

  VC v_i;
  VC v_j;
  VC v_big_a;
  VC v_big_b;
  VC v_temp;
  VC v_tw;

  for (i = 0, j = n_by_2 - 3; i < n_by_4; i += 4, j -= 4) {
    pi = in + (i << 1);
    pj = in + (j << 1);
    VC_LOAD_INTERLEAVE(&v_i, pi);

    v_j.real = _mm_set_ps(pj[0], pj[2], pj[4], pj[6]);
    v_j.imag = _mm_set_ps(pj[1], pj[3], pj[5], pj[7]);

    // A[k] = (X[k] + X'[N/2 - k])
    VC_ADD_SUB(&v_big_a, &v_i, &v_j);

    // temp = (X[k] - X'[N/2 - k])
    VC_SUB_ADD(&v_temp, &v_i, &v_j);

    // W[k]
    tw = twiddle + i;
    VC_LOAD_SPLIT(&v_tw, tw, n);

    // B[k] = (X[k] - X'[N/2 - k]) * W[k]
    VC_CONJ_MUL(&v_big_b, &v_temp, &v_tw);

    // Convert split format to interleaved format.
    // Z[k] = (A[k] + j * B[k]) (k = 0, ..., N/2 - 1)
    // The scaling of 1/2 will be merged into to the scaling in
    // the last step before the output in omxSP_FFTInv_CCSToR_F32_Sfs.
    VC_ADD_X_STORE_SPLIT((out + i), &v_big_a, &v_big_b, n_by_2);

    VC_SUB_X_INVERSE_STOREU_SPLIT((out + j), &v_big_a, &v_big_b, n_by_2);
  }

  // The n_by_2 complex point
  out[n_by_4] = 2.0f * in[n_by_2];
  out[n_by_4 + n_by_2] = -2.0f * in[n_by_2 + 1];

  // The first complex point
  out[0] = in[0] + in[n];
  out[n_by_2] = in[0] - in[n];
}