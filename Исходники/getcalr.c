VOID
RtlGetCallersAddress (
    OUT PVOID *CallersPc,
    OUT PVOID *CallersCallersPc
    )

/*++

Routine Description:

    This routine returns the address of the routine that called the routine
    that called this routine, and the routine that called the routine that
    called this routine. For example, if A called B called C which called
    this routine, the return addresses in A and B would be returned.

Arguments:

    CallersPc - Supplies a pointer to a variable that receives the address
        of the caller of the caller of this routine (B).

    CallersCallersPc - Supplies a pointer to a variable that receives the
        address of the caller of the caller of the caller of this routine
        (A).

Return Value:

    None.

Note:

    If either of the calling stack frames exceeds the limits of the stack,
    they are set to NULL.

--*/

{

    CONTEXT ContextRecord;
    ULONG EstablisherFrame;
    PRUNTIME_FUNCTION FunctionEntry;
    BOOLEAN InFunction;
    ULONG NextPc;
    ULONG HighLimit, LowLimit;

    //
    // Assume the function table entries for the various routines cannot be
    // found or there are not four procedure activation records on the stack.
    //

    *CallersPc = NULL;
    *CallersCallersPc = NULL;

    //
    // Capture the current context.
    //

    RtlCaptureContext(&ContextRecord);
    NextPc = (ULONG)ContextRecord.XIntRa;

    //
    // Get the high and low limits of the current thread's stack.
    //

    RtlpGetStackLimits(&LowLimit, &HighLimit);

    //
    // Attempt to unwind to the caller of this routine (C).
    //

    FunctionEntry = RtlLookupFunctionEntry(NextPc);
    if (FunctionEntry != NULL) {

        //
        // A function entry was found for this routine. Virtually unwind
        // to the caller of this routine (C).
        //

        NextPc = RtlVirtualUnwind(NextPc | 1,
                                  FunctionEntry,
                                  &ContextRecord,
                                  &InFunction,
                                  &EstablisherFrame,
                                  NULL);

        //
        // Attempt to unwind to the caller of the caller of this routine (B).
        //

        FunctionEntry = RtlLookupFunctionEntry(NextPc);
        if ((FunctionEntry != NULL) && ((ULONG)ContextRecord.XIntSp < HighLimit)) {

            //
            // A function table entry was found for the caller of the caller
            // of this routine (B). Virtually unwind to the caller of the
            // caller of this routine (B).
            //

            NextPc = RtlVirtualUnwind(NextPc | 1,
                                      FunctionEntry,
                                      &ContextRecord,
                                      &InFunction,
                                      &EstablisherFrame,
                                      NULL);

            *CallersPc = (PVOID)NextPc;

            //
            // Attempt to unwind to the caller of the caller of the caller
            // of the caller of this routine (A).
            //

            FunctionEntry = RtlLookupFunctionEntry(NextPc);
            if ((FunctionEntry != NULL) && ((ULONG)ContextRecord.XIntSp < HighLimit)) {

                //
                // A function table entry was found for the caller of the
                // caller of the caller of this routine (A). Virtually unwind
                // to the caller of the caller of the caller of this routine
                // (A).
                //

                NextPc = RtlVirtualUnwind(NextPc | 1,
                                          FunctionEntry,
                                          &ContextRecord,
                                          &InFunction,
                                          &EstablisherFrame,
                                          NULL);

                *CallersCallersPc = (PVOID)NextPc;
            }
        }
    }

    return;
}