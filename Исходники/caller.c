EASYHOOK_NT_EXPORT LhBarrierCallStackTrace(
            PVOID* OutMethodArray, 
            ULONG InMaxMethodCount,
            ULONG* OutMethodCount)
{
/*
Description:

    Creates a call stack trace and translates all method entries
    back into their owning modules.

Parameters:

    - OutMethodArray

        An array receiving the methods on the call stack.

    - InMaxMethodCount

        The length of the method array. 

    - OutMethodCount

        The actual count of methods on the call stack. This will never
        be greater than 64.

Returns:

    STATUS_NOT_IMPLEMENTED

        Only supported since Windows XP.
*/
    NTSTATUS				NtStatus;
    PVOID					Backup = NULL;

	if(InMaxMethodCount > 64)
		THROW(STATUS_INVALID_PARAMETER_2, L"At maximum 64 modules are supported.");

	if(!IsValidPointer(OutMethodArray, InMaxMethodCount * sizeof(PVOID)))
		THROW(STATUS_INVALID_PARAMETER_1, L"The given module buffer is invalid.");

	if(!IsValidPointer(OutMethodCount, sizeof(ULONG)))
		THROW(STATUS_INVALID_PARAMETER_3, L"Invalid module count storage.");

    FORCE(LhBarrierBeginStackTrace(&Backup));

#ifndef DRIVER
    if(RtlCaptureStackBackTrace == NULL)
        RtlCaptureStackBackTrace = (PROC_RtlCaptureStackBackTrace*)GetProcAddress(hKernel32, "RtlCaptureStackBackTrace");

    if(RtlCaptureStackBackTrace == NULL)
        THROW(STATUS_NOT_IMPLEMENTED, L"This method requires Windows XP or later.");
#endif

    *OutMethodCount = RtlCaptureStackBackTrace(1, 32, OutMethodArray, NULL);

    RETURN;

THROW_OUTRO:
FINALLY_OUTRO:
     {
        if(Backup != NULL)
            LhBarrierEndStackTrace(Backup);

        return NtStatus;
    }
}