bool VerifySHA1Signature(const void *data, size_t dataLen, const char *hexSignature, const void *pubkey, size_t pubkeyLen)
{
    HCRYPTPROV hProv = 0;
    HCRYPTKEY hPubKey = 0;
    HCRYPTHASH hHash = 0;
    BOOL ok = false;
    ScopedMem<BYTE> signature;
    size_t signatureLen;

#define Check(val) if ((ok = (val)) == FALSE) goto CleanUp
    Check(ExtractSignature(hexSignature, data, dataLen, signature, signatureLen));
    Check(CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT));
    Check(CryptImportKey(hProv, (const BYTE *)pubkey, (DWORD)pubkeyLen, 0, 0, &hPubKey));
    Check(CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash));
#ifdef _WIN64
    for (; dataLen > DWORD_MAX; data = (const BYTE *)data + DWORD_MAX, dataLen -= DWORD_MAX) {
        Check(CryptHashData(hHash, (const BYTE *)data, DWORD_MAX, 0));
    }
#endif
    Check(dataLen <= DWORD_MAX && pubkeyLen <= DWORD_MAX && signatureLen <= DWORD_MAX);
    Check(CryptHashData(hHash, (const BYTE *)data, (DWORD)dataLen, 0));
    Check(CryptVerifySignature(hHash, signature, (DWORD)signatureLen, hPubKey, NULL, 0));
#undef Check

CleanUp:
    if (hHash)
        CryptDestroyHash(hHash);
    if (hProv)
        CryptReleaseContext(hProv, 0);
    return ok;
}