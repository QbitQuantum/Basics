DWORD aes_Encrypt(LPBYTE key, DWORD SizeKey, LPBYTE iv, LPBYTE InData, DWORD SizeInData, LPBYTE *OutData)
{
    HCRYPTPROV provider = NULL;
    HCRYPTKEY hKey = NULL;
    DWORD SizeData = SizeInData;
    DWORD SizeBuffer = 0;
    DWORD Result = -1;

    do {
        if (!OpenCryptContext(&provider)) {
            xstrerror("CryptAcquireContext()");
            break;
        }

        // 创建 Key
        struct keyBlob {
            BLOBHEADER hdr;
            DWORD cbKeySize;
            BYTE rgbKeyData[32];                // FOR AES-256 = 32
        } keyBlob;
        keyBlob.hdr.bType = PLAINTEXTKEYBLOB;
        keyBlob.hdr.bVersion = CUR_BLOB_VERSION;
        keyBlob.hdr.reserved = 0;
        keyBlob.hdr.aiKeyAlg = CALG_AES_256;    // FOR AES-256 = CALG_AES_256
        keyBlob.cbKeySize = 32;                    // FOR AES-256 = 32
        CopyMemory(keyBlob.rgbKeyData, key, keyBlob.cbKeySize);

        if (!CryptImportKey(provider, (BYTE*)(&keyBlob), sizeof(keyBlob), NULL, 0, &hKey)) {
            break;
        }

        DWORD dwMode = CRYPT_MODE_CBC, dwPadding = PKCS5_PADDING;

        if (!CryptSetKeyParam(hKey, KP_IV, (BYTE*)iv, 0)) {
            break;
        }

        if (!CryptSetKeyParam(hKey, KP_MODE, reinterpret_cast<BYTE*>(&dwMode), 0)) {
            break;
        }

        if (!CryptSetKeyParam(hKey, KP_PADDING, reinterpret_cast<BYTE*>(&dwPadding), 0)) {
            break;
        }

        DWORD block_size = GetCipherBlockSize(hKey);
        DWORD data_len = SizeInData;
        SizeBuffer = data_len + block_size;
        *OutData = (LPBYTE)xmalloc(SizeBuffer);

        if (*OutData == NULL)
            break;

        memcpy(*OutData, InData, SizeInData);

        if (!CryptEncrypt(hKey, NULL, TRUE, 0, *OutData, &SizeData, SizeBuffer)) {
            xstrerror("CryptEncrypt()");
            break;
        }

        Result = SizeData;
    } while (0);

    if (hKey != NULL) {
        CryptDestroyKey(hKey);
    }

    if (provider != NULL)   {
        CryptReleaseContext(provider, 0);
    }

    if (OutData != NULL && !Result)
        xfree(*OutData);

    return Result;
}