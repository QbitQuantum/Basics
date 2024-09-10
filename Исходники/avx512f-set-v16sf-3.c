foo_r (float x)
{
  return _mm512_setr_ps (x, x, x, x, x, x, x, x,
			 x, x, x, x, x, x, x, x);
}