void OsMisc_flush_icache(address start, int size) {
#if defined(_WIN32_WCE)
  /* Currently the PocketPC API doesn't seem to support selective
     flushing of the icache => ignore start, size for now */
  BOOL ret = FlushInstructionCache(GetCurrentProcess(), 0, 0);
#else
  javacall_os_flush_icache((unsigned char*)start, size);
#endif
}