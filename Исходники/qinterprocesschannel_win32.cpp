/*!
    \brief Send a message to server instance
*/
void QInterProcessChannel::sendMessage(const QByteArray& msg) {
  if (msg.count()) {
    // a lot of simultaneous clients cause that pipe sometimes omits
    // some of these clients despite results of writing functions are ok ;/
    // workaround: reserve mutex, wait 100ms before every write operation

    HANDLE mutex = CreateMutexA(NULL, FALSE, qPrintable(blockerMutexStr));
    WaitForSingleObject(mutex, INFINITE);
    Sleep(100);

    HANDLE hPipe;

    // loop to get pipe's handle
    for (;;) {
      hPipe = CreateFileA(qPrintable(pipeName), GENERIC_WRITE, 0, NULL,
                          OPEN_EXISTING, 0, NULL);

      if (hPipe != INVALID_HANDLE_VALUE) break;

      if (GetLastError() != ERROR_PIPE_BUSY) {
        ReleaseMutex(mutex);
        return;
      }

      // wait max 1s and retry
      WaitNamedPipeA(qPrintable(pipeName), 1000);
    }

    // ok, now we have pipe's handle, we can prepare buffers and write to the
    // pipe

    char buffer[bufferSize];
    strncpy(buffer, msg.constData(), bufferSize);
    buffer[bufferSize - 1] = 0;

    DWORD bytesWritten;
    bool writeSuccess =
        WriteFile(hPipe, buffer, strlen(buffer) + 1, &bytesWritten, NULL);

    if (!writeSuccess) {
      ReleaseMutex(mutex);
      return;
    }

    CloseHandle(hPipe);
    ReleaseMutex(mutex);
  } else {
    // qWarning("::sendMessage(%d): Empty messages are not carried out...",
    // GetCurrentProcessId());
  }
}