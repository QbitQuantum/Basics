count_zeroes(size_t *x)
{
  int result;
#if defined(HAVE_BUILTIN_CTZL)
  result = __builtin_ctzl(*x);
  *x >>= result;
#elif defined(HAVE_BITSCANFORWARD64)
  _BitScanForward64(&result, *x);
  *x >>= result;
#elif defined(HAVE_BITSCANFORWARD)
  _BitScanForward(&result, *x);
  *x >>= result;
#else
  result = 0;
  while ((*x & 1) == 0) {
    ++result;
    *x >>= 1;
  }
#endif
  return result;
}