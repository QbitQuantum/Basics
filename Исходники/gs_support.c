__declspec(noreturn) void __cdecl
__report_gsfailure (ULONG_PTR StackCookie)
{
  volatile UINT_PTR cookie[2] __MINGW_ATTRIB_UNUSED;
#if defined(_WIN64) && !defined(__aarch64__)
  ULONG64 controlPC, imgBase, establisherFrame;
  PRUNTIME_FUNCTION fctEntry;
  PVOID hndData;

  RtlCaptureContext (&GS_ContextRecord);
  controlPC = GS_ContextRecord.Rip;
  fctEntry = RtlLookupFunctionEntry (controlPC, &imgBase, NULL);
  if (fctEntry != NULL)
    {
      RtlVirtualUnwind (UNW_FLAG_NHANDLER, imgBase, controlPC, fctEntry,
			&GS_ContextRecord, &hndData, &establisherFrame, NULL);
    }
  else
#endif /* _WIN64 */
    {
#if defined(__x86_64__) || defined(_AMD64_)
      GS_ContextRecord.Rip = (ULONGLONG) _ReturnAddress();
      GS_ContextRecord.Rsp = (ULONGLONG) _AddressOfReturnAddress() + 8;
#elif defined(__i386__) || defined(_X86_)
      GS_ContextRecord.Eip = (DWORD) _ReturnAddress();
      GS_ContextRecord.Esp = (DWORD) _AddressOfReturnAddress() + 4;
#elif defined(__arm__) || defined(_ARM_)
      GS_ContextRecord.Pc = (DWORD) _ReturnAddress();
      GS_ContextRecord.Sp = (DWORD) _AddressOfReturnAddress() + 4;
#endif /* _WIN64 */
    }

#if defined(__x86_64__) || defined(_AMD64_)
  GS_ExceptionRecord.ExceptionAddress = (PVOID) GS_ContextRecord.Rip;
  GS_ContextRecord.Rcx = StackCookie;
#elif defined(__i386__) || defined(_X86_)
  GS_ExceptionRecord.ExceptionAddress = (PVOID) GS_ContextRecord.Eip;
  GS_ContextRecord.Ecx = StackCookie;
#elif defined(__arm__) || defined(_ARM_)
  GS_ExceptionRecord.ExceptionAddress = (PVOID) GS_ContextRecord.Pc;
  UNUSED_PARAM(StackCookie);
#endif /* _WIN64 */
  GS_ExceptionRecord.ExceptionCode = STATUS_STACK_BUFFER_OVERRUN;
  GS_ExceptionRecord.ExceptionFlags = EXCEPTION_NONCONTINUABLE;
  cookie[0] = __security_cookie;
  cookie[1] = __security_cookie_complement;
  SetUnhandledExceptionFilter (NULL);
  UnhandledExceptionFilter ((EXCEPTION_POINTERS *) &GS_ExceptionPointers);
  TerminateProcess (GetCurrentProcess (), STATUS_STACK_BUFFER_OVERRUN);
  abort();
}