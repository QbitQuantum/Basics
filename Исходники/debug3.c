NTSTATUS
DebugService(
    ULONG   ServiceClass,
    PVOID   Arg1,
    PVOID   Arg2
    )

//++
//
//  Routine Description:
//
//      Allocate an ExceptionRecord, fill in data to allow exception
//      dispatch code to do the right thing with the service, and
//      call RtlRaiseException (NOT ExRaiseException!!!).
//
//  Arguments:
//      ServiceClass - which call is to be performed
//      Arg1 - generic first argument
//      Arg2 - generic second argument
//
//  Returns:
//      Whatever the exception returns in eax
//
//--

{
    NTSTATUS    RetValue;

#if defined(BUILD_WOW6432)

    extern NTSTATUS NtWow64DebuggerCall(ULONG, PVOID, PVOID);
    RetValue = NtWow64DebuggerCall(ServiceClass, Arg1, Arg2);

#else
    _asm {
        mov     eax, ServiceClass
        mov     ecx, Arg1
        mov     edx, Arg2

        int     2dh                 ; Raise exception
        int     3                   ; DO NOT REMOVE (See KiDebugService)

        mov     RetValue, eax

    }
#endif

    return RetValue;
}