portable_off_t portable_ftell(FILE *f)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
  return _ftelli64(f);
#else
  return ftello(f);
#endif
}