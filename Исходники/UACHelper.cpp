/**
 * Opens a user token for the given session ID
 *
 * @param  sessionID  The session ID for the token to obtain
 * @return A handle to the token to obtain which will be primary if enough
 *         permissions exist.  Caller should close the handle.
 */
HANDLE
UACHelper::OpenUserToken(DWORD sessionID)
{
  HMODULE module = LoadLibraryW(L"wtsapi32.dll");
  HANDLE token = nullptr;
  decltype(WTSQueryUserToken)* wtsQueryUserToken = 
    (decltype(WTSQueryUserToken)*) GetProcAddress(module, "WTSQueryUserToken");
  if (wtsQueryUserToken) {
    wtsQueryUserToken(sessionID, &token);
  }
  FreeLibrary(module);
  return token;
}