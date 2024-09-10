static std::wstring
GetDeviceMapping(const std::wstring& aDosDeviceName)
{
  wchar_t buf[MAX_PATH] = { 0 };
  DWORD rv = QueryDosDeviceW(aDosDeviceName.c_str(), buf, MAX_PATH);
  if (rv == 0) {
    return std::wstring(L"");
  }
  return std::wstring(buf, buf + rv);
}