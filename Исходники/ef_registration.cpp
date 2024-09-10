/**
* Once registered, this is a simple way to retrieve our 
* event framework cookie.
*/
HRESULT RetrieveRegistrationCookie(long* cookie) {
  ATLASSERT(cookie != NULL);
  CRegKey key;
  LONG res = key.Open(HKEY_CURRENT_USER, CONSOLE_CONFIG_KEY, KEY_READ);
  if (res != ERROR_SUCCESS)
    return AtlHresultFromWin32(res);

  res = key.QueryDWORDValue(COOKIE_VALUE,
                            *reinterpret_cast<DWORD*>(cookie));
  ATLASSERT(res == ERROR_SUCCESS);
  return AtlHresultFromWin32(res);
}