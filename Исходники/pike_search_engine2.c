static INLINE int NameNH(MEMCMP)(NCHAR *a, HCHAR *b, ptrdiff_t e)
{
#if NSHIFT == HSHIFT
  return MEMCMP(a, b, sizeof(HCHAR)*e);
#else
  for(;e;e--,b++,a++)
  {
    if(*b!=*a)
    {
      if(*b<*a) return -1;
      if(*b>*a) return 1;
    }
  }
  return 0;
  
#endif
}