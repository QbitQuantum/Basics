static void LOG(const char *fmt, ... )
{
  va_list ap;
  va_start(ap, fmt);
  PRUint32 nb = 0;
  char buf[512];

  nb = PR_snprintf(buf, sizeof(buf), "[%u:%p] ", GetPID(), PR_GetCurrentThread());

  PR_vsnprintf(buf + nb, sizeof(buf) - nb, fmt, ap);
  buf[sizeof(buf) - 1] = '\0';

  fwrite(buf, strlen(buf), 1, stdout);
  fflush(stdout);

  va_end(ap);
}