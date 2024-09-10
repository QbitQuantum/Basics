bool CCurlFile::GetMimeType(const CURL &url, CStdString &content, CStdString useragent)
{
  CCurlFile file;
  if (!useragent.IsEmpty())
    file.SetUserAgent(useragent);

  struct __stat64 buffer;
  if( file.Stat(url, &buffer) == 0 )
  {
    if (buffer.st_mode == _S_IFDIR)
      content = "x-directory/normal";
    else
      content = file.GetMimeType();
    CLog::Log(LOGDEBUG, "CCurlFile::GetMimeType - %s -> %s", url.Get().c_str(), content.c_str());
    return true;
  }
  CLog::Log(LOGDEBUG, "CCurlFile::GetMimeType - %s -> failed", url.Get().c_str());
  content = "";
  return false;
}