nsresult LaunchHelper(nsAutoString& aPath, nsAutoString& aParams) {
  SHELLEXECUTEINFOW executeInfo = {0};

  executeInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
  executeInfo.hwnd = NULL;
  executeInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
  executeInfo.lpDirectory = NULL;
  executeInfo.lpFile = aPath.get();
  executeInfo.lpParameters = aParams.get();
  executeInfo.nShow = SW_SHOWNORMAL;

  if (ShellExecuteExW(&executeInfo))
    // Block until the program exits
    WaitForSingleObject(executeInfo.hProcess, INFINITE);
  else
    return NS_ERROR_ABORT;

  // We're going to ignore errors here since there's nothing we can do about
  // them, and helper.exe seems to return non-zero ret on success.
  return NS_OK;
}