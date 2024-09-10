void extern
avx512dq_test (void)
{
  m = _mm512_fpclass_pd_mask (x512, 13);
  m = _mm256_fpclass_pd_mask (x256, 13);
  m = _mm_fpclass_pd_mask (x128, 13);
  m = _mm512_mask_fpclass_pd_mask (2, x512, 13);
  m = _mm256_mask_fpclass_pd_mask (2, x256, 13);
  m = _mm_mask_fpclass_pd_mask (2, x128, 13);
}