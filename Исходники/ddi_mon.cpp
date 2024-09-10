// The hook handler for ExFreePool(). Logs if ExFreePool() is called from where
// not backed by any image
_Use_decl_annotations_ static VOID DdimonpHandleExFreePool(PVOID p) {
  const auto original = DdimonpFindOrignal(DdimonpHandleExFreePool);
  original(p);

  // Is inside image?
  auto return_addr = _ReturnAddress();
  if (UtilPcToFileHeader(return_addr)) {
    return;
  }

  HYPERPLATFORM_LOG_INFO_SAFE("%p: ExFreePool(P= %p)", return_addr, p);
}