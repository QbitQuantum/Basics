_CRTIMP void __cdecl _invoke_watson(
    const wchar_t *pszExpression,
    const wchar_t *pszFunction,
    const wchar_t *pszFile,
    unsigned int nLine,
    uintptr_t pReserved
    )
{
    /* Fake an exception to call reportfault. */
    EXCEPTION_RECORD ExceptionRecord;
    CONTEXT ContextRecord;
    EXCEPTION_POINTERS ExceptionPointers;
    BOOL wasDebuggerPresent = FALSE;
    DWORD ret = 0;

    (pszExpression);
    (pszFunction);
    (pszFile);
    (nLine);
    (pReserved);

#ifdef _X86_

    __asm {
        mov dword ptr [ContextRecord.Eax], eax
        mov dword ptr [ContextRecord.Ecx], ecx
        mov dword ptr [ContextRecord.Edx], edx
        mov dword ptr [ContextRecord.Ebx], ebx
        mov dword ptr [ContextRecord.Esi], esi
        mov dword ptr [ContextRecord.Edi], edi
        mov word ptr [ContextRecord.SegSs], ss
        mov word ptr [ContextRecord.SegCs], cs
        mov word ptr [ContextRecord.SegDs], ds
        mov word ptr [ContextRecord.SegEs], es
        mov word ptr [ContextRecord.SegFs], fs
        mov word ptr [ContextRecord.SegGs], gs
        pushfd
        pop [ContextRecord.EFlags]
    }

    ContextRecord.ContextFlags = CONTEXT_CONTROL;
#pragma warning(push)
#pragma warning(disable:4311)
    ContextRecord.Eip = (ULONG)_ReturnAddress();
    ContextRecord.Esp = (ULONG)_AddressOfReturnAddress();
#pragma warning(pop)
    ContextRecord.Ebp = *((ULONG *)_AddressOfReturnAddress()-1);

#elif defined (_IA64_) || defined (_AMD64_)

    /* Need to fill up the Context in IA64 and AMD64. */
    RtlCaptureContext(&ContextRecord);

#else  /* defined (_IA64_) || defined (_AMD64_) */

    ZeroMemory(&ContextRecord, sizeof(ContextRecord));

#endif  /* defined (_IA64_) || defined (_AMD64_) */

    ZeroMemory(&ExceptionRecord, sizeof(ExceptionRecord));

    ExceptionRecord.ExceptionCode = STATUS_INVALID_PARAMETER;
    ExceptionRecord.ExceptionAddress = _ReturnAddress();

    ExceptionPointers.ExceptionRecord = &ExceptionRecord;
    ExceptionPointers.ContextRecord = &ContextRecord;

    wasDebuggerPresent = IsDebuggerPresent();

    /* Make sure any filter already in place is deleted. */
    SetUnhandledExceptionFilter(NULL);

    ret = UnhandledExceptionFilter(&ExceptionPointers);

    // if no handler found and no debugger previously attached
    // the execution must stop into the debugger hook.
    if (ret == EXCEPTION_CONTINUE_SEARCH && !wasDebuggerPresent) {
        _CRT_DEBUGGER_HOOK(_CRT_DEBUGGER_INVALIDPARAMETER);
    }

    TerminateProcess(GetCurrentProcess(), STATUS_INVALID_PARAMETER);
}