TEST (void)
{
  union
    {
      __m128i x;
      long long ll[2];
    } val1;
  long long res[2];
  int masks[2];
  int i;

  val1.ll[0] = 0x0807060504030201LL;
  val1.ll[1] = 0x100F0E0D0C0B0A09LL;

  res[0] = _mm_extract_epi64 (val1.x, msk0);
  res[1] = _mm_extract_epi64 (val1.x, msk1);

  masks[0] = msk0;
  masks[1] = msk1;

  for (i = 0; i < 2; i++)
    if (res[i] != val1.ll [masks[i]])
      abort ();
}