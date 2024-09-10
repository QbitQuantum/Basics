void static
avx_test (void)
{
  int i;
  long long m[4] = {mask_v(0), mask_v(1), mask_v(2), mask_v(3)};
  double s[4] = {1.1, 2.2, 3.3, 4.4};
  union256d u;
  union256i_q mask;
  double e [4] = {0.0};

  mask.x = _mm256_loadu_si256 ((__m256i *)m);
  u.x = _mm256_maskload_pd (s, mask.x);

  for (i = 0 ; i < 4; i++) 
    e[i] = m[i] ? s[i] : 0;
   
  if (check_union256d (u, e))
    abort ();
}