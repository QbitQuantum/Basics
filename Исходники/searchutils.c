/* Convert the *N-byte string, BEG, to lowercase, and write the
   NUL-terminated result into malloc'd storage.  Upon success, set *N
   to the length (in bytes) of the resulting string (not including the
   trailing NUL byte), and return a pointer to the lowercase string.
   Upon memory allocation failure, this function exits.
   Note that on input, *N must be larger than zero.

   Note that while this function returns a pointer to malloc'd storage,
   the caller must not free it, since this function retains a pointer
   to the buffer and reuses it on any subsequent call.  As a consequence,
   this function is not thread-safe.  */
char *
mbtolower (const char *beg, size_t *n)
{
  static char *out;
  static size_t outalloc;
  size_t outlen, mb_cur_max;
  mbstate_t is, os;
  const char *end;
  char *p;

  assert (0 < *n);

  if (*n > outalloc)
    {
      out = xrealloc (out, *n);
      outalloc = *n;
    }
  /* appease clang-2.6 */
  assert (out);

  memset (&is, 0, sizeof (is));
  memset (&os, 0, sizeof (os));
  end = beg + *n;

  mb_cur_max = MB_CUR_MAX;
  p = out;
  outlen = 0;
  while (beg < end)
    {
      wchar_t wc;
      size_t mbclen = mbrtowc(&wc, beg, end - beg, &is);
      if (outlen + mb_cur_max >= outalloc)
        {
          out = x2nrealloc (out, &outalloc, 1);
          p = out + outlen;
        }

      if (mbclen == (size_t) -1 || mbclen == (size_t) -2 || mbclen == 0)
        {
          /* An invalid sequence, or a truncated multi-octet character.
             We treat it as a single-octet character.  */
          *p++ = *beg++;
          outlen++;
          memset (&is, 0, sizeof (is));
          memset (&os, 0, sizeof (os));
        }
      else
        {
          beg += mbclen;
          mbclen = wcrtomb (p, towlower ((wint_t) wc), &os);
          p += mbclen;
          outlen += mbclen;
        }
    }

  *n = p - out;
  *p = 0;
  return out;
}