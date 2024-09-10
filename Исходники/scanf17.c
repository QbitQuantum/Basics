static int
xscanf (const char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);
  int ret = vscanf (fmt, ap);
  va_end (ap);
  return ret;
}