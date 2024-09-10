int sha256_hash(uint8_t *hash, uint8_t *data, size_t len)
{
  int res = 0;
  NTSTATUS    status;
  BCRYPT_ALG_HANDLE   sha = NULL;
  BCRYPT_HASH_HANDLE  ctx = NULL;

  status = BCryptOpenAlgorithmProvider(
              &sha,
              BCRYPT_SHA256_ALGORITHM,
              NULL,
              BCRYPT_HASH_REUSABLE_FLAG);

  status = BCryptCreateHash(
              sha,
              &ctx,
              NULL,
              0,
              NULL,
              0,
              0);

  status = BCryptHashData(
              ctx,
              (PBYTE)data,
              len,
              0);

  status = BCryptFinishHash(
              ctx,
              hash,
              32,
              0);

cleanup:

  if (NULL != ctx) {
    BCryptDestroyHash(ctx);
  }

  if( NULL != sha ) {
    BCryptCloseAlgorithmProvider(
              sha,
              0);
  }

  return res;

}