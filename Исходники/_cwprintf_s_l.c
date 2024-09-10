int __cdecl
_cwprintf_s_l (const wchar_t *s, _locale_t loc, ...)
{
  va_list argp;
  int r;

  va_start (argp, loc);
  r = _vcwprintf_s_l (s, loc, argp);
  va_end (argp);
  return r; 
}