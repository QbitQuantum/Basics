static void
avx2_test (void)
{
  union256i_d src1, src2, dst;
  int dst_ref[8];
  int i;

  for (i = 0; i < NUM; i++)
    {
      init_permd (src1.a, src2.a, i);

      dst.x = _mm256_permutevar8x32_epi32 (src1.x, src2.x);
      calc_permd (src1.a, src2.a, dst_ref);

      if (check_union256i_d (dst, dst_ref))
	abort ();
    }
}