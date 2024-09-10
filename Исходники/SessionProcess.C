void SessionProcess::exec(const Configuration& config,
			  boost::function<void (bool)> onReady)
{
#ifndef WT_WIN32
  std::string parentPortOption = std::string("--parent-port=")
    + boost::lexical_cast<std::string>(acceptor_->local_endpoint().port());
  const std::vector<std::string> &options = config.options();
  const char **c_options = new const char*[options.size() + 2];
  std::size_t i = 0;
  for (; i < options.size(); ++i) {
    c_options[i] = options[i].c_str();
  }
  c_options[i] = parentPortOption.c_str();
  ++i;
  c_options[i] = 0;

  pid_ = fork();
  if (pid_ < 0) {
    LOG_ERROR("failed to fork dedicated session process, error code: " << errno);
    stop();
    if (!onReady.empty()) {
      onReady(false);
    }
    return;
  } else if (pid_ == 0) {
#ifdef WT_THREADED
    sigset_t mask;
    sigfillset(&mask);
    pthread_sigmask(SIG_UNBLOCK, &mask, 0);
#endif // WT_THREADED

    execv(c_options[0], const_cast<char *const *>(c_options));
    // An error occurred, this should not be reached
    exit(1);
  }

  delete[] c_options;
#else // WT_WIN32
  STARTUPINFOW startupInfo;
  ZeroMemory(&startupInfo, sizeof(startupInfo));
  startupInfo.cb = sizeof(startupInfo);

  std::wstring commandLine = GetCommandLineW();
  commandLine += L" --parent-port=" + boost::lexical_cast<std::wstring>(acceptor_->local_endpoint().port());
  LPWSTR c_commandLine = new wchar_t[commandLine.size() + 1];
  wcscpy(c_commandLine, commandLine.c_str());

  if(!CreateProcessW(0, c_commandLine, 0, 0, true,
      0, 0, 0, &startupInfo, &processInfo_)) {
    LOG_ERROR("failed to start dedicated session process, error code: " << GetLastError());
    stop();
    if (!onReady.empty()) {
      onReady(false);
    }
  }
  delete c_commandLine;
#endif // WT_WIN32
}