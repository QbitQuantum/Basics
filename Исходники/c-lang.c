static char *
convert_ucn (char *p, char *limit, const char *dest_charset,
	     struct obstack *output, int length)
{
  unsigned long result = 0;
  gdb_byte data[4];
  int i;

  for (i = 0; i < length && p < limit && ISXDIGIT (*p); ++i, ++p)
    result = (result << 4) + host_hex_value (*p);

  for (i = 3; i >= 0; --i)
    {
      data[i] = result & 0xff;
      result >>= 8;
    }

  convert_between_encodings ("UTF-32BE", dest_charset, data,
			     4, 4, output, translit_none);

  return p;
}