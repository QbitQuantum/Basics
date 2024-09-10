/*
 * Returns 1 if the operating system is a 64-bit version of
 * Windows.
 */
int NaClOsIs64BitWindows() {
  SYSTEM_INFO system_info;

  GetNativeSystemInfo(&system_info);
  if (PROCESSOR_ARCHITECTURE_AMD64 == system_info.wProcessorArchitecture) {
    /*
     * The installed operating system processor architecture is x86-64.
     * This assumes the caller already knows it's a supported architecture.
     */
    return 1;
  }
  return 0;
}