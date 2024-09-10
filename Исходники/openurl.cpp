uint8* __open_url (wchar_t const* url, uint32& len)
{
  HINTERNET inet = InternetOpen(L"Firefox/3.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
  if (!inet)
    return NULL;
  HINTERNET file = InternetOpenUrl(inet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
  if (!file)
  {
    InternetCloseHandle (inet);
    return NULL;
  }
  uint32 size = 4096;
  len = 0;
  uint8* buf = new uint8[size];
  while (true)
  {
    if (size - len < 1024)
    {
      size *= 2;
      uint8* tmp = new uint8[size];
      memcpy (tmp, buf, len);
      delete[] buf;
      buf = tmp;
    }
    DWORD amount;
    if (!InternetReadFile (file, buf + len, size - len - 2, &amount))
      break;
    len += amount;
    if (amount == 0)
      break;
  }
  buf[len] = 0;
  InternetCloseHandle (file);
  InternetCloseHandle (inet);
  return buf;
}