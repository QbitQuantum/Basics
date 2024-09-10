BOOL
GetUserSidStringFromToken(HANDLE hToken,
                          PUNICODE_STRING SidString)
{
    PTOKEN_USER UserBuffer, nsb;
    ULONG Length;
    NTSTATUS Status;

    Length = 256;
    UserBuffer = LocalAlloc(LPTR, Length);
    if (UserBuffer == NULL)
        return FALSE;

    Status = NtQueryInformationToken(hToken,
                                     TokenUser,
                                     (PVOID)UserBuffer,
                                     Length,
                                     &Length);
    if (Status == STATUS_BUFFER_TOO_SMALL)
    {
        nsb = LocalReAlloc(UserBuffer,
                           Length,
                           LMEM_MOVEABLE);
        if (nsb == NULL)
        {
            LocalFree(UserBuffer);
            return FALSE;
        }

        UserBuffer = nsb;
        Status = NtQueryInformationToken(hToken,
                                         TokenUser,
                                         (PVOID)UserBuffer,
                                         Length,
                                         &Length);
    }

    if (!NT_SUCCESS (Status))
    {
        LocalFree(UserBuffer);
        SetLastError(RtlNtStatusToDosError(Status));
        return FALSE;
    }

    DPRINT("SidLength: %lu\n", RtlLengthSid (UserBuffer->User.Sid));

    Status = RtlConvertSidToUnicodeString(SidString,
                                          UserBuffer->User.Sid,
                                          TRUE);

    LocalFree(UserBuffer);

    if (!NT_SUCCESS(Status))
    {
        SetLastError(RtlNtStatusToDosError(Status));
        return FALSE;
    }

    DPRINT("SidString.Length: %lu\n", SidString->Length);
    DPRINT("SidString.MaximumLength: %lu\n", SidString->MaximumLength);
    DPRINT("SidString: '%wZ'\n", SidString);

    return TRUE;
}