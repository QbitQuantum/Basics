int LauncherStartup(const wchar_t *args, int channel) {
  wchar_t pwszPath[UNC_MAX_PATH];
  GetModuleFileNameW(nullptr, pwszPath, UNC_MAX_PATH);
  PathRemoveFileSpecW(pwszPath);
  PathRemoveFileSpecW(pwszPath);
  PathRemoveFileSpecW(pwszPath);
  std::wstring psfile = pwszPath;
  switch (channel) {
  case kOpenEnvironment:
    psfile += L"\\bin\\ClangBuilderEnvironment.ps1";
    break;
  case kBaseBuilder:
    psfile += L"\\bin\\ClangBuilderManager.ps1";
    break;
  case kNinjaBootstrap:
    psfile += L"\\bin\\ClangBuilderBootstrap.ps1";
    break;
  default:
    psfile = L"Not support channel value: " + std::to_wstring(channel);
    OutErrorMessage(psfile.c_str(), L"Not support clangbuilder channel !");
    return -2;
  }
  if (!PathFileExistsW(psfile.c_str())) {
    OutErrorMessage(psfile.c_str(), L"PathFileExists return false");
    return -1;
  }

  if (SHGetFolderPathW(NULL, CSIDL_SYSTEM, NULL, 0, pwszPath) != S_OK) {
    return -1;
  }
  auto length = wcslen(pwszPath);
  StringCchCatW(pwszPath, UNC_MAX_PATH - length,
                L"\\WindowsPowerShell\\v1.0\\powershell.exe ");
  length = wcslen(pwszPath);
  auto offsetPtr = pwszPath + length;
  StringCchPrintfW(offsetPtr, UNC_MAX_PATH - length,
                   L" -NoLogo -NoExit   -File \"%s\" %s", psfile.c_str(), args);
  PROCESS_INFORMATION pi;
  STARTUPINFO si;
  ZeroMemory(&si, sizeof(si));
  ZeroMemory(&pi, sizeof(pi));
  si.cb = sizeof(si);
  si.dwFlags = STARTF_USESHOWWINDOW;
  si.wShowWindow = SW_SHOW;
  if (CreateProcessW(nullptr, pwszPath, NULL, NULL, FALSE,
                     CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL,
                     &si, &pi)) {
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
  }
  return GetLastError();
}