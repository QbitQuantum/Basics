void execute_program(std::string operation, std::string fname, std::string args, bool wait) {
  SHELLEXECUTEINFOW lpExecInfo;
  tstring tstr_operation = widen(operation);
  tstring tstr_fname = widen(fname);
  tstring tstr_args = widen(args);
  lpExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
  lpExecInfo.lpFile = tstr_fname.c_str();
  lpExecInfo.fMask = SEE_MASK_DOENVSUBST | SEE_MASK_NOCLOSEPROCESS;
  lpExecInfo.hwnd = enigma::hWnd;
  lpExecInfo.lpVerb = tstr_operation.c_str();
  lpExecInfo.lpParameters = tstr_args.c_str();
  WCHAR cDir[MAX_PATH];
  GetCurrentDirectoryW(MAX_PATH, cDir);
  lpExecInfo.lpDirectory = cDir;
  lpExecInfo.nShow = SW_SHOW;
  lpExecInfo.hInstApp = (HINSTANCE)SE_ERR_DDEFAIL;  //WINSHELLAPI BOOL WINAPI result;
  ShellExecuteExW(&lpExecInfo);

  //wait until a file is finished printing
  if (wait && lpExecInfo.hProcess != NULL) {
    ::WaitForSingleObject(lpExecInfo.hProcess, INFINITE);
    ::CloseHandle(lpExecInfo.hProcess);
  }
}