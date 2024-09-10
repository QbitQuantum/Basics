ErrorCode ProcessSpawner::run(std::function<bool()> preExecAction) {
  std::vector<WCHAR> commandLine;
  std::vector<WCHAR> environment;
  STARTUPINFOW si;
  PROCESS_INFORMATION pi;

  commandLine.push_back(L'"');
  std::wstring wideExecutablePath =
      Platform::NarrowToWideString(_executablePath);
  commandLine.insert(commandLine.end(), wideExecutablePath.begin(),
                     wideExecutablePath.end());
  commandLine.push_back(L'"');
  for (auto const &arg : _arguments) {
    commandLine.push_back(L' ');
    commandLine.push_back(L'"');
    std::wstring wideArg = Platform::NarrowToWideString(arg);
    for (auto const &ch : wideArg) {
      if (ch == L'"')
        commandLine.push_back(L'\\');
      commandLine.push_back(ch);
    }
    commandLine.push_back(L'"');
  }
  commandLine.push_back(L'\0');

  for (auto const &env : _environment) {
    std::wstring wideKey = Platform::NarrowToWideString(env.first);
    std::wstring wideValue = Platform::NarrowToWideString(env.second);
    environment.insert(environment.end(), wideKey.begin(), wideKey.end());
    environment.push_back(L'=');
    environment.insert(environment.end(), wideValue.begin(), wideValue.end());
    environment.push_back(L'\0');
  }
  environment.push_back(L'\0');

  memset(&si, 0, sizeof si);
  si.cb = sizeof si;

  // Note(sas): Not sure if we want DEBUG_ONLY_THIS_PROCESS here. Will need to
  // check back later.
  std::wstring wideWorkingDirectory =
      Platform::NarrowToWideString(_workingDirectory);
  BOOL result = CreateProcessW(
      nullptr, commandLine.data(), nullptr, nullptr, false,
      DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS | CREATE_UNICODE_ENVIRONMENT,
      environment.data(),
      wideWorkingDirectory.empty() ? nullptr : wideWorkingDirectory.c_str(),
      &si, &pi);

  _processHandle = pi.hProcess;
  _pid = pi.dwProcessId;

  return result ? kSuccess : kErrorUnknown;
}