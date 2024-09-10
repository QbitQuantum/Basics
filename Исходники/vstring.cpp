std::wstring char_to_wcs(const char* s, size_t s_len)
{
  size_t size;
  if (s_len == 0) s_len = strlen(s);
  wchar_t* ws = new wchar_t[s_len + 1];
  mbstowcs_s(&size, ws, s_len + 1, s, s_len);
  std::wstring res = ws;
  delete[] ws;
  return res;
}