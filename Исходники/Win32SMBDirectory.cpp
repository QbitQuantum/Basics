// check for empty string, remove trailing slash if any, convert to win32 form
inline static std::wstring prepareWin32SMBDirectoryName(const CURL& url)
{
  assert(url.GetProtocol() == "smb");

  if (url.GetHostName().empty() || url.GetShareName().empty())
    return std::wstring(); // can't use win32 standard file API, return empty string

  std::wstring nameW(CWIN32Util::ConvertPathToWin32Form("\\\\?\\UNC\\" + url.GetHostName() + '\\' + url.GetFileName()));
  if (!nameW.empty() && nameW.back() == L'\\')
    nameW.pop_back(); // remove slash at the end if any

  return nameW;
}