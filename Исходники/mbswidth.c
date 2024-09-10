/* Returns the number of columns needed to represent the multibyte
   character string pointed to by STRING of length NBYTES.  If a
   non-printable character occurs, and MBSW_REJECT_UNPRINTABLE is
   specified, -1 is returned.  */
int
mbsnwidth (const char *string, size_t nbytes, int flags)
{
  const char *p = string;
  const char *plimit = p + nbytes;
  int width;

  width = 0;
  if (MB_CUR_MAX > 1)
    {
      while (p < plimit)
        switch (*p)
          {
            case ' ': case '!': case '"': case '#': case '%':
            case '&': case '\'': case '(': case ')': case '*':
            case '+': case ',': case '-': case '.': case '/':
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case ':': case ';': case '<': case '=': case '>':
            case '?':
            case 'A': case 'B': case 'C': case 'D': case 'E':
            case 'F': case 'G': case 'H': case 'I': case 'J':
            case 'K': case 'L': case 'M': case 'N': case 'O':
            case 'P': case 'Q': case 'R': case 'S': case 'T':
            case 'U': case 'V': case 'W': case 'X': case 'Y':
            case 'Z':
            case '[': case '\\': case ']': case '^': case '_':
            case 'a': case 'b': case 'c': case 'd': case 'e':
            case 'f': case 'g': case 'h': case 'i': case 'j':
            case 'k': case 'l': case 'm': case 'n': case 'o':
            case 'p': case 'q': case 'r': case 's': case 't':
            case 'u': case 'v': case 'w': case 'x': case 'y':
            case 'z': case '{': case '|': case '}': case '~':
              /* These characters are printable ASCII characters.  */
              p++;
              width++;
              break;
            default:
              /* If we have a multibyte sequence, scan it up to its end.  */
              {
                mbstate_t mbstate;
                memset (&mbstate, 0, sizeof mbstate);
                do
                  {
                    wchar_t wc;
                    size_t bytes;
                    int w;

                    bytes = mbrtowc (&wc, p, plimit - p, &mbstate);

                    if (bytes == (size_t) -1)
                      /* An invalid multibyte sequence was encountered.  */
                      {
                        if (!(flags & MBSW_REJECT_INVALID))
                          {
                            p++;
                            width++;
                            break;
                          }
                        else
                          return -1;
                      }

                    if (bytes == (size_t) -2)
                      /* An incomplete multibyte character at the end.  */
                      {
                        if (!(flags & MBSW_REJECT_INVALID))
                          {
                            p = plimit;
                            width++;
                            break;
                          }
                        else
                          return -1;
                      }

                    if (bytes == 0)
                      /* A null wide character was encountered.  */
                      bytes = 1;

                    w = wcwidth (wc);
                    if (w >= 0)
                      /* A printable multibyte character.  */
                      {
                        if (w > INT_MAX - width)
                          goto overflow;
                        width += w;
                      }
                    else
                      /* An unprintable multibyte character.  */
                      if (!(flags & MBSW_REJECT_UNPRINTABLE))
                        {
                          if (!iswcntrl (wc))
                            {
                              if (width == INT_MAX)
                                goto overflow;
                              width++;
                            }
                        }
                      else
                        return -1;

                    p += bytes;
                  }
                while (! mbsinit (&mbstate));
              }
              break;
          }
      return width;
    }

  while (p < plimit)
    {
      unsigned char c = (unsigned char) *p++;

      if (isprint (c))
        {
          if (width == INT_MAX)
            goto overflow;
          width++;
        }
      else if (!(flags & MBSW_REJECT_UNPRINTABLE))
        {
          if (!iscntrl (c))
            {
              if (width == INT_MAX)
                goto overflow;
              width++;
            }
        }
      else
        return -1;
    }
  return width;

 overflow:
  return INT_MAX;
}