int
QLuaApplication::Private::printMessage(int status, const char *fmt, ...)
{
  fflush(stdout);
  fflush(stderr);
  if (programName)
    fprintf(stderr,"%s: ", programName);
  if (!fmt)
    fmt = "unprintable error";
  QString message;
  va_list ap;
  va_start(ap, fmt);
  message = message.vsprintf(fmt, ap);
  va_end(ap);
  fprintf(stderr, "%s\n", message.toLocal8Bit().constData());
  return status;
}