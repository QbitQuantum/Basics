void CHTTPFileHandler::SetFile(const std::string& file, int responseStatus)
{
  m_url = file;
  m_response.status = responseStatus;
  if (m_url.empty())
    return;

  // translate the response status into the response type
  if (m_response.status == MHD_HTTP_OK)
    m_response.type = HTTPFileDownload;
  else if (m_response.status == MHD_HTTP_FOUND)
      m_response.type = HTTPRedirect;
  else
    m_response.type = HTTPError;

  // try to determine some additional information if the file can be downloaded
  if (m_response.type == HTTPFileDownload)
  {
    // determine the content type
    std::string ext = URIUtils::GetExtension(m_url);
    StringUtils::ToLower(ext);
    m_response.contentType = CMime::GetMimeType(ext);

    // determine the last modified date
    XFILE::CFile fileObj;
    if (!fileObj.Open(m_url, XFILE::READ_NO_CACHE))
    {
      m_response.type = HTTPError;
      m_response.status = MHD_HTTP_INTERNAL_SERVER_ERROR;
    }
    else
    {
      struct __stat64 statBuffer;
      if (fileObj.Stat(&statBuffer) == 0)
        SetLastModifiedDate(&statBuffer);
    }
  }

  // disable ranges and caching if the file can't be downloaded
  if (m_response.type != HTTPFileDownload)
  {
    m_canHandleRanges = false;
    m_canBeCached = false;
  }

  // disable caching if the last modified date couldn't be read
  if (!m_lastModified.IsValid())
    m_canBeCached = false;
}