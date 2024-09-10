void static
avx_test (void)
{
  union256 u, s1, s2;
  float e [8];

  s1.x = _mm256_set_ps (1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8);
  s2.x = _mm256_set_ps (2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8);
  u.x = _mm256_shuffle_ps (s1.x, s2.x, MASK);


  e[0] = select4(s1.a,   (MASK >> 0) & 0x3);
  e[1] = select4(s1.a,   (MASK >> 2) & 0x3);
  e[2] = select4(s2.a,   (MASK >> 4) & 0x3);
  e[3] = select4(s2.a,   (MASK >> 6) & 0x3);
  e[4] = select4(s1.a+4, (MASK >> 0) & 0x3);
  e[5] = select4(s1.a+4, (MASK >> 2) & 0x3);
  e[6] = select4(s2.a+4, (MASK >> 4) & 0x3);
  e[7] = select4(s2.a+4, (MASK >> 6) & 0x3);

  if (check_union256 (u, e))
    abort ();
}