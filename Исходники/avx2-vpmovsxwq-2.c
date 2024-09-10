static void
avx2_test (void)
{
  union128i_w s;
  union256i_q res;
  long long int res_ref[4];

  s.x = _mm_set_epi16 (1, 2, 3, 4, -200, 50, 6, 8);

  res.x = _mm256_cvtepi16_epi64 (s.x);

  compute_movsxwq (s.a, res_ref);

  if (check_union256i_q (res, res_ref))
    abort ();
}