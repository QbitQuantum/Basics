//
// Assert an NT privilege for this thread.
//
BOOL
AssertPrivilege(
    IN  LPCSTR PrivilegeName
    )

{
    BOOL                b;
    HANDLE              hThread;
    HANDLE              hProcess;
    TOKEN_PRIVILEGES    tokenPrivileges, oldTokenPrivileges;
    DWORD               oldPrivilegesLength;


    b = OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES |
                        TOKEN_QUERY, TRUE, &hThread);
    if (!b) {
        if (GetLastError() != ERROR_NO_TOKEN) {
            return b;
        }

        b = OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE, &hProcess);
        if (!b) {
            return b;
        }

        b = DuplicateTokenEx(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY |
                             TOKEN_IMPERSONATE, NULL, SecurityImpersonation,
                             TokenImpersonation, &hThread);
        if (!b) {
            CloseHandle(hProcess);
            return b;
        }

        b = SetThreadToken(NULL, hThread);
        if (!b) {
            CloseHandle(hProcess);
            CloseHandle(hThread);
            return b;
        }

        CloseHandle(hProcess);
    }

    ZeroMemory(&tokenPrivileges, sizeof(tokenPrivileges));

    b = LookupPrivilegeValue(NULL,PrivilegeName,&tokenPrivileges.Privileges[0].Luid);
    if (!b) {
        return b;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    b = AdjustTokenPrivileges(hThread, FALSE, &tokenPrivileges,
                              sizeof(tokenPrivileges), &oldTokenPrivileges,
                              &oldPrivilegesLength);

    CloseHandle(hThread);

    return b;
}