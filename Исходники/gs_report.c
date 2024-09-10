    __declspec(noreturn) void __cdecl __report_gsfailure(GSFAILURE_PARAMETER)
    {
        if (IsProcessorFeaturePresent(PF_FASTFAIL_AVAILABLE))
        {
            __fastfail(FAST_FAIL_STACK_COOKIE_CHECK_FAILURE);
        }

        volatile UINT_PTR cookie[2];

        // Set up a fake exception, and report it via UnhandledExceptionFilter.
        // We can't raise a true exception because the stack (and therefore
        // exception handling) can't be trusted after a buffer overrun.  The
        // exception should appear as if it originated after the call to
        // __security_check_cookie, so it is attributed to the function where the
        // buffer overrun was detected.

        #if defined _M_IX86
        // On x86, we reserve some extra stack which won't be used.  That is to
        // preserve as much of the call frame as possible when the function with
        // the buffer overrun entered __security_check_cookie with a JMP instead of
        // a CALL, after the calling frame has been released in the epilogue of
        // that function.
        ULONG volatile dw[(sizeof(CONTEXT) + sizeof(EXCEPTION_RECORD)) / sizeof(ULONG)];

        // Save the state in the context record immediately.  Hopefully, since
        // opts are disabled, this will happen without modifying ECX, which has
        // the local cookie which failed the check.
        __asm
        {
            mov dword ptr [GS_ContextRecord.Eax  ], eax
            mov dword ptr [GS_ContextRecord.Ecx  ], ecx
            mov dword ptr [GS_ContextRecord.Edx  ], edx
            mov dword ptr [GS_ContextRecord.Ebx  ], ebx
            mov dword ptr [GS_ContextRecord.Esi  ], esi
            mov dword ptr [GS_ContextRecord.Edi  ], edi
            mov word ptr  [GS_ContextRecord.SegSs], ss
            mov word ptr  [GS_ContextRecord.SegCs], cs
            mov word ptr  [GS_ContextRecord.SegDs], ds
            mov word ptr  [GS_ContextRecord.SegEs], es
            mov word ptr  [GS_ContextRecord.SegFs], fs
            mov word ptr  [GS_ContextRecord.SegGs], gs
            pushfd
            pop [GS_ContextRecord.EFlags]

            // Set the context EBP/EIP/ESP to the values which would be found
            // in the caller to __security_check_cookie.
            mov eax, [ebp]
            mov dword ptr [GS_ContextRecord.Ebp], eax
            mov eax, [ebp+4]
            mov dword ptr [GS_ContextRecord.Eip], eax
            lea eax, [ebp+8]
            mov dword ptr [GS_ContextRecord.Esp], eax

            // Make sure the dummy stack space looks referenced.
            mov eax, dword ptr dw
        }

        GS_ContextRecord.ContextFlags       = CONTEXT_CONTROL;
        GS_ExceptionRecord.ExceptionAddress = (PVOID)(ULONG_PTR)GS_ContextRecord.Eip;

        #else // ^^^ _M_IX86 ^^^ // vvv _M_X64 vvv //

        capture_previous_context(&GS_ContextRecord);
        GS_ContextRecord.Rip                = (ULONGLONG)_ReturnAddress();
        GS_ContextRecord.Rsp                = (ULONGLONG)_AddressOfReturnAddress()+8;
        GS_ExceptionRecord.ExceptionAddress = (PVOID)GS_ContextRecord.Rip;
        GS_ContextRecord.Rcx                = stack_cookie;

        #endif // _M_X64

        GS_ExceptionRecord.ExceptionCode           = STATUS_SECURITY_CHECK_FAILURE;
        GS_ExceptionRecord.ExceptionFlags          = EXCEPTION_NONCONTINUABLE;
        GS_ExceptionRecord.NumberParameters        = 1;
        GS_ExceptionRecord.ExceptionInformation[0] = FAST_FAIL_STACK_COOKIE_CHECK_FAILURE;

        // Save the global cookie and cookie complement locally - using an array
        // to defeat any potential stack-packing.
        cookie[0] = __security_cookie;
        cookie[1] = __security_cookie_complement;

        // Raise the security failure by passing it to the unhandled exception
        // filter and then terminate the process.
        __raise_securityfailure((EXCEPTION_POINTERS*)&GS_ExceptionPointers);
    }