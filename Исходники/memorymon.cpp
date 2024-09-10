// Locate MmPfnDatabase
_Use_decl_annotations_ static NTSTATUS MmonpInitializeMmPfnDatabase() {
  PAGED_CODE();

  if (IsX64()) {
    g_mmonp_MmPfnDatabase = reinterpret_cast<void *>(0xfffffa8000000000);
  } else {
    const auto p_MmGetVirtualForPhysical = reinterpret_cast<UCHAR *>(
        UtilGetSystemProcAddress(L"MmGetVirtualForPhysical"));
    if (!p_MmGetVirtualForPhysical) {
      return STATUS_PROCEDURE_NOT_FOUND;
    }

    RTL_OSVERSIONINFOW os_version = {};
    auto status = RtlGetVersion(&os_version);
    if (!NT_SUCCESS(status)) {
      return status;
    }
    if (os_version.dwMajorVersion == 6 && os_version.dwMinorVersion == 1) {
      // Windows 7 (No PAE)
      // 6B C0 18                          imul    eax, 18h
      // 8B 0D 14 28 56 00                 mov     ecx, ds:_MmPfnDatabase
      static const UCHAR kPatternWin7[] = {
          0x6B, 0xC0, 0x18, 0x8B, 0x0D,
      };
      // Windows 7 (PAE)
      // 6B C0 1C                          imul    eax, 1Ch
      // 8B 0D 14 28 56 00                 mov     ecx, ds:_MmPfnDatabase
      static const UCHAR kPatternWin7Pae[] = {
          0x6B, 0xC0, 0x1C, 0x8B, 0x0D,
      };
      const auto is_pae_enabled = Cr4{__readcr4()}.fields.pae;
      const auto pattern = (is_pae_enabled) ? kPatternWin7Pae : kPatternWin7;
      const auto size =
          (is_pae_enabled) ? sizeof(kPatternWin7Pae) : sizeof(kPatternWin7);
      auto found = reinterpret_cast<UCHAR *>(
          UtilMemMem(p_MmGetVirtualForPhysical, 0x20, pattern, size));
      if (found) {
        found += size;
        const auto address = *reinterpret_cast<ULONG_PTR *>(found);
        g_mmonp_MmPfnDatabase = *reinterpret_cast<void **>(address);
      }
    } else if ((os_version.dwMajorVersion == 6 &&
                os_version.dwMinorVersion == 3) ||
               (os_version.dwMajorVersion == 10 &&
                os_version.dwMinorVersion == 0)) {
      // Windows 8.1 and 10
      // C1 F8 0C                          sar     eax, 0Ch
      // A1 08 B7 62 00                    mov     eax, ds:_MmPfnDatabase
      static const UCHAR kPatternWin81And10[] = {
          0xC1, 0xF8, 0x0C, 0xA1,
      };
      auto found = reinterpret_cast<UCHAR *>(
          UtilMemMem(p_MmGetVirtualForPhysical, 0x20, kPatternWin81And10,
                     sizeof(kPatternWin81And10)));
      if (found) {
        found += sizeof(kPatternWin81And10);
        const auto address = *reinterpret_cast<ULONG_PTR *>(found);
        g_mmonp_MmPfnDatabase = *reinterpret_cast<void **>(address);
      }
    }
  }
  return (g_mmonp_MmPfnDatabase) ? STATUS_SUCCESS : STATUS_PROCEDURE_NOT_FOUND;
}