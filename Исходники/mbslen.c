/*
 * @implemented
 */
size_t _mbslen(const unsigned char *str)
{
  size_t len = 0;
  while(*str)
  {
    if (_ismbblead(*str))
    {
      str++;
      if (!*str)  /* count only full chars */
        break;
    }
    str++;
    len++;
  }
  return len;
}