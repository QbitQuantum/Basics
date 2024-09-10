void extern
avx2_test (void)
{
  x = _mm_mask_i32gather_epi32 (x, base, idx, x, 1);
}