BOOL
WinLaunchChild(const wchar_t *exePath,
               int argc,
               wchar_t **argv,
               HANDLE userToken,
               HANDLE *hProcess)
{
  wchar_t *cl;
  BOOL ok;

  cl = MakeCommandLine(argc, argv);
  if (!cl) {
    return FALSE;
  }

  STARTUPINFOW si = {0};
  si.cb = sizeof(STARTUPINFOW);
  si.lpDesktop = L"winsta0\\Default";
  PROCESS_INFORMATION pi = {0};

  if (userToken == nullptr) {
    ok = CreateProcessW(exePath,
                        cl,
                        nullptr,  // no special security attributes
                        nullptr,  // no special thread attributes
                        FALSE, // don't inherit filehandles
                        0,     // creation flags
                        nullptr,  // inherit my environment
                        nullptr,  // use my current directory
                        &si,
                        &pi);
  } else {
    // Create an environment block for the process we're about to start using
    // the user's token.
    LPVOID environmentBlock = nullptr;
    if (!CreateEnvironmentBlock(&environmentBlock, userToken, TRUE)) {
      environmentBlock = nullptr;
    }

    ok = CreateProcessAsUserW(userToken,
                              exePath,
                              cl,
                              nullptr,  // no special security attributes
                              nullptr,  // no special thread attributes
                              FALSE,    // don't inherit filehandles
                              0,        // creation flags
                              environmentBlock,
                              nullptr,  // use my current directory
                              &si,
                              &pi);

    if (environmentBlock) {
      DestroyEnvironmentBlock(environmentBlock);
    }
  }

  if (ok) {
    if (hProcess) {
      *hProcess = pi.hProcess; // the caller now owns the HANDLE
    } else {
      CloseHandle(pi.hProcess);
    }
    CloseHandle(pi.hThread);
  } else {
    LPVOID lpMsgBuf = nullptr;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr,
                  GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR) &lpMsgBuf,
                  0,
                  nullptr);
    wprintf(L"Error restarting: %s\n", lpMsgBuf ? static_cast<const wchar_t*>(lpMsgBuf) : L"(null)");
    if (lpMsgBuf)
      LocalFree(lpMsgBuf);
  }

  free(cl);

  return ok;
}