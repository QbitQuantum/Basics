CHTTPImageTransformationHandler::CHTTPImageTransformationHandler(const HTTPRequest &request)
  : IHTTPRequestHandler(request),
    m_url(),
    m_lastModified(),
    m_buffer(NULL),
    m_responseData()
{
  m_url = m_request.pathUrl.substr(ImageBasePath.size());
  if (m_url.empty())
  {
    m_response.status = MHD_HTTP_BAD_REQUEST;
    m_response.type = HTTPError;
    return;
  }

  XFILE::CImageFile imageFile;
  const CURL pathToUrl(m_url);
  if (!imageFile.Exists(pathToUrl))
  {
    m_response.status = MHD_HTTP_NOT_FOUND;
    m_response.type = HTTPError;
    return;
  }

  m_response.type = HTTPMemoryDownloadNoFreeCopy;
  m_response.status = MHD_HTTP_OK;

  // determine the content type
  std::string ext = URIUtils::GetExtension(pathToUrl.GetHostName());
  StringUtils::ToLower(ext);
  m_response.contentType = CMime::GetMimeType(ext);

  //! @todo determine the maximum age

  // determine the last modified date
  struct __stat64 statBuffer;
  if (imageFile.Stat(pathToUrl, &statBuffer) != 0)
    return;

  struct tm *time;
#ifdef HAVE_LOCALTIME_R
  struct tm result = {};
  time = localtime_r((time_t*)&statBuffer.st_mtime, &result);
#else
  time = localtime((time_t *)&statBuffer.st_mtime);
#endif
  if (time == NULL)
    return;

  m_lastModified = *time;
}