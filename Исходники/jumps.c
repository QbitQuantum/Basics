int
setjmp (
    IN jmp_buf JumpBuffer
    )

/*++

Routine Description:

    This function performs a set jump operation by capturing the current
    context, virtualy unwinding to the caller of set jump, and returns zero
    to the caller.

Arguments:

    JumpBuffer - Supplies the address of a jump buffer to store the virtual
        frame pointer and target address of the caller.

        N.B. This is an array of double to force quadword alignment.

Return Value:

    A value of zero is returned.

--*/

{

    CONTEXT ContextRecord;
    ULONG EstablisherFrame;
    PRUNTIME_FUNCTION FunctionEntry;
    BOOLEAN InFunction;
    PULONG JumpArray;
    ULONG NextPc;

    //
    // Capture the current context, virtually unwind to the caller of set
    // jump, and return zero to the caller.
    //

    JumpArray = (PULONG)&JumpBuffer[0];
    RtlCaptureContext(&ContextRecord);
    NextPc = ContextRecord.Lr - 4;
    FunctionEntry = RtlLookupFunctionEntry(NextPc);
    NextPc = RtlVirtualUnwind(NextPc,
                              FunctionEntry,
                              &ContextRecord,
                              &InFunction,
                              &EstablisherFrame,
                              NULL,
                              0,
                              0xffffffff);

    JumpArray[1] = NextPc + 4;
    FunctionEntry = RtlLookupFunctionEntry(NextPc);
    NextPc = RtlVirtualUnwind(NextPc,
                              FunctionEntry,
                              &ContextRecord,
                              &InFunction,
                              &EstablisherFrame,
                              NULL,
                              0,
                              0xffffffff);

    JumpArray[0] = EstablisherFrame;
    return 0;
}