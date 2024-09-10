// CTOR of HTTP Server session
ServerSession::ServerSession()
{
  ASSERT(g_session == nullptr);

  ReadRegistrySettings();
  CreateLogfile();
  InitializeCriticalSection(&m_lock);
}