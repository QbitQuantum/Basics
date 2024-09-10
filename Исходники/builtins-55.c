void testl(long double x)
{
#ifdef HAVE_C99_RUNTIME
  if (sizeof(long) != sizeof(long long))
    return;

  if (__builtin_lceill(x) != __builtin_llceill(x))
    link_error();
  if (__builtin_lfloorl(x) != __builtin_llfloorl(x))
    link_error();
  if (lroundl(x) != llroundl(x))
    link_error();
  if (lrintl(x) != llrintl(x))
    link_error();
#endif
}