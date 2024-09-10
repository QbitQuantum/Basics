int CLobbyApp::OnMessageBox(const char * strText, const char * strCaption, UINT nType)
{
  char sz[256];
  if (strCaption && *strCaption)
  {
    Strcpy(sz, strCaption);
    Strcat(sz, ": ");
  }
  Strcat(sz, strText);
  return m_plas->LogEvent(EVENTLOG_ERROR_TYPE, LE_ODBC_Error, strText);
}