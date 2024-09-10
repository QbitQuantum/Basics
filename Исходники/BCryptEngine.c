// Argh! This is one more of these OpenSSL-style schizophrenic APIs, where
// depending on whether a parameter is NULL or not, different values are
// expected...
static int bcrypt_derive(EVP_PKEY_CTX *ctx, unsigned char *outKey, size_t *outKeyLen)
{
  *outKeyLen = X25519_KEYLEN;

  // First usage: a query for how many bytes the caller needs to allocate.
  if (outKey == NULL)
    return 1;

  // Second usage: writing into outkey the derived secret.

  // Note: this does NOT give you the actual bytes for the SECRET_HANDLE. (See
  // http://stackoverflow.com/questions/87694/im-using-wincrypt-for-diffie-hellman-can-i-export-the-shared-secret-in-plain
  // for something vaguely related). BCryptExportKey works for a KEY_HANDLE, not
  // a SECRET_HANDLE... and the type is defined as void* in the public Windows
  // 10 headers.
  bcrypt_x25519_key *pkey = EVP_PKEY_get0(EVP_PKEY_CTX_get0_pkey(ctx));
  bcrypt_x25519_key *peerkey = EVP_PKEY_get0(EVP_PKEY_CTX_get0_peerkey(ctx));
  BCRYPT_SECRET_HANDLE hSecret = NULL;
  if (!NT_SUCCESS(BCryptSecretAgreement(pkey->pair, peerkey->pair, &hSecret, 0))) {
    fprintf(stderr, "Cannot compute agreement\n");
    return 0;
  }
  // Writing out a dummy value in the meanwhile...
  memset(outKey, 0, X25519_KEYLEN);

  return 1;
}