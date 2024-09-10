int CFileSFTP::Stat(const CURL& url, struct __stat64* buffer)
{
  CSFTPSessionPtr session = CSFTPSessionManager::CreateSession(url.GetHostName().c_str(), url.GetUserName().c_str(), url.GetPassWord().c_str());
  if (session)
    return session->Stat(url.GetFileName().c_str(), buffer);
  else
  {
    CLog::Log(LOGERROR, "SFTPFile: Failed to create session to stat");
    return -1;
  }
}