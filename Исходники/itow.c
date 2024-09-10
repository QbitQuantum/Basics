/*
 * @implemented
 */
wchar_t *
_itow(int value, wchar_t *string, int radix)
{
  return _ltow(value, string, radix);
}