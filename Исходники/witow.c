/*
 * @implemented
 */
wchar_t* _ui64tow(unsigned __int64 value, wchar_t* string, int radix)
{
  wchar_t tmp[65];
  wchar_t* tp = tmp;
  long i;
  unsigned long v = value;
  wchar_t* sp;

  if (radix > 36 || radix <= 1) {
    _set_errno(EDOM);
    return 0;
  }

  while (v || tp == tmp) {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+L'0';
    else
      *tp++ = i + L'a' - 10;
  }

  if (string == 0)
    string = (wchar_t*)malloc(((tp-tmp)+1)*sizeof(wchar_t));
  sp = string;

  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}