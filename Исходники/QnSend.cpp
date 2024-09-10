/// \brief Starts a new process with low integrity level
///
/// The newly started process is sandboxed and cannot increase its integrity level
///
int StartRestricted()
{
    BOOL ret;
    HANDLE token = nullptr;
    HANDLE newToken = nullptr;
    PSID integritySid = nullptr;
    TOKEN_MANDATORY_LABEL til = { 0 };
    PROCESS_INFORMATION procInfo = { 0 };
    STARTUPINFO startupInfo = { 0 };
    WCHAR procCommand[MAX_PATH] = _T("QnSend.exe /restricted");
    WCHAR lowIntegrityLevelSid[20] = _T("S-1-16-4096");

    try
    {
        ret = OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_ADJUST_DEFAULT | TOKEN_QUERY | TOKEN_ASSIGN_PRIMARY, &token);
        if (!ret)
            throw ret;
        ret = DuplicateTokenEx(token, 0, nullptr, SecurityImpersonation, TokenPrimary, &newToken);
        if (!ret)
            throw ret;
        ret = ConvertStringSidToSid(lowIntegrityLevelSid, &integritySid);
        if (!ret)
            throw ret;
        til.Label.Attributes = SE_GROUP_INTEGRITY;
        til.Label.Sid = integritySid;
        ret = SetTokenInformation(newToken, TokenIntegrityLevel, &til, sizeof(TOKEN_MANDATORY_LABEL) + GetLengthSid(integritySid));
        if (!ret)
            throw ret;
        ret = CreateProcessAsUser(newToken, NULL, procCommand, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &procInfo);
        if (!ret)
            throw ret;
    }
    catch (...)
    {
#pragma region Cleanup
        if (procInfo.hProcess != nullptr)
            CloseHandle(procInfo.hProcess);
        if (procInfo.hThread != nullptr)
            CloseHandle(procInfo.hThread);
        LocalFree(integritySid);
        if (newToken != nullptr)
            CloseHandle(newToken);
        if (token != nullptr)
            CloseHandle(token);
#pragma endregion
        return ERROR_C;
    }
#pragma region Cleanup
    if (procInfo.hProcess != nullptr)
        CloseHandle(procInfo.hProcess);
    if (procInfo.hThread != nullptr)
        CloseHandle(procInfo.hThread);
    LocalFree(integritySid);
    if (newToken != nullptr)
        CloseHandle(newToken);
    if (token != nullptr)
        CloseHandle(token);
#pragma endregion
    return SUCCESS_C;
}