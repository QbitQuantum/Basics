void _ltoa(long value, char* string, unsigned char radix)
{
  if (value < 0 && radix == 10) {
    *string++ = '-';
    value = -value;
  }
  _ultoa(value, string, radix);
}