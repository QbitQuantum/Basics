int32_t 
DataMap::utoi(const UnicodeString &s) const
{
  char ch[256];
  const UChar *u = s.getBuffer();
  int32_t len = s.length();
  u_UCharsToChars(u, ch, len);
  ch[len] = 0; /* include terminating \0 */
  return atoi(ch);
}