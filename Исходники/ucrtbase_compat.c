_onexit_t __cdecl _onexit(_onexit_t func)
{
  return _crt_atexit(func) == 0 ? func : NULL;
}