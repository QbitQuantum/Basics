// If an exception happen as doing a local unwind, this function is the nested exception handler.
// The call convention is __cdecl, but in fact it could be __stdcall too.
// The EstablishFrame would be
//                   ebp
//                   CookiePointer
//                   PrevEstablishFrame
//                   EnclosingLevel
//                   Cookie
//                   _unwind_handler4
//                   next
EXCEPTION_DISPOSITION __cdecl
_unwind_handler4(PEXCEPTION_RECORD ExceptionRecord,
                 PVOID             EstablishFrame,
                 PCONTEXT          ContextRecord,
                 PVOID             DispatchContext)
{
    if ( (ExceptionRecord->ExceptionFlags & (EXCEPTION_UNWINDING | EXCEPTION_EXIT_UNWIND)) == 0) {
        return ExceptionContinueSearch;
    }

    // first check is the establishframe cookie is overwritten.
    DWORD cookie = *(DWORD*)((DWORD)EstablishFrame + 8);
    cookie ^= (DWORD)EstablishFrame;
    __security_check_cookie(cookie);

    __asm {
        mov  eax, EstablishFrame
        push ebp
        mov  ebp, eax
        push [eax+0x0c]      // EstablishFrame.EnclosingLevel
        push [eax+0x10]     // EstablishFrame.PrevEstablishFrame
        push [eax+0x14]     // EstablishFrame.CookiePointer
        call __local_unwind4
        add  esp, 0x0c
        pop  ebp
    }

    *(DWORD*)DispatchContext = (DWORD)EstablishFrame;
    return ExceptionCollidedUnwind;
}