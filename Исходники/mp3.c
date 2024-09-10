void mp3_debug (char *format, ...) {
  va_list arg;
  va_start (arg, format);
  vfprintf (stderr, format, arg);
  va_end (arg);
}