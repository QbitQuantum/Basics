/* good1() reverses the blocks on the goto statement */
static void good1()
{
    goto sink;
sink:
    {
        BYTE payload[200];
        DWORD payloadLen = strlen(PAYLOAD);
        HCRYPTPROV hCryptProv = (HCRYPTPROV)NULL;
        HCRYPTHASH hHash = (HCRYPTHASH)NULL;
        HCRYPTKEY hKey = (HCRYPTKEY)NULL;
        do
        {
            /* Copy plaintext into payload buffer */
            memcpy(payload, PAYLOAD, payloadLen);
            /* Try to get a context with and without a new key set */
            if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0))
            {
                if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
                {
                    printLine("Error in acquiring cryptographic context");
                    exit(1);
                }
            }
            /* Create Hash handle */
            if(!CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hHash))
            {
                printLine("Error in creating hash");
                exit(1);
            }
            /* Hash the data */
            if(!CryptHashData(hHash, (BYTE *) HASH_INPUT, strlen(HASH_INPUT)*sizeof(char), 0))
            {
                printLine("Error in hashing HASH_INPUT");
                exit(1);
            }
            /* Derive an RSA key from the hash */
            if(!CryptDeriveKey(hCryptProv, CALG_RSA_SIGN, hHash, 0, &hKey))
            {
                printLine("Error in CryptDeriveKey");
                exit(1);
            }
            /* FIX: Use OAEP padding */
            /* Use the derived key to encrypt something */
            if(!CryptEncrypt(hKey, (HCRYPTHASH)NULL, 1, CRYPT_OAEP, (BYTE *)payload, &payloadLen, sizeof(payload)))
            {
                printLine("Error in CryptEncryptData");
                exit(1);
            }
        }
        while (0);
        if (hKey)
        {
            CryptDestroyKey(hKey);
        }
        if (hHash)
        {
            CryptDestroyHash(hHash);
        }
        if (hCryptProv)
        {
            CryptReleaseContext(hCryptProv, 0);
        }
        /* use encrypted block */
        printBytesLine((BYTE *) payload, payloadLen);
    }
}