std::string CMime::GetMimeType(const CURL &url, bool lookup)
{
  
  std::string strMimeType;

  if( url.IsProtocol("shout") || url.IsProtocol("http") || url.IsProtocol("https"))
  {
    // If lookup is false, bail out early to leave mime type empty
    if (!lookup)
      return strMimeType;

    std::string strmime;
    XFILE::CCurlFile::GetMimeType(url, strmime);

    // try to get mime-type again but with an NSPlayer User-Agent
    // in order for server to provide correct mime-type.  Allows us
    // to properly detect an MMS stream
    if (StringUtils::StartsWithNoCase(strmime, "video/x-ms-"))
      XFILE::CCurlFile::GetMimeType(url, strmime, "NSPlayer/11.00.6001.7000");

    // make sure there are no options set in mime-type
    // mime-type can look like "video/x-ms-asf ; charset=utf8"
    size_t i = strmime.find(';');
    if(i != std::string::npos)
      strmime.erase(i, strmime.length() - i);
    StringUtils::Trim(strmime);
    strMimeType = strmime;
  }
  else
    strMimeType = GetMimeType(url.GetFileType());

  // if it's still empty set to an unknown type
  if (strMimeType.empty())
    strMimeType = "application/octet-stream";

  return strMimeType;
}