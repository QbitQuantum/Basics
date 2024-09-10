int
attribute_compat_text_section
__nldbl_vswscanf (const wchar_t *string, const wchar_t *fmt, va_list ap)
{
  int res;
  __no_long_double = 1;
  res = vswscanf (string, fmt, ap);
  __no_long_double = 0;
  return res;
}