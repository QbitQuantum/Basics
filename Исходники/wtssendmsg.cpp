int wts_send_message(int mode, const char * title, const char * text,
                     int * perrcnt /* = 0 */)
{
  if (perrcnt)
    *perrcnt = 0;

  // Get session list
  WTS_SESSION_INFOA * sessions; DWORD count;
  if (!WTSEnumerateSessionsA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessions, &count))
    return -1;

  int msgcnt = 0;
  for (unsigned i = 0; i < count; i++) {

    if (   !strcmpi(sessions[i].pWinStationName, "Console")
        || (mode >= 1 && sessions[i].State == WTSActive)
        || (mode >= 2 && sessions[i].State == WTSConnected)) {

      // Send Message, don't wait for OK button
      DWORD result;
      if (WTSSendMessageA(WTS_CURRENT_SERVER_HANDLE, sessions[i].SessionId,
          const_cast<char *>(title), strlen(title),
          const_cast<char *>(text), strlen(text),
          MB_OK|MB_ICONEXCLAMATION, 0 /*Timeout*/,
          &result, FALSE /*Wait*/))
        msgcnt++;
      else if (perrcnt)
        (*perrcnt)++;
    }
  }

  WTSFreeMemory(sessions);
  return msgcnt;
}