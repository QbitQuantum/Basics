foo_r (float x, int i)
{
  switch (i)
    {
    case 0:
      return _mm512_setr_ps (x, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    case 1:
      return _mm512_setr_ps (0, x, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    case 2:
      return _mm512_setr_ps (0, 0, x, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    case 3:
      return _mm512_setr_ps (0, 0, 0, x, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    case 4:
      return _mm512_setr_ps (0, 0, 0, 0, x, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    case 5:
      return _mm512_setr_ps (0, 0, 0, 0, 0, x, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    case 6:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, x, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    case 7:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, x, 0, 0, 0, 0, 0, 0, 0, 0);
    case 8:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, x, 0, 0, 0, 0, 0, 0, 0);
    case 9:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, 0, x, 0, 0, 0, 0, 0, 0);
    case 10:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x, 0, 0, 0, 0, 0);
    case 11:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x, 0, 0, 0, 0);
    case 12:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x, 0, 0, 0);
    case 13:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x, 0, 0);
    case 14:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x, 0);
    case 15:
      return _mm512_setr_ps (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x);
    default:
      abort ();
    }
}