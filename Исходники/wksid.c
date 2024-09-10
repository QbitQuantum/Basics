PSID FspWksidNew(WELL_KNOWN_SID_TYPE WellKnownSidType, PNTSTATUS PResult)
{
    NTSTATUS Result;
    PSID Sid;
    DWORD Size;

    Size = SECURITY_MAX_SID_SIZE;
    Sid = MemAlloc(Size);
    if (0 == Sid)
    {
        Result = STATUS_INSUFFICIENT_RESOURCES;
        goto exit;
    }

    if (!CreateWellKnownSid(WellKnownSidType, 0, Sid, &Size))
    {
        Result = FspNtStatusFromWin32(GetLastError());
        MemFree(Sid); Sid = 0;
        goto exit;
    }

    Result = STATUS_SUCCESS;

exit:
    if (0 != PResult)
        *PResult = Result;

    return Sid;
}