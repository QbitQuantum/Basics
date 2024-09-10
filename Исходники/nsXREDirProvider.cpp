static nsresult
GetShellFolderPath(int folder, nsAString& _retval)
{
  wchar_t* buf;
  uint32_t bufLength = _retval.GetMutableData(&buf, MAXPATHLEN + 3);
  NS_ENSURE_TRUE(bufLength >= (MAXPATHLEN + 3), NS_ERROR_OUT_OF_MEMORY);

  nsresult rv = NS_OK;

  LPITEMIDLIST pItemIDList = nullptr;

  if (SUCCEEDED(SHGetSpecialFolderLocation(nullptr, folder, &pItemIDList)) &&
      SHGetPathFromIDListW(pItemIDList, buf)) {
    // We're going to use wcslen (wcsnlen not available in msvc7.1) so make
    // sure to null terminate.
    buf[bufLength - 1] = L'\0';
    _retval.SetLength(wcslen(buf));
  } else {
    _retval.SetLength(0);
    rv = NS_ERROR_NOT_AVAILABLE;
  }

  CoTaskMemFree(pItemIDList);

  return rv;
}