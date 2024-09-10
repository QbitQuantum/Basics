void
processSpeechInput (SpeechSynthesizer *spk) {
#if defined(__MINGW32__)
  if (speechInputHandle != INVALID_HANDLE_VALUE) {
    if (speechInputConnected ||
        (speechInputConnected = ConnectNamedPipe(speechInputHandle, NULL)) ||
        (speechInputConnected = (GetLastError() == ERROR_PIPE_CONNECTED))) {
      char buffer[0X1000];
      DWORD count;

      if (ReadFile(speechInputHandle, buffer, sizeof(buffer), &count, NULL)) {
        if (count) sayCharacters(spk, buffer, count, 0);
      } else {
        DWORD error = GetLastError();

        if (error != ERROR_NO_DATA) {
          speechInputConnected = 0;
          DisconnectNamedPipe(speechInputHandle);

          if (error != ERROR_BROKEN_PIPE)
            logWindowsSystemError("speech input FIFO read");
        }
      }
    }
  }
#elif defined(S_ISFIFO)
  if (speechInputDescriptor != -1) {
    char buffer[0X1000];
    int count = read(speechInputDescriptor, buffer, sizeof(buffer));
    if (count > 0) sayCharacters(spk, buffer, count, 0);
  }
#endif /* process speech input */
}