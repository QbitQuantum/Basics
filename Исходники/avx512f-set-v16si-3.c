foo_r (int x)
{
  return _mm512_setr_epi32 (x, x, x, x, x, x, x, x,
			    x, x, x, x, x, x, x, x);
}