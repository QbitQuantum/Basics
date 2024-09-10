inline T str2number(const char *str, int base, bool safe)
{
  int errno_bak=errno;
  errno=0;
  char *endptr;
// _strtoi64 is available in Visual Studio, but not yet in MINGW
#ifdef _MSC_VER
  const __int64 val=_strtoi64(str, &endptr, base);
#else
  const long long val=strtoll(str, &endptr, base);
#endif

  if(safe)
  {
    CHECK_RETURN(0==errno);
    errno=errno_bak;
    CHECK_RETURN(endptr!=str);
    if(std::numeric_limits<T>::min()==0)
    {
      // unsigned
      CHECK_RETURN(val>=0);
      CHECK_RETURN(
        (unsigned long long)(T)val<=
        (unsigned long long)std::numeric_limits<T>::max());
    }
    else
    {
      // signed
      CHECK_RETURN(val<=(long long)std::numeric_limits<T>::max());
      CHECK_RETURN(val>=(long long)std::numeric_limits<T>::min());
    }
  }

  return (T)val;
}