//
// Ugly workaround for macro fmodl:
//
inline long double call_fmodl(long double a, long double b)
{  return fmodl(a, b); }