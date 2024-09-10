// http://code.google.com/p/drmemory/issues/detail?id=412
TEST(CryptoTests, CryptoBasic) {
    BOOL success;
    HCRYPTPROV provider;
    success = CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_AES, 0);
    // Ask for a new keyset if this one doesn't exist.
    if (!success && GetLastError() == NTE_BAD_KEYSET) {
        success = CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_AES,
                                      CRYPT_NEWKEYSET);
    }
    ASSERT_TRUE(success) << "CryptAcquireContext failed: " << GetLastError();

    HCRYPTKEY key;
    success = CryptGenKey(provider, CALG_AES_256, CRYPT_EXPORTABLE, &key);
    ASSERT_TRUE(success) << "CryptGenKey failed: " << GetLastError();

    // Get the key size.
    DWORD buffer_size = 0;
    success = CryptExportKey(key, 0, PLAINTEXTKEYBLOB, 0, NULL, &buffer_size);
    ASSERT_TRUE(success) << "CryptExportKey 1 failed: " << GetLastError();

    // Export the key.
    BYTE *buffer = new BYTE[buffer_size];
    success = CryptExportKey(key, 0, PLAINTEXTKEYBLOB, 0, buffer, &buffer_size);
    ASSERT_TRUE(success) << "CryptExportKey 2 failed: " << GetLastError();

    plaintext_blob_t *blob = (plaintext_blob_t*)buffer;
    ASSERT_EQ(buffer_size - offsetof(plaintext_blob_t, rgbKeyData), blob->cbKeySize);

    // Check that the rest of it is initialized.  Copy the buffer and compare it
    // against itself to trigger the uninit checks.
    BYTE *key_copy = new BYTE[blob->cbKeySize];
    memcpy(key_copy, blob->rgbKeyData, blob->cbKeySize);
    ASSERT_EQ(0, memcmp(blob->rgbKeyData, key_copy, blob->cbKeySize));
    delete [] key_copy;

    delete [] buffer;
    CryptDestroyKey(key);
    CryptReleaseContext(provider, 0);
}