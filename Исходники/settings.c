static BOOL
OpenUserRegistryPathPerProcessId(DWORD ProcessId,
                                 PHKEY hResult,
                                 REGSAM samDesired)
{
    BOOL bRet = TRUE;
    HANDLE hProcessToken = NULL;
    HANDLE hProcess;
    BYTE Buffer[256];
    DWORD Length = 0;
    UNICODE_STRING SidName;
    PTOKEN_USER TokUser;

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | READ_CONTROL, FALSE, ProcessId);
    if (!hProcess)
    {
        DPRINT1("Error: OpenProcess failed(0x%x)\n", GetLastError());
        return FALSE;
    }

    if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hProcessToken))
    {
        DPRINT1("Error: OpenProcessToken failed(0x%x)\n", GetLastError());
        CloseHandle(hProcess);
        return FALSE;
    }

    if (!GetTokenInformation(hProcessToken, TokenUser, (PVOID)Buffer, sizeof(Buffer), &Length))
    {
        DPRINT1("Error: GetTokenInformation failed(0x%x)\n",GetLastError());
        CloseHandle(hProcessToken);
        CloseHandle(hProcess);
        return FALSE;
    }

    TokUser = ((PTOKEN_USER)Buffer)->User.Sid;
    if (!NT_SUCCESS(RtlConvertSidToUnicodeString(&SidName, TokUser, TRUE)))
    {
        DPRINT1("Error: RtlConvertSidToUnicodeString failed(0x%x)\n", GetLastError());
        CloseHandle(hProcessToken);
        CloseHandle(hProcess);
        return FALSE;
    }

    /*
     * Might fail for LiveCD... Why ? Because only HKU\.DEFAULT exists.
     */
    bRet = (RegOpenKeyExW(HKEY_USERS,
                          SidName.Buffer,
                          0,
                          samDesired,
                          hResult) == ERROR_SUCCESS);

    RtlFreeUnicodeString(&SidName);

    CloseHandle(hProcessToken);
    CloseHandle(hProcess);

    return bRet;
}