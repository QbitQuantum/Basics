static
int fct2 (int dummy, ...)
{
  va_list argp;
  int ret = dummy;

  __va_start (argp, dummy);
  ret += fct1 (argp, SZ_ARGS);
  __va_end (argp);
  return ret;
}