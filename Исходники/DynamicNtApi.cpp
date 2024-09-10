static VOID InitializeInternals()
{
  //because we are using NKTHOOKLIB_CurrentProcess and ScanMappedImages to FALSE, we are avoiding the recursion
  LPVOID _hNtDll = ::NktHookLib::GetRemoteModuleBaseAddress(NKTHOOKLIB_CurrentProcess, L"ntdll.dll", FALSE);
  if (_hNtDll != NULL)
  {
    #define NKT_PARSE_NTAPI_NTSTATUS(name, _notused, _notused2)                                                   \
      lpfn_##name __fn_##name = (lpfn_##name)::NktHookLib::GetRemoteProcedureAddress(NKTHOOKLIB_CurrentProcess,    \
                                                                                    _hNtDll, # name);
    #define NKT_PARSE_NTAPI_VOID NKT_PARSE_NTAPI_NTSTATUS
    #define NKT_PARSE_NTAPI_PVOID NKT_PARSE_NTAPI_NTSTATUS
    #define NKT_PARSE_NTAPI_BOOLEAN NKT_PARSE_NTAPI_NTSTATUS
    #define NKT_PARSE_NTAPI_ULONG NKT_PARSE_NTAPI_NTSTATUS
    #include "NtApiDeclarations.h"
    #undef NKT_PARSE_NTAPI_NTSTATUS
    #undef NKT_PARSE_NTAPI_VOID
    #undef NKT_PARSE_NTAPI_PVOID
    #undef NKT_PARSE_NTAPI_BOOLEAN
    #undef NKT_PARSE_NTAPI_ULONG

#if defined(_M_IX86)
    #define NKT_PARSE_NTAPI_NTSTATUS(name, _notused, _notused2)  \
      _InterlockedExchange((long volatile*)&(NktHookLib_fn_##name), (long)(__fn_##name));
#elif defined(_M_X64)
    #define NKT_PARSE_NTAPI_NTSTATUS(name, _notused, _notused2)  \
      _InterlockedExchangePointer((void* volatile*)&(NktHookLib_fn_##name), (__fn_##name));
#endif
    #define NKT_PARSE_NTAPI_VOID NKT_PARSE_NTAPI_NTSTATUS
    #define NKT_PARSE_NTAPI_PVOID NKT_PARSE_NTAPI_NTSTATUS
    #define NKT_PARSE_NTAPI_BOOLEAN NKT_PARSE_NTAPI_NTSTATUS
    #define NKT_PARSE_NTAPI_ULONG NKT_PARSE_NTAPI_NTSTATUS
    #include "NtApiDeclarations.h"
    #undef NKT_PARSE_NTAPI_NTSTATUS
    #undef NKT_PARSE_NTAPI_VOID
    #undef NKT_PARSE_NTAPI_PVOID
    #undef NKT_PARSE_NTAPI_BOOLEAN
    #undef NKT_PARSE_NTAPI_ULONG
    //----
    NktHookLib_fn_vsnprintf = ::NktHookLib::GetRemoteProcedureAddress(NKTHOOKLIB_CurrentProcess, _hNtDll,
                                                                      "_vsnprintf");
    NktHookLib_fn_vsnwprintf = ::NktHookLib::GetRemoteProcedureAddress(NKTHOOKLIB_CurrentProcess, _hNtDll,
                                                                       "_vsnwprintf");
    NktHookLib_fn_DbgPrint  = ::NktHookLib::GetRemoteProcedureAddress(NKTHOOKLIB_CurrentProcess, _hNtDll,
                                                                      "DbgPrint");
  }
#if defined(_M_IX86)
  _InterlockedExchange((long volatile*)&hNtDll, (long)_hNtDll);
#elif defined(_M_X64)
  _InterlockedExchangePointer((volatile PVOID*)&hNtDll, _hNtDll);
#endif
  return;
}