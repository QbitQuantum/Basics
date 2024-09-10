/*
 * @implemented
 */
unsigned char * _mbsninc(const unsigned char *str, size_t n)
{
  if(!str)
    return NULL;

  while (n > 0 && *str)
  {
    if (_ismbblead(*str))
    {
      if (!*(str+1))
         break;
      str++;
    }
    str++;
    n--;
  }

  return (unsigned char*)str;
}