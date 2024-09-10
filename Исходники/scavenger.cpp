EXTERN_C static NTSTATUS ScvnpGetSha1(_Out_ UCHAR(&Sha1Hash)[20],
                                      _In_ void *Data, _In_ ULONG DataSize) {
  PAGED_CODE();

  BCRYPT_HASH_HANDLE hashHandle = nullptr;
  auto status = BCryptCreateHash(g_ScvnpSha1AlgorithmHandle, &hashHandle,
                                 nullptr, 0, nullptr, 0, 0);
  if (!NT_SUCCESS(status)) {
    LOG_ERROR_SAFE("BCryptCreateHash failed (%08x)", status);
    return status;
  }

  status = BCryptHashData(hashHandle, static_cast<UCHAR *>(Data), DataSize, 0);
  if (!NT_SUCCESS(status)) {
    LOG_ERROR_SAFE("BCryptHashData failed (%08x)", status);
    goto End;
  }

  static_assert(sizeof(Sha1Hash) == 20, "Size check");
  status = BCryptFinishHash(hashHandle, Sha1Hash, sizeof(Sha1Hash), 0);
  if (!NT_SUCCESS(status)) {
    LOG_ERROR_SAFE("BCryptFinishHash failed (%08x)", status);
    goto End;
  }

End:
  if (hashHandle) {
    BCryptDestroyHash(hashHandle);
  }
  return status;
}