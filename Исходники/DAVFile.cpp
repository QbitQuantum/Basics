int CDAVFile::Stat(const CURL& url, struct __stat64* buffer)
{
  CCurlFile dav;
  std::string strRequest = "PROPFIND";
  dav.SetCustomRequest(strRequest);
  dav.SetRequestHeader("depth", 0);

  return dav.Stat(url, buffer);
}