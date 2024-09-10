/* Return a copy of ORIG, encrypted using the Windows CryptoAPI and
   allocated from POOL. */
const svn_string_t *
encrypt_data(const svn_string_t *orig,
             apr_pool_t *pool)
{
  DATA_BLOB blobin;
  DATA_BLOB blobout;
  const svn_string_t *crypted = NULL;

  blobin.cbData = orig->len;
  blobin.pbData = (BYTE *)orig->data;
  if (CryptProtectData(&blobin, description, NULL, NULL, NULL,
                       CRYPTPROTECT_UI_FORBIDDEN, &blobout))
    {
      crypted = svn_string_ncreate((const char *)blobout.pbData,
                                   blobout.cbData, pool);
      LocalFree(blobout.pbData);
    }
  return crypted;
}