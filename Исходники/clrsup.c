HRESULT STDMETHODCALLTYPE DnCLRDataTarget_GetThreadContext(
    __in ICLRDataTarget *This,
    __in ULONG32 threadID,
    __in ULONG32 contextFlags,
    __in ULONG32 contextSize,
    __out BYTE *context
    )
{
    NTSTATUS status;
    HANDLE threadHandle;
    CONTEXT buffer;

    if (contextSize < sizeof(CONTEXT))
        return E_INVALIDARG;

    memset(&buffer, 0, sizeof(CONTEXT));
    buffer.ContextFlags = contextFlags;

    if (NT_SUCCESS(status = PhOpenThread(&threadHandle, THREAD_GET_CONTEXT, ULongToHandle(threadID))))
    {
        status = PhGetThreadContext(threadHandle, &buffer);
        NtClose(threadHandle);
    }

    if (NT_SUCCESS(status))
    {
        memcpy(context, &buffer, sizeof(CONTEXT));

        return S_OK;
    }
    else
    {
        return HRESULT_FROM_WIN32(RtlNtStatusToDosError(status));
    }
}