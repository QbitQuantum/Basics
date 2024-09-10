int strnicomp(const char *s1,const char *s2,size_t n)
{
#ifdef _WIN_ALL
  // If we specify 'n' exceeding the actual string length, CompareString goes
  // beyond the trailing zero and compares garbage. So we need to limit 'n'
  // to real string length.
  // It is important to use strnlen (or memchr(...,0)) instead of strlen,
  // because data can be not zero terminated.
  size_t l1=Min(strnlen(s1,n),n);
  size_t l2=Min(strnlen(s2,n),n);
  return CompareStringA(LOCALE_USER_DEFAULT,NORM_IGNORECASE|SORT_STRINGSORT,s1,(int)l1,s2,(int)l2)-2;
#else
  if (n==0)
    return 0;
  while (toupper(*s1)==toupper(*s2))
  {
    if (*s1==0 || --n==0)
      return 0;
    s1++;
    s2++;
  }
  return s1 < s2 ? -1 : 1;
#endif
}