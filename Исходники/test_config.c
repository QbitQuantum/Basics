static void print_current_stack() {
  typedef USHORT(WINAPI * CaptureStackBackTraceType)(
      __in ULONG, __in ULONG, __out PVOID *, __out_opt PULONG);
  CaptureStackBackTraceType func = (CaptureStackBackTraceType)(GetProcAddress(
      LoadLibrary(_T("kernel32.dll")), "RtlCaptureStackBackTrace"));

  if (func == NULL) return;  // WOE 29.SEP.2010

// Quote from Microsoft Documentation:
// ## Windows Server 2003 and Windows XP:
// ## The sum of the FramesToSkip and FramesToCapture parameters must be less
// than 63.
#define MAX_CALLERS 62

  void *callers_stack[MAX_CALLERS];
  unsigned short frames;
  SYMBOL_INFOW *symbol;
  HANDLE process;
  process = GetCurrentProcess();
  SymInitialize(process, NULL, TRUE);
  frames = (func)(0, MAX_CALLERS, callers_stack, NULL);
  symbol =
      (SYMBOL_INFOW *)calloc(sizeof(SYMBOL_INFOW) + 256 * sizeof(wchar_t), 1);
  symbol->MaxNameLen = 255;
  symbol->SizeOfStruct = sizeof(SYMBOL_INFOW);

  const unsigned short MAX_CALLERS_SHOWN = 32;
  frames = frames < MAX_CALLERS_SHOWN ? frames : MAX_CALLERS_SHOWN;
  for (unsigned int i = 0; i < frames; i++) {
    SymFromAddrW(process, (DWORD64)(callers_stack[i]), 0, symbol);
    fwprintf(stderr, L"*** %d: %016I64X %ls - %016I64X\n", i,
             (DWORD64)callers_stack[i], symbol->Name, (DWORD64)symbol->Address);
    fflush(stderr);
  }

  free(symbol);
}