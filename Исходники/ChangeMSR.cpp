// Modify or restore MSR
_Use_decl_annotations_ EXTERN_C static NTSTATUS MsrHookCallback(void* Context) {
  UNREFERENCED_PARAMETER(Context);

  auto oldmsr = &g_MSRs[KeGetCurrentProcessorNumber()];
  if (*oldmsr == 0) {
    // Modify
    *oldmsr = __readmsr(IA32_LSTAR);
    __writemsr(IA32_LSTAR, reinterpret_cast<ULONG_PTR>(g_Trampoline));
    LOG_INFO("MSR(%08x) %p => %p", IA32_LSTAR, *oldmsr, g_Trampoline);
  } else {
    // Restore
    __writemsr(IA32_LSTAR, *oldmsr);
    LOG_INFO("MSR(%08x) %p => %p", IA32_LSTAR, g_Trampoline, *oldmsr);
  }
  return STATUS_SUCCESS;
}