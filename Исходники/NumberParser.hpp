static inline uint64_t
ParseUint64(const TCHAR *p, TCHAR **endptr=NULL, int base=10)
{
  assert(p != NULL);

  return wcstoull(p, endptr, base);
}