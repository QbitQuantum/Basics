void 
ON_qsort( void *base, size_t nel, size_t width, int (*compar)(void*,const void *, const void *),void* context)
{
#if defined(ON__HAVE_RELIABLE_SYSTEM_CONTEXT_QSORT)
  // The call here must be a thread safe system qsort
  // that is faster than the alternative code in this function.
  // In particular, if it uses a random number generator to
  // find pivots, that calculation must be thread safe.
#if defined(ON_COMPILER_MSC)
  qsort_s(base,nel,width,compar,context);
#elif defined(ON_COMPILER_XCODE)
  qsort_r(base,nel,width,context,compar);
#endif
#else
  ON_hsort(base, nel, width, compar, context);
#endif
}