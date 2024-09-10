nsresult
NamedPipeInfo::Connect(const nsACString& aPath)
{
  MOZ_ASSERT(PR_GetCurrentThread() == gSocketThread);

  HANDLE pipe;
  nsAutoCString path(aPath);

  pipe = CreateFileA(path.get(),
                     GENERIC_READ | GENERIC_WRITE,
                     FILE_SHARE_READ | FILE_SHARE_WRITE,
                     nullptr,
                     OPEN_EXISTING,
                     FILE_FLAG_OVERLAPPED,
                     nullptr);

  if (pipe == INVALID_HANDLE_VALUE) {
    LOG_NPIO_ERROR("[%p] CreateFile error (%d)", this, GetLastError());
    return NS_ERROR_FAILURE;
  }

  DWORD pipeMode = PIPE_READMODE_MESSAGE;
  if (!SetNamedPipeHandleState(pipe, &pipeMode, nullptr, nullptr)) {
    LOG_NPIO_ERROR("[%p] SetNamedPipeHandleState error (%d)",
                   this,
                   GetLastError());
    CloseHandle(pipe);
    return NS_ERROR_FAILURE;
  }

  nsresult rv = mNamedPipeService->AddDataObserver(pipe, this);
  if (NS_WARN_IF(NS_FAILED(rv))) {
    CloseHandle(pipe);
    return rv;
  }

  HANDLE readEvent = CreateEventA(nullptr, TRUE, TRUE, "NamedPipeRead");
  if (NS_WARN_IF(!readEvent || readEvent == INVALID_HANDLE_VALUE)) {
    CloseHandle(pipe);
    return NS_ERROR_FAILURE;
  }

  HANDLE writeEvent = CreateEventA(nullptr, TRUE, TRUE, "NamedPipeWrite");
  if (NS_WARN_IF(!writeEvent || writeEvent == INVALID_HANDLE_VALUE)) {
    CloseHandle(pipe);
    CloseHandle(readEvent);
    return NS_ERROR_FAILURE;
  }

  mPipe = pipe;
  mReadOverlapped.hEvent = readEvent;
  mWriteOverlapped.hEvent = writeEvent;
  return NS_OK;
}