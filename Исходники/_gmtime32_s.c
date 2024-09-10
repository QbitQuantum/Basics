static errno_t __cdecl
_int_gmtime32_s (struct tm *ptm, const __time32_t *pt)
{
  struct tm *ltm;

  if (ptm)
    memset (ptm, 0xff, sizeof (*ptm));
  if (!ptm || !pt)
     {
        errno = EINVAL;
	return EINVAL;
     }
  if ((ltm = _gmtime32 (pt)) == NULL)
    return errno;
  *ptm = *ltm;
  return 0;
}