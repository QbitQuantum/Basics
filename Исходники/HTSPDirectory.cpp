bool CHTSPDirectorySession::Open(const CURI& url)
{
  if(!m_session.Connect(url.GetHostName(), url.GetPort()))
    return false;

  if(m_session.GetProtocol() < 2)
  {
    CLog::Log(LOGERROR, "CHTSPDirectory::GetDirectory - incompatible protocol version %d", m_session.GetProtocol());
    return false;
  }

  if(!url.GetUserName().IsEmpty())
    m_session.Auth(url.GetUserName(), url.GetPassWord());

  if(!m_session.SendEnableAsync())
    return false;

  Create();

  m_started.WaitMSec(30000);
  return !m_bStop;
}