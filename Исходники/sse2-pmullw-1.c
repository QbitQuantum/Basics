static void
TEST (void)
{
  union128i_w u, s1, s2;
  short e[8];
  int i, tmp;
   
  s1.x = _mm_set_epi16 (10,2067,-3033,90,80,40,-1000,15);
  s2.x = _mm_set_epi16 (11, 9834, 7444, -10222, 34, -7833, 39, 14);
  u.x = test (s1.x, s2.x); 
   
  for (i = 0; i < 8; i++)
    {
      tmp = s1.a[i] * s2.a[i];
    
      e[i] = tmp;
    }

  if (check_union128i_w (u, e))
    abort ();
}