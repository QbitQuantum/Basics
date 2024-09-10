static int
call_vscanf (const char *format, ...)
{
  va_list ap;
  va_start (ap, format);
  int ret = vscanf (format, ap);
  va_end (ap);
  return ret;
}