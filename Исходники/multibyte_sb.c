size_t
wcstombs(
  char *s,
  const wchar_t *pwcs,
  size_t n
  )
{

  /* s may be NULL */
  /* pwcs may be NULL */

  return wcsrtombs(s, &pwcs, n, NULL);
}