bool to_uint64(char const * s, uint64_t & i)
{
  char * stop;
#ifdef OMIM_OS_WINDOWS_NATIVE
  i = _strtoui64(s, &stop, 10);
#else
  i = strtoull(s, &stop, 10);
#endif
  return *stop == 0 && s != stop;
}