/*********************************************************************
 *		_mbsncpy(MSVCRT.@)
 * REMARKS
 *  The parameter n is the number or characters to copy, not the size of
 *  the buffer. Use _mbsnbcpy for a function analogical to strncpy
 */
unsigned char* CDECL _mbsncpy(unsigned char* dst, const unsigned char* src, size_t n)
{
  unsigned char* ret = dst;
  if(!n)
    return dst;
  if (get_mbcinfo()->ismbcodepage)
  {
    while (*src && n)
    {
      n--;
      if (_ismbblead(*src))
      {
        if (!*(src+1))
        {
            *dst++ = 0;
            *dst++ = 0;
            break;
        }

        *dst++ = *src++;
      }

      *dst++ = *src++;
    }
  }
  else
  {
    while (n)
    {
        n--;
        if (!(*dst++ = *src++)) break;
    }
  }
  while (n--) *dst++ = 0;
  return ret;
}