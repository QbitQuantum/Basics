wchar_t *__cdecl _wctime(const time_t *_Time)
{
  return _wctime64 (_Time);
}