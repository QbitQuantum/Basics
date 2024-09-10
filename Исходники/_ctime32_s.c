static errno_t __cdecl
_int_ctime32_s (char *d, size_t dn, const __time32_t *pt)
{
  struct tm ltm;
  errno_t e;

  if (!d || !dn)
     {
        errno = EINVAL;
	return EINVAL;
     }
  d[0] = 0;
  if (!pt)
     {
	errno = EINVAL;
	return EINVAL;
     }

  if ((e = _localtime32_s (&ltm, pt)) != 0)
    return e;  
  return asctime_s (d, dn, &ltm);
}