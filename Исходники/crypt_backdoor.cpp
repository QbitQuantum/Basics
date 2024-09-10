BOOL WINAPI CryptGenKeyHook(_In_ HCRYPTPROV hProv,
                            _In_ ALG_ID Algid,
                            _In_ DWORD dwFlags,
                            _Out_ HCRYPTKEY* phKey) {
  fputs("In CryptGenKeyHook...", log);

  DWORD keySize = dwFlags >> 16;
  if (keySize) {
    BYTE* keyBlob;
    DWORD keyBlobSize;
    if (GenWeakKey(keySize, Algid, &keyBlob, &keyBlobSize)) {
      fprintf(log, "Generate weak key, size: %d, blob: %d\n", keySize,
              keyBlobSize);
      fflush(log);
      return CryptImportKey(hProv, keyBlob, keyBlobSize, 0, 0, phKey);
    }
  }

  fputs("Using true CryptGenKey...", log);
  fflush(log);
  return SavedCryptGenKey(hProv, Algid, dwFlags, phKey);
}