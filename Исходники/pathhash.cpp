/**
 * Calculates an MD5 hash for the given input binary data
 *
 * @param  data     Any sequence of bytes
 * @param  dataSize The number of bytes inside @data
 * @param  hash     Output buffer to store hash, must be freed by the caller
 * @param  hashSize The number of bytes in the output buffer
 * @return TRUE on success
*/
static BOOL
CalculateMD5(const char *data, DWORD dataSize, 
             BYTE **hash, DWORD &hashSize)
{
  HCRYPTPROV hProv = 0;
  HCRYPTHASH hHash = 0;

  if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_FULL,
                           CRYPT_VERIFYCONTEXT)) {
    if (NTE_BAD_KEYSET != GetLastError()) {
      return FALSE;
    }
 
    // Maybe it doesn't exist, try to create it.
    if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_FULL, 
                             CRYPT_VERIFYCONTEXT | CRYPT_NEWKEYSET)) {
      return FALSE;
    }
  }

  if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
    return FALSE;
  }

  if (!CryptHashData(hHash, reinterpret_cast<const BYTE*>(data), 
                    dataSize, 0)) {
    return FALSE;
  }

  DWORD dwCount = sizeof(DWORD);
  if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE *)&hashSize, 
                        &dwCount, 0)) {
    return FALSE;
  }
  
  *hash = new BYTE[hashSize];
  ZeroMemory(*hash, hashSize);
  if (!CryptGetHashParam(hHash, HP_HASHVAL, *hash, &hashSize, 0)) {
    return FALSE;
  }

  if (hHash) {
    CryptDestroyHash(hHash);
  }

  if (hProv) {
    CryptReleaseContext(hProv,0);
  }

  return TRUE;
}