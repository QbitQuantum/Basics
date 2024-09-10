void CRarFile::InitFromUrl(const CURL& url)
{
  m_strCacheDir = g_advancedSettings.m_cachePath;//url.GetDomain();
  URIUtils::AddSlashAtEnd(m_strCacheDir);
  m_strRarPath = url.GetHostName();
  m_strPassword = url.GetUserName();
  m_strPathInRar = url.GetFileName();

  std::vector<std::string> options;
  if (!url.GetOptions().empty())
    StringUtils::Tokenize(url.GetOptions().substr(1), options, "&");

  m_bFileOptions = 0;

  for(std::vector<std::string>::iterator it = options.begin();it != options.end(); ++it)
  {
    size_t iEqual = (*it).find('=');
    if(iEqual != std::string::npos)
    {
      std::string strOption = StringUtils::Left((*it), iEqual);
      std::string strValue = StringUtils::Mid((*it), iEqual+1);

      if( strOption == "flags" )
        m_bFileOptions = atoi(strValue.c_str());
      else if( strOption == "cache" )
        m_strCacheDir = strValue;
    }
  }

}