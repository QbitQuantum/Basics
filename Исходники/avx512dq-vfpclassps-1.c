void extern
avx512dq_test (void)
{
  m16 = _mm512_fpclass_ps_mask (x512, 13);
  m8 = _mm256_fpclass_ps_mask (x256, 13);
  m8 = _mm_fpclass_ps_mask (x128, 13);
  m16 = _mm512_mask_fpclass_ps_mask (2, x512, 13);
  m8 = _mm256_mask_fpclass_ps_mask (2, x256, 13);
  m8 = _mm_mask_fpclass_ps_mask (2, x128, 13);
}