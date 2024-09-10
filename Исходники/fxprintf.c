int
__fxprintf (FILE *fp, const char *fmt, ...)
{
  if (fp == NULL)
    fp = stderr;

  va_list ap;
  va_start (ap, fmt);

  int res;
  if (fwide (fp, 0) > 0)
    {
      size_t len = strlen (fmt) + 1;
      wchar_t wfmt[len];
      for (size_t i = 0; i < len; ++i)
	{
	  assert (isascii (fmt[i]));
	  wfmt[i] = fmt[i];
	}
      res = vfwprintf (fp, wfmt, ap);
    }
  else
    res = INTUSE(vfprintf) (fp, fmt, ap);

  va_end (ap);

  return res;
}