static int
subsys_winprocess_initialize(void)
{
#ifndef HeapEnableTerminationOnCorruption
#define HeapEnableTerminationOnCorruption 1
#endif

  /* On heap corruption, just give up; don't try to play along. */
  HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

  /* SetProcessDEPPolicy is only supported on 32-bit Windows.
   * (On 64-bit Windows it always fails, and some compilers don't like the
   * PSETDEP cast.)
   * 32-bit Windows defines _WIN32.
   * 64-bit Windows defines _WIN32 and _WIN64. */
#ifndef _WIN64
  /* Call SetProcessDEPPolicy to permanently enable DEP.
     The function will not resolve on earlier versions of Windows,
     and failure is not dangerous. */
  HMODULE hMod = GetModuleHandleA("Kernel32.dll");
  if (hMod) {
    typedef BOOL (WINAPI *PSETDEP)(DWORD);
    PSETDEP setdeppolicy = (PSETDEP)GetProcAddress(hMod,
                           "SetProcessDEPPolicy");
    if (setdeppolicy) {
      /* PROCESS_DEP_ENABLE | PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION */
      setdeppolicy(3);
    }
  }
#endif /* !defined(_WIN64) */

  return 0;
}