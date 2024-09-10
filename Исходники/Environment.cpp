bool Environment::getCurrentUserName(StringStorage *out, LogWriter *log)
{
  TCHAR *userName;
  DWORD byteCount;
  DWORD sessionId = WTS::getActiveConsoleSessionId(log);
  if (WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessionId,
                                 WTSUserName, &userName, &byteCount) == 0) {
    return false;
  }
  out->setString(userName);
  WTSFreeMemory(userName);

  return true;
}