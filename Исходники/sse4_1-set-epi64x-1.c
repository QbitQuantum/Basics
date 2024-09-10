test (unsigned long long *v)
{
  union
    {
      __m128i x;
      unsigned long long i[2];
    } u;
  unsigned int i;
  
  u.x = _mm_set_epi64x (v[1], v[0]);

  for (i = 0; i < sizeof (v) / sizeof (v[0]); i++)
    if (v[i] != u.i[i])
      {
#ifdef DEBUG
	printf ("%i: 0x%llx != 0x%llx\n", i, v[i], u.i[i]);
#endif
	abort ();
      }
}