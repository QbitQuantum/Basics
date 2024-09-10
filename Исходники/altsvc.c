static CURLcode getalnum(const char **ptr, char *alpnbuf, size_t buflen)
{
  size_t len;
  const char *protop;
  const char *p = *ptr;
  while(*p && ISBLANK(*p))
    p++;
  protop = p;
  while(*p && ISALNUM(*p))
    p++;
  len = p - protop;

  if(!len || (len >= buflen))
    return CURLE_BAD_FUNCTION_ARGUMENT; /* TODO: improve error code */
  memcpy(alpnbuf, protop, len);
  alpnbuf[len] = 0;
  *ptr = p;
  return CURLE_OK;
}