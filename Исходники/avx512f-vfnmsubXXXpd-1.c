void extern
avx512f_test (void)
{
  x1 = _mm512_fnmsub_pd (x1, x2, x3);
  x1 = _mm512_mask_fnmsub_pd (x1, m, x2, x3);
  x3 = _mm512_mask3_fnmsub_pd (x1, x2, x3, m);
  x1 = _mm512_maskz_fnmsub_pd (m, x1, x2, x3);
  x1 = _mm512_fnmsub_round_pd (x1, x2, x3, _MM_FROUND_TO_NEAREST_INT);
  x1 = _mm512_mask_fnmsub_round_pd (x1, m, x2, x3, _MM_FROUND_TO_NEG_INF);
  x3 = _mm512_mask3_fnmsub_round_pd (x1, x2, x3, m, _MM_FROUND_TO_POS_INF);
  x1 = _mm512_maskz_fnmsub_round_pd (m, x1, x2, x3, _MM_FROUND_TO_ZERO);
}