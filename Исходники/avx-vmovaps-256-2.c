void static
avx_test (void)
{
  union256 u;
  float e [8] __attribute__ ((aligned (32))) = {0.0};

  u.x = _mm256_set_ps (1.17, 24567.16, 3.15, 4567.14, 5.13, 65467.12, 788.11, 8.9);

  test (e, u.x);

  if (check_union256 (u, e))
    abort ();
}