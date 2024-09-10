static
nsresult
GenerateRandomBytes(uint32_t aSize,
                    uint8_t* _buffer)
{
  // On Windows, we'll use its built-in cryptographic API.
#if defined(XP_WIN)
  HCRYPTPROV cryptoProvider;
  BOOL rc = CryptAcquireContext(&cryptoProvider, 0, 0, PROV_RSA_FULL,
                                CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
  if (rc) {
    rc = CryptGenRandom(cryptoProvider, aSize, _buffer);
    (void)CryptReleaseContext(cryptoProvider, 0);
  }
  return rc ? NS_OK : NS_ERROR_FAILURE;

  // On Unix, we'll just read in from /dev/urandom.
#elif defined(XP_UNIX)
  NS_ENSURE_ARG_MAX(aSize, INT32_MAX);
  PRFileDesc* urandom = PR_Open("/dev/urandom", PR_RDONLY, 0);
  nsresult rv = NS_ERROR_FAILURE;
  if (urandom) {
    int32_t bytesRead = PR_Read(urandom, _buffer, aSize);
    if (bytesRead == static_cast<int32_t>(aSize)) {
      rv = NS_OK;
    }
    (void)PR_Close(urandom);
  }
  return rv;
#endif
}