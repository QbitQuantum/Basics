CHAR *
STUPID_STPNCPY (CHAR *dst, const CHAR *src, size_t n)
{
  size_t nc = STRNLEN (src, n);
  size_t i;

  for (i = 0; i < nc; ++i)
    dst[i] = src[i];
  for (; i < n; ++i)
    dst[i] = '\0';
  return dst + nc;
}