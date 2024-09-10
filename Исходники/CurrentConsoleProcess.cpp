void CurrentConsoleProcess::start()
{
  cleanup();

  DWORD sessionId = WTS::getActiveConsoleSessionId(m_log);
  m_log->info(_T("Try to start \"%s %s\" process as current user at %d session"),
            m_path.getString(),
            m_args.getString(),
            sessionId);

  PROCESS_INFORMATION pi;
  STARTUPINFO sti;
  getStartupInfo(&sti);

  m_log->debug(_T("sti: cb = %d, hStdError = %p, hStdInput = %p,")
             _T(" hStdOutput = %p, dwFlags = %u"),
             (unsigned int)sti.cb,
             (void *)sti.hStdError,
             (void *)sti.hStdInput,
             (void *)sti.hStdOutput,
             (unsigned int)sti.dwFlags);

  HANDLE procHandle = GetCurrentProcess();

  HANDLE token, userToken;

  try {
    m_log->debug(_T("Try OpenProcessToken(%p, , )"),
               (void *)procHandle);
    if (OpenProcessToken(procHandle, TOKEN_DUPLICATE, &token) == 0) {
      throw SystemException();
    }

    m_log->debug(_T("Try DuplicateTokenEx(%p, , , , , )"),
               (void *)token);
    if (DuplicateTokenEx(token,
      MAXIMUM_ALLOWED,
      0,
      SecurityImpersonation,
      TokenPrimary,
      &userToken) == 0) {
        throw SystemException();
    }

    m_log->debug(_T("Try SetTokenInformation(%p, , , )"),
               (void *)userToken);
    if (SetTokenInformation(userToken,
      (TOKEN_INFORMATION_CLASS) TokenSessionId,
      &sessionId,
      sizeof(sessionId)) == 0) {
        throw SystemException();
    }

    StringStorage commandLine = getCommandLineString();

    m_log->debug(_T("Try CreateProcessAsUser(%p, 0, %s, 0, 0, %d, NORMAL_PRIORITY_CLASS, 0, 0,")
               _T(" sti, pi)"),
               (void *)userToken, commandLine.getString(),
               (int)m_handlesIsInherited);
    if (CreateProcessAsUser(userToken, 0, (LPTSTR) commandLine.getString(),
      0, 0, m_handlesIsInherited, NORMAL_PRIORITY_CLASS, 0, 0, &sti,
      &pi) == 0) {
        throw SystemException();
    }
    m_log->info(_T("Created \"%s\" process at %d windows session"),
              commandLine.getString(), sessionId);
  } catch (SystemException &sysEx) {
    m_log->error(_T("Failed to start process with %d error"), sysEx.getErrorCode());
    throw;
  }

  //
  // FIXME: Leak.
  //

  CloseHandle(userToken);
  CloseHandle(token);

  m_hThread = pi.hThread;
  m_hProcess = pi.hProcess;
}