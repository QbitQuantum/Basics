void extern
avx512dq_test (void)
{
  m8 = _mm_fpclass_sd_mask (x128, 13);
}