static void
avx2_test (void)
{
  union256i_d src1, src2, dst;
  int dst_ref[8];
  int i;

  for (i = 0; i < NUM; i++)
    {
      init_pblendd256 (src1.a, src2.a, i);

      dst.x = _mm256_blend_epi32 (src1.x, src2.x, MASK);
      calc_pblendd256 (src1.a, src2.a, MASK, dst_ref);

      if (check_union256i_d (dst, dst_ref))
	abort ();
    }
}