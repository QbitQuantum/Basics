/**
 * Like asprintf, just portable.
 *
 * @param buf set to a buffer of sufficient size (allocated, caller must free)
 * @param format format string (see printf, fprintf, etc.)
 * @param ... data for format string
 * @return number of bytes in "*buf" excluding 0-termination
 */
int
GNUNET_asprintf (char **buf, const char *format, ...)
{
  int ret;
  va_list args;

  va_start (args, format);
  ret = VSNPRINTF (NULL, 0, format, args);
  va_end (args);
  *buf = GNUNET_malloc (ret + 1);
  va_start (args, format);
  ret = VSPRINTF (*buf, format, args);
  va_end (args);
  return ret;
}