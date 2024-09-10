static uint64_t generateLuid() {
  LUID luid;
  if (AllocateLocallyUniqueId(&luid)) {
    uint64_t id = luid.HighPart;
    return id << 32 | luid.LowPart;
  }
  throw std::system_error(
      GetLastError(), Win32ErrorCategory::get(), "Failed to generate the luid");
}