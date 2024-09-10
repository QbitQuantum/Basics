/**********************************************************************
 *           K32WOWCallback16Ex         (KERNEL32.55)
 */
BOOL WINAPI K32WOWCallback16Ex( DWORD vpfn16, DWORD dwFlags,
                                DWORD cbArgs, LPVOID pArgs, LPDWORD pdwRetCode )
{
    /*
     * Arguments must be prepared in the correct order by the caller
     * (both for PASCAL and CDECL calling convention), so we simply
     * copy them to the 16-bit stack ...
     */
    char *stack = (char *)CURRENT_STACK16 - cbArgs;

    memcpy( stack, pArgs, cbArgs );

    if (dwFlags & (WCB16_REGS|WCB16_REGS_LONG))
    {
        CONTEXT *context = (CONTEXT *)pdwRetCode;

        if (TRACE_ON(relay))
        {
            DWORD count = cbArgs / sizeof(WORD);
            WORD * wstack = (WORD *)stack;

            DPRINTF("%04x:CallTo16(func=%04x:%04x,ds=%04x",
                    GetCurrentThreadId(),
                    context->SegCs, LOWORD(context->Eip), context->SegDs );
            while (count) DPRINTF( ",%04x", wstack[--count] );
            DPRINTF(") ss:sp=%04x:%04x",
                    SELECTOROF(NtCurrentTeb()->WOW32Reserved), OFFSETOF(NtCurrentTeb()->WOW32Reserved) );
            DPRINTF(" ax=%04x bx=%04x cx=%04x dx=%04x si=%04x di=%04x bp=%04x es=%04x fs=%04x\n",
                    (WORD)context->Eax, (WORD)context->Ebx, (WORD)context->Ecx,
                    (WORD)context->Edx, (WORD)context->Esi, (WORD)context->Edi,
                    (WORD)context->Ebp, (WORD)context->SegEs, (WORD)context->SegFs );
            SYSLEVEL_CheckNotLevel( 2 );
        }

        if (context->EFlags & 0x00020000)  /* v86 mode */
        {
            EXCEPTION_REGISTRATION_RECORD frame;
            frame.Handler = vm86_handler;
            errno = 0;
            __wine_push_frame( &frame );
            __wine_enter_vm86( context );
            __wine_pop_frame( &frame );
            if (errno != 0)  /* enter_vm86 will fall with ENOSYS on x64 kernels */
            {
                WARN("__wine_enter_vm86 failed (errno=%d)\n", errno);
                if (errno == ENOSYS)
                    SetLastError(ERROR_NOT_SUPPORTED);
                else
                    SetLastError(ERROR_GEN_FAILURE);
                return FALSE;
            }
        }
        else
        {
            /* push return address */
            if (dwFlags & WCB16_REGS_LONG)
            {
                stack -= sizeof(DWORD);
                *((DWORD *)stack) = HIWORD(call16_ret_addr);
                stack -= sizeof(DWORD);
                *((DWORD *)stack) = LOWORD(call16_ret_addr);
                cbArgs += 2 * sizeof(DWORD);
            }
            else
            {
                stack -= sizeof(SEGPTR);
                *((SEGPTR *)stack) = call16_ret_addr;
                cbArgs += sizeof(SEGPTR);
            }

            /*
             * Start call by checking for pending events.
             * Note that wine_call_to_16_regs overwrites context stack
             * pointer so we may modify it here without a problem.
             */
            if (get_vm86_teb_info()->dpmi_vif)
            {
                context->SegSs = wine_get_ds();
                context->Esp   = (DWORD)stack;
                insert_event_check( context );
                cbArgs += (DWORD)stack - context->Esp;
            }

            _EnterWin16Lock();
            wine_call_to_16_regs( context, cbArgs, call16_handler );
            _LeaveWin16Lock();
        }

        if (TRACE_ON(relay))
        {
            DPRINTF("%04x:RetFrom16() ss:sp=%04x:%04x ",
                    GetCurrentThreadId(), SELECTOROF(NtCurrentTeb()->WOW32Reserved),
                    OFFSETOF(NtCurrentTeb()->WOW32Reserved));
            DPRINTF(" ax=%04x bx=%04x cx=%04x dx=%04x bp=%04x sp=%04x\n",
                    (WORD)context->Eax, (WORD)context->Ebx, (WORD)context->Ecx,
                    (WORD)context->Edx, (WORD)context->Ebp, (WORD)context->Esp );
            SYSLEVEL_CheckNotLevel( 2 );
        }
    }
    else
    {
        DWORD ret;

        if (TRACE_ON(relay))
        {
            DWORD count = cbArgs / sizeof(WORD);
            WORD * wstack = (WORD *)stack;

            DPRINTF("%04x:CallTo16(func=%04x:%04x,ds=%04x",
                    GetCurrentThreadId(), HIWORD(vpfn16), LOWORD(vpfn16),
                    SELECTOROF(NtCurrentTeb()->WOW32Reserved) );
            while (count) DPRINTF( ",%04x", wstack[--count] );
            DPRINTF(") ss:sp=%04x:%04x\n",
                    SELECTOROF(NtCurrentTeb()->WOW32Reserved), OFFSETOF(NtCurrentTeb()->WOW32Reserved) );
            SYSLEVEL_CheckNotLevel( 2 );
        }

        /* push return address */
        stack -= sizeof(SEGPTR);
        *((SEGPTR *)stack) = call16_ret_addr;
        cbArgs += sizeof(SEGPTR);

        /*
         * Actually, we should take care whether the called routine cleans up
         * its stack or not.  Fortunately, our wine_call_to_16 core doesn't rely on
         * the callee to do so; after the routine has returned, the 16-bit
         * stack pointer is always reset to the position it had before.
         */
        _EnterWin16Lock();
        ret = wine_call_to_16( (FARPROC16)vpfn16, cbArgs, call16_handler );
        if (pdwRetCode) *pdwRetCode = ret;
        _LeaveWin16Lock();

        if (TRACE_ON(relay))
        {
            DPRINTF("%04x:RetFrom16() ss:sp=%04x:%04x retval=%08x\n",
                    GetCurrentThreadId(), SELECTOROF(NtCurrentTeb()->WOW32Reserved),
                    OFFSETOF(NtCurrentTeb()->WOW32Reserved), ret);
            SYSLEVEL_CheckNotLevel( 2 );
        }
    }

    return TRUE;  /* success */
}