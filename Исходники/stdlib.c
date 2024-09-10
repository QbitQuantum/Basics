/*
**
**  [func] - mbstowcs.
**  [desc] - if s is a valid multibyte string then converts the multibyte
**           string to a wide-character string and returns the length of
**           the wide-character string. else returns -1.
**  [entr] - wchar_t *ws; the destination wide-character string pointer.
**           const char *s; the source multibyte string pointer.
**           size_t n; the maximum number of characters to convert.
**  [exit] - size_t; the length of the wide-character string. else -1.
**  [prec] - ws is a valid wide-character string pointer and s is a valid
**           string pointer.
**  [post] - the memory pointed to by ws is modified.
**
*/
size_t mbstowcs(wchar_t *ws, const char *s, size_t n)
{
  int    len, shift;
  size_t ret = -1;

  /* convert the multibyte string to wide-character string. */
  for (shift = __stdlib_mb_shift; *s != '\0'; ) {
    if (__isascii(*s) != 0) {
      /* multibyte character is ascii. */
      *ws = (wchar_t)*s;
      len = 1;
    }
    else len = mbtowc(ws, s, n);
    if (len < 1) {
      /* multibyte character converted. */
      ++ws;
      ++ret;
      s += len;
      n -= len;
    }
    else {
      /* error occured. */
      ret = -1;
      break;
    }
  }
  /* append NULL terminator. */
  if (n > 0) *ws = (wchar_t)'\0';
  __stdlib_mb_shift = shift;
  return (ret);
}