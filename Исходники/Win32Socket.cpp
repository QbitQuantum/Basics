bool
LocalWin32Socket::Write( const void* buf, size_t size )
{
  char* src = (char*) buf;
  lastError = EC_OK;
  while (size > 0 && state == SS_OPEN)
  {
    sendBuffer->sendWaitFlag = true;
    size_t begin = sendBuffer->dataBeg;
    size_t end = sendBuffer->dataEnd;
    size_t snd_size = (begin <= end) ?
                      sizeof(sendBuffer->dataBuf) - end - (begin == 0) :
                      begin - end - 1;
    if ( snd_size > 0 )
    {
      sendBuffer->sendWaitFlag = false;
      if ( snd_size >= size )
      {
        memcpy( &sendBuffer->dataBuf[end], src, size );
        end += size;
        size = 0;
      }
      else
      {
        memcpy( &sendBuffer->dataBuf[end], src, snd_size );
        end += snd_size;
        src += snd_size;
        size -= snd_size;
      }
      sendBuffer->dataEnd = (end == sizeof(sendBuffer->dataBuf)) ? 0 : end;
      if ( sendBuffer->recvWaitFlag )
      {
        SetEvent( signalHandle[TD] );
      }
    }
    else
    {
      HANDLE h[2];
      h[0] = signalHandle[RTT];
      h[1] = mutexHandle;
      int rc = WaitForMultipleObjects( 2, h, FALSE, INFINITE );
      recvBuffer->sendWaitFlag = false;
      if ( rc != WAIT_OBJECT_0 )
      {
        if ( rc == WAIT_OBJECT_0+1 || rc == WAIT_ABANDONED+1 )
        {
          SetStreamState( ios::failbit | ios::eofbit );
          lastError = EC_BROKEN_PIPE;
          ReleaseMutex( mutexHandle );
        }
        else
        {
          SetStreamState( ios::failbit );
          lastError = GetLastError();
        }
        return (false);
      }
    }
  }
  return (size == 0);
}