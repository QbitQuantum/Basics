/**
 *
 *  Generate System key from pass phrase -> level 2
 *  Derives 128-bit value from MD5
 *
 */
BOOL SystemKey::SetFromPassword (std::wstring pwd) {
  HCRYPTPROV hProv;
  HCRYPTHASH hHash;

  if (CryptAcquireContext (&hProv, NULL, NULL, PROV_RSA_FULL,
      CRYPT_VERIFYCONTEXT)) {
    if (CryptCreateHash (hProv, CALG_MD5, 0, 0, &hHash)) {
      if (CryptHashData (hHash, (PBYTE)pwd.c_str(),
          pwd.length() * sizeof(wchar_t), 0)) {

        DWORD dwHashLen = SYSTEM_KEY_LEN;
        CryptGetHashParam (hHash, HP_HASHVAL, key, &dwHashLen, 0);
        dwError = GetLastError();
      }
      CryptDestroyHash (hHash);
    } else {
      dwError = GetLastError ();
    }
    CryptReleaseContext (hProv, 0);
  } else {
    dwError = GetLastError ();
  }
  return dwError == ERROR_SUCCESS;
}