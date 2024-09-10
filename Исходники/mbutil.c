/* return the number of bytes parsed from the multibyte sequence starting
   at src, if a non-L'\0' wide character was recognized. It returns 0,
   if a L'\0' wide character was recognized. It  returns (size_t)(-1),
   if an invalid multibyte sequence was encountered. It returns (size_t)(-2)
   if it couldn't parse a complete  multibyte character.  */
int
_rl_get_char_len(char *src, mbstate_t *ps)
{
  size_t tmp;

  tmp = mbrlen((const char *)src, (size_t)strlen(src), ps);
  if (tmp == (size_t)(-2))
    {
      /* shorted to compose multibyte char */
      if (ps)
	memset (ps, 0, sizeof(mbstate_t));
      return -2;
    }
  else if (tmp == (size_t)(-1))
    {
      /* invalid to compose multibyte char */
      /* initialize the conversion state */
      if (ps)
	memset (ps, 0, sizeof(mbstate_t));
      return -1;
    }
  else if (tmp == (size_t)0)
    return 0;
  else
    return (int)tmp;
}