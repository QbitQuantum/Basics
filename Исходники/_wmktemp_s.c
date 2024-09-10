static errno_t __cdecl
_int_wmktemp_s (wchar_t *d, size_t dn)
{
  size_t sz;
  if (!d || !dn)
    {
      _wmktemp (NULL);
      return EINVAL;
    }
  sz = wcsnlen (d, dn);
  if (sz >= dn || sz < 6)
    {
      d[0] = 0;
      _wmktemp (NULL);
      return EINVAL;
    }
  if (_wmktemp (d) != NULL)
    return 0;
  return errno;
}