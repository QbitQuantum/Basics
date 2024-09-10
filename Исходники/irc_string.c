/*
 * clean_string - clean up a string possibly containing garbage
 *
 * *sigh* Before the kiddies find this new and exciting way of
 * annoying opers, lets clean up what is sent to local opers
 * -Dianora
 */
char *
clean_string(char *dest, const unsigned char *src, ssize_t len)
{
  char *d    = dest;
  assert(0 != dest);
  assert(0 != src);

  if (dest == NULL || src == NULL)
    return NULL;

  len -= 3;  /* allow for worst case, '^A\0' */

  while (*src && (len > 0))
  {
    if (*src & 0x80)             /* if high bit is set */
      *d++ = '.';
    else if (!IsPrint(*src))       /* if NOT printable */
    {
      *d++ = '^';
      --len;
      *d++ = 0x40 + *src;   /* turn it into a printable */
    }
    else
      *d++ = *src;

    ++src, --len;
  }

  *d = '\0';
  return dest;
}