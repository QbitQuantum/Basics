void extern
avx512vl_test (void)
{
  _mm256_i64scatter_pd (addr, idx1, src1, 8);
  _mm256_mask_i64scatter_pd (addr, m8, idx1, src1, 8);

  _mm_i64scatter_pd (addr, idx2, src2, 8);
  _mm_mask_i64scatter_pd (addr, m8, idx2, src2, 8);
}