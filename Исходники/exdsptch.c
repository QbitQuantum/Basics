BOOLEAN
RtlIsValidHandler (
    IN PEXCEPTION_ROUTINE Handler
    )
{
    PULONG FunctionTable;
    ULONG FunctionTableLength;
    PVOID Base;

    FunctionTable = RtlLookupFunctionTable(Handler, &Base, &FunctionTableLength);

    if (FunctionTable && FunctionTableLength) {
        PEXCEPTION_ROUTINE FunctionEntry;
        LONG High, Middle, Low;

        if ((FunctionTable == LongToPtr(-1)) && (FunctionTableLength == (ULONG)-1)) {
            // Address is in an image that shouldn't have any handlers (like a resource only dll).
            RtlInvalidHandlerDetected((PVOID)((ULONG)Handler+(ULONG)Base), LongToPtr(-1), -1);
            return FALSE;
        }
    
        // Bias the handler value down by the image base and see if the result
        // is in the table

        (ULONG)Handler -= (ULONG)Base;
        Low = 0;
        High = FunctionTableLength;
        while (High >= Low) {
            Middle = (Low + High) >> 1;
            FunctionEntry = (PEXCEPTION_ROUTINE)FunctionTable[Middle];
            if (Handler < FunctionEntry) {
                High = Middle - 1;
            } else if (Handler > FunctionEntry) {
                Low = Middle + 1;
            } else {
                // found it
                return TRUE;
            }
        }
        // Didn't find it
        RtlInvalidHandlerDetected((PVOID)((ULONG)Handler+(ULONG)Base), FunctionTable, FunctionTableLength);

        return FALSE;
    }