static void
TEST (void)
{
  union128i_w u, s;
  union128i_q c;
  short e[8] = {0};
  int i;
 
  s.x = _mm_set_epi16 (1, -2, 3, 4, 5, 6, -0x7000, 0x9000);
  c.x = _mm_set_epi64x (12, 13);

  u.x = test (s.x, c.x);

  if (c.a[0] < 16)
    for (i = 0; i < 8; i++)
      e[i] = s.a[i] >> c.a[0]; 

  if (check_union128i_w (u, e))
    abort (); 
}