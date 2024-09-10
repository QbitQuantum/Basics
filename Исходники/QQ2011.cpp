HANDLE
NTAPI
QqCreateWaitQQProtectThread(
    PSECURITY_ATTRIBUTES    ThreadAttributes,
    ULONG_PTR               StackSize,
    PTHREAD_START_ROUTINE   StartAddress,
    PVOID                   Parameter,
    ULONG                   CreationFlags,
    PULONG                  ThreadId
)
{
    NTSTATUS    Status;
    PVOID       Ebp, CallCreateQQProtectExchangeWindow;
    PROCESS_BASIC_INFORMATION BasicInfo;

    LOOP_ONCE
    {
        if (PtrAnd(Parameter, 0xFFF00000) != 0)
            continue;

        Status = NtQueryInformationProcess((HANDLE)Parameter, ProcessBasicInformation, &BasicInfo, sizeof(BasicInfo), nullptr);
        FAIL_BREAK(Status);

        if (BasicInfo.UniqueProcessId != CurrentPid())
            break;

        AllocStack(16);
        Ebp = *((PVOID *)_AddressOfReturnAddress() - 1);

        CallCreateQQProtectExchangeWindow = *((PVOID *)Ebp + 1);
        if (*(PBYTE)CallCreateQQProtectExchangeWindow != CALL)
            break;

        NtClose((HANDLE)Parameter);

        *(PULONG_PTR)((PVOID *)Ebp + 1) += GetOpCodeSize(CallCreateQQProtectExchangeWindow);

        return nullptr;
    }

    return HummerCreateThread(ThreadAttributes, StackSize, StartAddress, Parameter, CreationFlags, ThreadId);
}