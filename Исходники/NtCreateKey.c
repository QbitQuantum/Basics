static
VOID
VerifyAccess_(
    _In_ HANDLE Handle,
    _In_ ACCESS_MASK ExpectedAccess,
    _In_ PCSTR File,
    _In_ INT Line)
{
    NTSTATUS Status;
    OBJECT_BASIC_INFORMATION BasicInfo;
    ULONG Length;

    Status = NtQueryObject(Handle,
                           ObjectBasicInformation,
                           &BasicInfo,
                           sizeof(BasicInfo),
                           &Length);
    ok_(File, Line)(Status == STATUS_SUCCESS, "NtQueryObject returned 0x%lx\n", Status);
    ok_(File, Line)(BasicInfo.GrantedAccess == ExpectedAccess,
                    "GrantedAccess is 0x%lx, expected 0x%lx\n",
                    BasicInfo.GrantedAccess, ExpectedAccess);
}