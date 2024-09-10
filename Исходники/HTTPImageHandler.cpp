CHTTPImageHandler::CHTTPImageHandler(const HTTPRequest &request)
  : CHTTPFileHandler(request)
{
  std::string file;
  int responseStatus = MHD_HTTP_BAD_REQUEST;

  // resolve the URL into a file path and a HTTP response status
  if (m_request.pathUrl.size() > 7)
  {
    file = m_request.pathUrl.substr(7);

    XFILE::CImageFile imageFile;
    const CURL pathToUrl(file);
    if (imageFile.Exists(pathToUrl))
    {
      responseStatus = MHD_HTTP_OK;
      struct __stat64 statBuffer;
      if (imageFile.Stat(pathToUrl, &statBuffer) == 0)
      {
        SetLastModifiedDate(&statBuffer);
        SetCanBeCached(true);
      }
    }
    else
      responseStatus = MHD_HTTP_NOT_FOUND;
  }

  // set the file and the HTTP response status
  SetFile(file, responseStatus);
}