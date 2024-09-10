/**
 * Unlike pthreads, the Windows API does not seem to provide a convenient way to
 * hook a callback onto thread shutdown.  However, the Windows portable
 * executable format does define a concept of thread-local storage callbacks.
 * Here, we define a function and instruct the linker to set a pointer to that
 * function in the segment for thread-local storage callbacks.  See page 85 of
 * Microsoft Portable Executable and Common Object File Format Specification:
 * http://msdn.microsoft.com/en-us/gg463119.aspx
 * This technique only works for implicit linking (OS loads DLL on demand), not
 * for explicit linking (user code calls LoadLibrary directly).  This effectively
 * means that we have a known limitation: libhdfs may not work correctly if a
 * Windows application attempts to use it via explicit linking.
 *
 * @param h module handle
 * @param reason the reason for calling the callback
 * @param pv reserved, unused
 */
static void NTAPI tlsCallback(PVOID h, DWORD reason, PVOID pv)
{
  DWORD tlsIndex;
  switch (reason) {
  case DLL_THREAD_DETACH:
    detachCurrentThreadFromJvm();
    break;
  case DLL_PROCESS_DETACH:
    detachCurrentThreadFromJvm();
    tlsIndex = gTlsIndex;
    gTlsIndex = TLS_OUT_OF_INDEXES;
    if (!TlsFree(tlsIndex)) {
      fprintf(stderr, "tlsCallback: TlsFree failed with error %d\n",
        GetLastError());
    }
    break;
  default:
    break;
  }
}