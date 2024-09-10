void static
avx_test (void)
{
  union256d u;
  double e [4] __attribute__ ((aligned (32))) = {0.0};

  u.x = _mm256_set_pd (39578.467285, 7856.342941, 85632.783567, 47563.234215);

  test (e, u.x);

  if (check_union256d (u, e))
    abort ();
}