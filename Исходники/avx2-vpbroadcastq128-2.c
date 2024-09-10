static void
avx2_test (void)
{
  union128i_q src, dst;
  long long int dst_ref[2];
  int i;

  for (i = 0; i < NUM; i++)
    {
      init_pbroadcastq128 (src.a, i);

      dst.x = _mm_broadcastq_epi64 (src.x);
      calc_pbroadcastq128 (src.a, dst_ref);

      if (check_union128i_q (dst, dst_ref))
	abort ();
    }
}