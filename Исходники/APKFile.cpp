bool CAPKFile::Open(const CURL& url)
{
  Close();

  m_url = url;
  CStdString path = url.GetFileName();
  CStdString host = url.GetHostName();
  // host name might be encoded rfc1738.txt, decode it.
  CURL::Decode(host);

  int zip_flags = 0, zip_error = 0;
  m_zip_archive = zip_open(host.c_str(), zip_flags, &zip_error);
  if (!m_zip_archive || zip_error)
  {
    CLog::Log(LOGERROR, "CAPKFile::Open: Unable to open archive : '%s'",
      host.c_str());
    return false;
  }

  m_zip_index = zip_name_locate(m_zip_archive, path.c_str(), zip_flags);
  if (m_zip_index == -1)
  {
    // might not be an error if caller is just testing for presence/absence 
    CLog::Log(LOGDEBUG, "CAPKFile::Open: Unable to locate file : '%s'",
      path.c_str());
    zip_close(m_zip_archive);
    m_zip_archive = NULL;
    return false;
  }

  // cache the file size
  struct zip_stat sb;
  zip_stat_init(&sb);
  int rtn = zip_stat_index(m_zip_archive, m_zip_index, zip_flags, &sb);
  if (rtn == -1)
  {
    CLog::Log(LOGERROR, "CAPKFile::Open: Unable to stat file : '%s'",
      path.c_str());
    zip_close(m_zip_archive);
    m_zip_archive = NULL;
    return false;
  }
  m_file_pos = 0;
  m_file_size = sb.size;

  // finally open the file
  m_zip_file = zip_fopen_index(m_zip_archive, m_zip_index, zip_flags);
  if (!m_zip_file)
  {
    CLog::Log(LOGERROR, "CAPKFile::Open: Unable to open file : '%s'",
      path.c_str());
    zip_close(m_zip_archive);
    m_zip_archive = NULL;
    return false;
  }

  // We've successfully opened the file!
  return true;
}