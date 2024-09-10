CCMythSession::CCMythSession(const CURI& url)
{
  m_control   = NULL;
  m_event     = NULL;
  m_database  = NULL;
  m_hostname  = url.GetHostName();
  m_username  = url.GetUserName() == "" ? MYTH_DEFAULT_USERNAME : url.GetUserName();
  m_password  = url.GetPassWord() == "" ? MYTH_DEFAULT_PASSWORD : url.GetPassWord();
  m_port      = url.HasPort() ? url.GetPort() : MYTH_DEFAULT_PORT;
  m_timestamp = CTimeUtils::GetTimeMS();
  m_dll = new DllLibCMyth;
  m_dll->Load();
  if(m_dll->IsLoaded())
  {
    if(CLog::m_logLevel == LOGDEBUG)
      m_dll->dbg_level(CMYTH_DBG_DETAIL);
    else
      m_dll->dbg_level(CMYTH_DBG_ERROR);
  }
}