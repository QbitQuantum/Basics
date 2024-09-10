HRESULT TCUserAccount::SetRunAsUser(LPCTSTR szAppID, LPCTSTR szUserName, LPCTSTR szPassword)
{
  // Not supported under Windows9x
  if (IsWin9x())
    return S_FALSE;

  // Copy the specified AppID string to a non-const wide string
  USES_CONVERSION;
  UINT cchAppID = max(_tcslen(szAppID), 48) + 1;
  LPWSTR pszAppID = (LPWSTR)_alloca(cchAppID * sizeof(WCHAR));
  wcscpy(pszAppID, T2CW(szAppID));

  // Resolve the specified string to an AppID
  HKEY hkey = NULL;
  RETURN_FAILED(ResolveAppID(pszAppID, &hkey));
  CRegKey key;
  key.Attach(hkey);

  // Ensure that we have a domain name
  LPCTSTR pszUserName = szUserName;
  LPCTSTR pszWhack = _tcschr(szUserName, TEXT('\\'));
  if (!pszWhack || pszWhack == szUserName ||
    (pszWhack == (szUserName + 1) && TEXT('.') == *szUserName))
  {
    // Get the domain name and user name
    TCCoTaskPtr<LPTSTR> spszDomainName;
    RETURN_FAILED(GetSID(szUserName, NULL, &spszDomainName));
    LPCTSTR pszUserOnly = pszWhack ? pszWhack + 1 : szUserName;

    // Concatenate the user name onto the domain name
    UINT cch = _tcslen(spszDomainName) + _tcslen(pszUserOnly) + 2;
    LPTSTR pszUserNameTemp = (LPTSTR)_alloca(cch * sizeof(TCHAR));
    _tcscpy(pszUserNameTemp, spszDomainName);
    _tcscat(pszUserNameTemp, TEXT("\\"));
    _tcscat(pszUserNameTemp, pszUserOnly);
    pszUserName = pszUserNameTemp;
  }

  // Open the local security policy
  TCLsaHandle           hPolicy;
  LSA_OBJECT_ATTRIBUTES oa = {sizeof(oa)};
  RETURN_FAILED(LsaOpenPolicy(NULL, &oa, POLICY_CREATE_SECRET, &hPolicy));

  // Format the key string
  WCHAR szKey[48] = L"SCM:";
  wcscat(szKey, pszAppID);

  // Create an LSA_UNICODE_STRING for the key name
  LSA_UNICODE_STRING lsaKeyString;
  lsaKeyString.Length        = (wcslen(szKey) + 1) * sizeof(WCHAR);
  lsaKeyString.MaximumLength = lsaKeyString.Length;
  lsaKeyString.Buffer        = szKey;

  // Copy the specified password string to a non-const wide string
  UINT cchPassword = _tcslen(szPassword);
  LPWSTR pszPassword = (LPWSTR)_alloca((cchPassword + 1) * sizeof(WCHAR));
  wcscpy(pszPassword, T2CW(szPassword));

  // Create an LSA_UNICODE_STRING for the password string
  LSA_UNICODE_STRING lsaPasswordString;
  lsaPasswordString.Length        = (cchPassword + 1) * sizeof(WCHAR);
  lsaPasswordString.MaximumLength = lsaPasswordString.Length;
  lsaPasswordString.Buffer        = pszPassword;

  // Store the specified password
  RETURN_FAILED(LsaStorePrivateData(hPolicy, &lsaKeyString,
    &lsaPasswordString));

  // Set the specified user name as the RunAs user for the AppID
  // mdvalley: Another former SetStringValue
  LONG lr = key.SetValue(TEXT("RunAs"), pszUserName);
  if (lr)
    return HRESULT_FROM_WIN32(lr);

  // Indicate success
  return S_OK;
}