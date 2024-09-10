static void
TEST (void)
{
  union128i_w u, s1, s2;
  short e[8];
  int i;
   
  s1.x = _mm_set_epi16 (1,2,3,4,5,6,7,8);
  s2.x = _mm_set_epi16 (8,7,6,5,4,3,2,1);
  u.x = test (s1.x, s2.x);

  for (i=0; i<8; i++)
    e[i] = s1.a[i]>s2.a[i]?s1.a[i]:s2.a[i]; 

  if (check_union128i_w (u, e))
    abort ();
}