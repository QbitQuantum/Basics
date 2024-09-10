static void
TEST (void)
{
  union128i_q u, s;
  long long e[2] = {0};
  unsigned long long tmp;
  int i;
 
  s.x = _mm_set_epi64x (-1, 0xf);

  u.x = test (s.x);

  if (N < 64)
    for (i = 0; i < 2; i++) {
      tmp = s.a[i]; 
      e[i] = tmp >> N;
    }

  if (check_union128i_q (u, e))
    abort (); 
}