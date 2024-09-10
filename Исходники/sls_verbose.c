/*
 *   for GalUtil_PInfo1, GalUtil_PInfo2, GalUtil_Debug1, GalUtil_Debug2
 */
static void printf_info(const char *format, va_list args, void *client_data)
{
  vprintf(format, args);
  fflush(stdout);
}