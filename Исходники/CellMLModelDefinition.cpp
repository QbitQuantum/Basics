wchar_t* string2wstring(const char* str)
{
  if (str)
  {
    wchar_t* s;
    size_t l = strlen(str);
    s = (wchar_t*)malloc(sizeof(wchar_t)*(l+1));
    memset(s,0,(l+1)*sizeof(wchar_t));
    mbsrtowcs(s,&str,l,NULL);
    return(s);
  }
  return((wchar_t*)NULL);
}