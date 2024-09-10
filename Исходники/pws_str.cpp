double pws_os::wctof(const wchar_t *s)
{
  return double(wcstold(s, nullptr));
}