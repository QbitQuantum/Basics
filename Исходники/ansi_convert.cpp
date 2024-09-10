std::string ANSIToUTF8(std::string path, const std::string& name)
{
  path += name;
  int    len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, NULL, 0);
  LPWSTR buf = (LPWSTR)malloc(2*len);

  if (buf) {
    MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, buf, len);
    int plen = GetLongPathNameW(buf, NULL, 0);
    LPWSTR buf2 = (LPWSTR)malloc(plen*2+2);
    if (buf2) {
      GetLongPathNameW(buf, buf2, plen);
      LPWSTR buf3 = wcsrchr((wchar_t*)buf2, L'\\')+1;
      int ulen = WideCharToMultiByte(CP_UTF8, 0, buf3, -1, NULL, 0, NULL, NULL);
      if (ulen) {
        std::string tmp;
        tmp.resize(ulen-1);
        WideCharToMultiByte(CP_UTF8, 0, buf3, -1, (LPSTR)tmp.c_str(), ulen-1, NULL, NULL);
        free(buf2);
        free(buf);
        return tmp;
      }
      free(buf2);
    }
    free(buf);
  }
  return "";
}