NTSTATUS PhpGetObjectBasicInformation(
    __in HANDLE ProcessHandle,
    __in HANDLE Handle,
    __out POBJECT_BASIC_INFORMATION BasicInformation
    )
{
    NTSTATUS status;

    if (KphIsConnected())
    {
        status = KphQueryInformationObject(
            ProcessHandle,
            Handle,
            KphObjectBasicInformation,
            BasicInformation,
            sizeof(OBJECT_BASIC_INFORMATION),
            NULL
            );

        if (NT_SUCCESS(status))
        {
            // The object was referenced in KProcessHacker, so
            // we need to subtract 1 from the pointer count.
            BasicInformation->PointerCount -= 1;
        }
    }
    else
    {
        status = NtQueryObject(
            Handle,
            ObjectBasicInformation,
            BasicInformation,
            sizeof(OBJECT_BASIC_INFORMATION),
            NULL
            );

        if (NT_SUCCESS(status))
        {
            // The object was referenced in NtQueryObject and
            // a handle was opened to the object. We need to
            // subtract 1 from the pointer count, then subtract
            // 1 from both counts.
            BasicInformation->HandleCount -= 1;
            BasicInformation->PointerCount -= 2;
        }
    }

    return status;
}