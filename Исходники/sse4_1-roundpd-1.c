static void
TEST (void)
{
  union128d u, s;
  double e[2] = {0.0};
  int i;

  s.x = _mm_set_pd (1.1234, -2.3478);
  u.x = _mm_round_pd (s.x, iRoundMode);

  for (i = 0; i < 2; i++)
    {
      __m128d tmp = _mm_load_sd (&s.a[i]);
      tmp = _mm_round_sd (tmp, tmp, iRoundMode);
      _mm_store_sd (&e[i], tmp);
    }
  
  if (check_union128d (u, e))
    abort ();
} 