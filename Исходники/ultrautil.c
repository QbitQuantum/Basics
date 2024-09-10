INLINE int ispage(struct pike_string *url, struct multiset *pagexts)
{
  char *dot;
  int cnt;
  if(!url->len)
    return 0;
  if(*(url->str+url->len-1) == '/' || *(url->str) != '/') {
    return 1;
  }
    
  dot = STRRCHR(url->str, '.');
  if(dot && multiset_string_lookup(pagexts, dot+1)) {
    return 1;
  }
  return 0;
}