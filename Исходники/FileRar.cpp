void CFileRar::InitFromUrl(const CURL& url)
{
  m_strCacheDir = g_advancedSettings.m_cachePath;//url.GetDomain();
  CUtil::AddSlashAtEnd(m_strCacheDir);
  m_strRarPath = url.GetHostName();
  m_strPassword = url.GetUserName();
  m_strPathInRar = url.GetFileName();

  vector<CStdString> options;
  CUtil::Tokenize(url.GetOptions().Mid(1), options, "&");

  m_bFileOptions = 0;

  for( vector<CStdString>::iterator it = options.begin();it != options.end(); it++)
  {
    int iEqual = (*it).Find('=');
    if( iEqual >= 0 )
    {
      CStdString strOption = (*it).Left(iEqual);
      CStdString strValue = (*it).Mid(iEqual+1);

      if( strOption.Equals("flags") )
        m_bFileOptions = atoi(strValue.c_str());
      else if( strOption.Equals("cache") )
        m_strCacheDir = strValue;
    }
  }

}