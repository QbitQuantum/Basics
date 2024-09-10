void extern
avx512f_test (void)
{
  m = _mm512_cmp_pd_mask (x, x, _CMP_FALSE_OQ);
  m = _mm512_mask_cmp_pd_mask (m, x, x, _CMP_FALSE_OQ);
  m = _mm512_cmp_round_pd_mask (x, x, _CMP_FALSE_OQ, _MM_FROUND_NO_EXC);
  m = _mm512_mask_cmp_round_pd_mask (m, x, x, _CMP_FALSE_OQ, _MM_FROUND_NO_EXC);

  m = _mm512_cmpeq_pd_mask (x, x);
  m = _mm512_mask_cmpeq_pd_mask (m, x, x);

  m = _mm512_cmplt_pd_mask (x, x);
  m = _mm512_mask_cmplt_pd_mask (m, x, x);

  m = _mm512_cmple_pd_mask (x, x);
  m = _mm512_mask_cmple_pd_mask (m, x, x);

  m = _mm512_cmpunord_pd_mask (x, x);
  m = _mm512_mask_cmpunord_pd_mask (m, x, x);

  m = _mm512_cmpneq_pd_mask (x, x);
  m = _mm512_mask_cmpneq_pd_mask (m, x, x);

  m = _mm512_cmpnlt_pd_mask (x, x);
  m = _mm512_mask_cmpnlt_pd_mask (m, x, x);

  m = _mm512_cmpnle_pd_mask (x, x);
  m = _mm512_mask_cmpnle_pd_mask (m, x, x);

  m = _mm512_cmpord_pd_mask (x, x);
  m = _mm512_mask_cmpord_pd_mask (m, x, x);
}