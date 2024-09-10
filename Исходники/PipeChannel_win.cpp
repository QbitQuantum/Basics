bool ezPipeChannel_win::ProcessConnection()
{
  EZ_ASSERT_DEBUG(m_ThreadId == ezThreadUtils::GetCurrentThreadID(), "Function must be called from worker thread!");
  if (m_InputState.IsPending)
    m_InputState.IsPending = false;

  BOOL res = ConnectNamedPipe(m_PipeHandle, &m_InputState.Context.Overlapped);
  if (res)
  {
    //EZ_REPORT_FAILURE
    return false;
  }

  ezUInt32 error = GetLastError();
  switch (error)
  {
    case ERROR_IO_PENDING:
      m_InputState.IsPending = true;
      break;
    case ERROR_PIPE_CONNECTED:
      m_Connected = true;
      break;
    case ERROR_NO_DATA:
      return false;
    default:
      ezLog::Error("Could not connect to pipe (Error code: {0})", ezArgErrorCode(error));
      return false;
  }

  return true;
}