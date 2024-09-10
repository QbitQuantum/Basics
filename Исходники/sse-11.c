void
foo (unsigned int x, double *y, const double *z)
{
  __m128d tmp;
  while (x)
    {
      tmp = _mm_load_sd (z);
      _mm_store_sd (y, tmp);
      --x; ++z; ++y;
    }
}