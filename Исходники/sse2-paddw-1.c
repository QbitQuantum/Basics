static void
TEST (void)
{
  union128i_w u, s1, s2;
  short e[8];
  int i;
   
  s1.x = _mm_set_epi16 (10,20,30,90,-80,-40,-100,-15);
  s2.x = _mm_set_epi16 (11, 98, 76, -100, -34, -78, -39, 14);
  u.x = test (s1.x, s2.x); 
   
  for (i = 0; i < 8; i++)
     e[i] = s1.a[i] + s2.a[i];

  if (check_union128i_w (u, e))
    abort ();
}