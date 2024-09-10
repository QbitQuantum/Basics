static void
avx2_test (void)
{
  union128i_b s;
  union256i_w res;
  short res_ref[16];

  s.x = _mm_set_epi8 (1, 2, 3, 4, 200, 50, 6, 8, 1, 2, 3, 4, 200, 5, 6, 8);

  res.x = _mm256_cvtepu8_epi16 (s.x);

  compute_movzxbw (s.a, res_ref);

  if (check_union256i_w (res, res_ref))
    abort ();
}