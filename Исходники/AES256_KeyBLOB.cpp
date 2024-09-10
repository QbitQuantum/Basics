BOOL Create_AES256_KeyBLOB(
  HCRYPTPROV    prov,               // CSP
  unsigned char *pbPassword,        // input (Password for Key and IV)
  DWORD         cbPassword,         // input (length)
  unsigned char *pbSalt,            // input (Salt for Key and IV)
  DWORD         cbSalt,             // input (length 8 or 16)
  AES_256_KEY_BLOB  *blob,          // output
  unsigned char pbIV[16]            // output (length fixed 16)
)
{
  BOOL bStatus = FALSE;
  DWORD dwError = 0;
  EVERIFY(prov && pbPassword && pbSalt && blob && pbIV);
  const int N = 3;
  BYTE hashdata[N][HASH_MD5_LEN];
  for(int i = 0; i < N; i++){
    HCRYPTHASH hash = NULL;
    EVERIFY(CryptCreateHash(prov, CALG_MD5, 0, 0, &hash));
    BYTE hashwork[HASH_MD5_LEN * 64];
    EVERIFY(HASH_MD5_LEN + cbPassword + cbSalt <= sizeof(hashwork));
    DWORD hashlen; // must get with HP_HASHVAL (not use HP_HASHSIZE)
    if(!i) hashlen = 0;
    else CopyMemory(hashwork, hashdata[i - 1], hashlen = HASH_MD5_LEN);
    CopyMemory(hashwork + hashlen, pbPassword, cbPassword);
    CopyMemory(hashwork + hashlen + cbPassword, pbSalt, cbSalt);
    EVERIFY(CryptHashData(hash, hashwork, hashlen + cbPassword + cbSalt, 0));
    EVERIFY(CryptGetHashParam(hash, HP_HASHVAL, NULL, &hashlen, 0));
    EVERIFY(hashlen == HASH_MD5_LEN);
    EVERIFY(CryptGetHashParam(hash, HP_HASHVAL, hashdata[i], &hashlen, 0));
    if(hash) EVERIFY(CryptDestroyHash(hash));
  }
  blob->hdr.bType = PLAINTEXTKEYBLOB;
  blob->hdr.bVersion = CUR_BLOB_VERSION;
  blob->hdr.reserved = 0;
  blob->hdr.aiKeyAlg = CALG_AES_256;
  blob->cbKeySize = 32; // sizeof(blob->pbDerivedKey) is the size of pointer
  CopyMemory(blob->pbDerivedKey, hashdata[0], HASH_MD5_LEN);
  CopyMemory(blob->pbDerivedKey + HASH_MD5_LEN, hashdata[1], HASH_MD5_LEN);
  CopyMemory(pbIV, hashdata[2], HASH_MD5_LEN);
  bStatus = TRUE;

done:
  return bStatus;
}