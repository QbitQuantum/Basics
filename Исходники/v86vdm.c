VOID
FASTCALL
KiEnterV86Mode(IN ULONG_PTR StackFrameUnaligned)
{
    PKTHREAD Thread;
    PKV8086_STACK_FRAME StackFrame = (PKV8086_STACK_FRAME)(ROUND_UP(StackFrameUnaligned - 4, 16) + 4);
    PKTRAP_FRAME TrapFrame = &StackFrame->TrapFrame;
    PKV86_FRAME V86Frame = &StackFrame->V86Frame;
    PFX_SAVE_AREA NpxFrame = &StackFrame->NpxArea;

    ASSERT((ULONG_PTR)NpxFrame % 16 == 0);

    /* Build fake user-mode trap frame */
    TrapFrame->SegCs = KGDT_R0_CODE | RPL_MASK;
    TrapFrame->SegEs = TrapFrame->SegDs = TrapFrame->SegFs = TrapFrame->SegGs = 0;
    TrapFrame->ErrCode = 0;

    /* Get the current thread's initial stack */
    Thread = KeGetCurrentThread();
    V86Frame->ThreadStack = KiGetThreadNpxArea(Thread);

    /* Save TEB addresses */
    V86Frame->ThreadTeb = Thread->Teb;
    V86Frame->PcrTeb = KeGetPcr()->NtTib.Self;

    /* Save return EIP */
    TrapFrame->Eip = (ULONG_PTR)Ki386BiosCallReturnAddress;

    /* Save our stack (after the frames) */
    TrapFrame->Esi = StackFrameUnaligned;
    TrapFrame->Edi = (ULONG_PTR)_AddressOfReturnAddress() + 4;

    /* Sanitize EFlags and enable interrupts */
    TrapFrame->EFlags = __readeflags() & 0x60DD7;
    TrapFrame->EFlags |= EFLAGS_INTERRUPT_MASK;

    /* Fill out the rest of the frame */
    TrapFrame->HardwareSegSs = KGDT_R3_DATA | RPL_MASK;
    TrapFrame->HardwareEsp = 0x11FFE;
    TrapFrame->ExceptionList = EXCEPTION_CHAIN_END;
    TrapFrame->Dr7 = 0;

    /* Set some debug fields if trap debugging is enabled */
    KiFillTrapFrameDebug(TrapFrame);

    /* Disable interrupts */
    _disable();

    /* Copy the thread's NPX frame */
    RtlCopyMemory(NpxFrame, V86Frame->ThreadStack, sizeof(FX_SAVE_AREA));

    /* Clear exception list */
    KeGetPcr()->NtTib.ExceptionList = EXCEPTION_CHAIN_END;

    /* Set new ESP0 */
    KeGetPcr()->TSS->Esp0 = (ULONG_PTR)&TrapFrame->V86Es;

    /* Set new initial stack */
    Thread->InitialStack = V86Frame;

    /* Set VDM TEB */
    Thread->Teb = (PTEB)TRAMPOLINE_TEB;
    KiSetTebBase(KeGetPcr(), (PVOID)TRAMPOLINE_TEB);

    /* Enable interrupts */
    _enable();

    /* Start VDM execution */
    NtVdmControl(VdmStartExecution, NULL);

    /* Exit to V86 mode */
    KiEoiHelper(TrapFrame);
}