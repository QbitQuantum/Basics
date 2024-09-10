static void
TEST (void)
{
  union128i_b u, s1, s2;
  char e[16];
  int i;
   
  s1.x = _mm_set_epi8 (1,2,3,4,10,20,30,90,-80,-40,-100,-15,98, 25, 98,7);
  s2.x = _mm_set_epi8 (88, 44, 33, 22, 11, 98, 76, -100, -34, -78, -39, 6, 3, 4, 5, 119);
  u.x = test (s1.x, s2.x); 
   
  for (i = 0; i < 16; i++)
     e[i] = s1.a[i] + s2.a[i];

  if (check_union128i_b (u, e))
    abort ();
}