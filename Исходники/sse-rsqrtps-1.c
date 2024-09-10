static void
TEST (void)
{
  union128 u, s1;
  float e[4];
  int i;
   
  s1.x = _mm_set_ps (24.43, 68.346, 43.35, 546.46);
  u.x = test (s1.x); 
  
  for (i = 0; i < 4; i++)
    {
      __m128 tmp = _mm_load_ss (&s1.a[i]);
      tmp = _mm_rsqrt_ss (tmp);
      _mm_store_ss (&e[i], tmp);
    }

  if (check_union128 (u, e))
    abort ();
}