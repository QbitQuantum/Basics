static void
avx2_test (void)
{
  union128i_d s;
  union256i_q res;
  long long int res_ref[4];

  s.x = _mm_set_epi32 (1, 2, 3, 4);

  res.x = _mm256_cvtepu32_epi64 (s.x);

  compute_movzxdq (s.a, res_ref);

  if (check_union256i_q (res, res_ref))
    abort ();
}