ssize_t
WideTtyCvt( CHAR16 *dest, const char *buf, size_t n)
{
  UINTN   i;
  wint_t  wc;

  for(i = 0; i < n; ++i) {
    wc = btowc(*buf++);
    if( wc == 0) {
      break;
    };
    if(wc < 0) {
      wc = BLOCKELEMENT_LIGHT_SHADE;
    }
    if(wc == L'\n') {
      *dest++ = L'\r';
    }
    *dest++ = (CHAR16)wc;
  }
  *dest = 0;
  return (ssize_t)i;
}