int
basestring_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
  int ret;

  if (size == 0)
  {
    char buf[1];
    return basestring_vsnprintf(buf, 1, format, ap);
  }
  ret = IF_WIN(_vsnprintf,vsnprintf)(str, size, format, ap);
  if (ret >= 0 && ret < (int)size)
    return ret;
#ifdef _WIN32
  if (ret < 0 && errno == EINVAL)
    return ret;
  // otherwise, more than size chars are needed
  return _vscprintf(format, ap);
#else
  return ret;
#endif
}