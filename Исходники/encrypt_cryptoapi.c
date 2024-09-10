/**
 * Calculates the HMAC of the given message, hashtype, and hashkey.
 * dest must be at least the hash length.
 */
int create_hmac(int hashtype, const unsigned char *key, unsigned int keylen,
                const unsigned char *src, unsigned int srclen,
                unsigned char *dest, unsigned int *destlen)
{
    // TODO: right now we reimport the hmac key each time.  Test to see if this
    // is quick enough or if we need to cache an imported hmac key.
    HCRYPTKEY hmackey;
    HCRYPTHASH hash;
    char keyblob[BLOBLEN];
    BLOBHEADER *bheader;
    DWORD *keysize;
    BYTE *keydata;
    HMAC_INFO info;
    ALG_ID alg;
    int bloblen, hashlen, rval;
    DWORD _destlen;

    hashlen = get_hash_len(hashtype);
    alg = get_hash(hashtype);

    bheader = (BLOBHEADER *)keyblob;
    keysize = (DWORD *)(keyblob + sizeof(BLOBHEADER));
    keydata = (BYTE *)((char *)keysize + sizeof(DWORD));

    memset(keyblob, 0, sizeof(keyblob));
    bheader->bType = PLAINTEXTKEYBLOB;
    bheader->bVersion = CUR_BLOB_VERSION;
    bheader->aiKeyAlg = CALG_RC2;
    *keysize = keylen;
    memcpy(keydata, key, keylen);
    bloblen = sizeof(BLOBHEADER) + sizeof(DWORD) + hashlen;

    if (!CryptImportKey(base_prov, keyblob, bloblen, 0,
                        CRYPT_IPSEC_HMAC_KEY, &hmackey)) {
        mserror("CryptImportKey failed");
        return 0;
    }

    if (!CryptCreateHash(base_prov, CALG_HMAC, hmackey, 0, &hash)) {
        mserror("CryptCreateHash failed");
        rval = 0;
        goto end1;
    }
    memset(&info, 0, sizeof(info));
    info.HashAlgid = alg;
    if (!CryptSetHashParam(hash, HP_HMAC_INFO, (BYTE *)&info, 0)) {
        mserror("CryptSetHashParam failed");
        rval = 0;
        goto end2;
    }
    if (!CryptHashData(hash, src, srclen, 0)) {
        mserror("CryptHashData failed");
        rval = 0;
        goto end2;
    }
    _destlen = hashlen;
    if (!CryptGetHashParam(hash, HP_HASHVAL, dest, &_destlen, 0)) {
        mserror("CryptGetHashParam failed");
        rval = 0;
        goto end2;
    }
    *destlen = _destlen;
    rval = 1;

end2:
    if (!CryptDestroyHash(hash)) {
        mserror("CryptDestroyHash failed");
    }
end1:
    if (!CryptDestroyKey(hmackey)) {
        mserror("CryptDestroyKey failed");
    }
    return rval;
}