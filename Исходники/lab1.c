HCRYPTKEY generateKey(HCRYPTPROV provider, ALG_ID algid, LPTSTR password) {
  BOOL       res;
  DWORD      data;
  HCRYPTKEY  key;
  HCRYPTHASH hash;

  if (!CryptCreateHash(provider, CALG_SHA, 0, 0, &hash))
    return 0;
  data = strlen(password);
  if (!CryptHashData(hash, (BYTE *)password, data, 0)) {
    CryptDestroyHash(hash);
    return 0;
  }
  res = CryptDeriveKey(provider, algid, hash, CRYPT_EXPORTABLE, &key);
  CryptDestroyHash(hash);
  return (res ? key : 0);
}