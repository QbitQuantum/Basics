bool SecurityHelper::CallLsaLogonUser(
    HANDLE hLsa,
    const wchar_t* domain,
    const wchar_t* user,
    const wchar_t* pass,
    SECURITY_LOGON_TYPE logonType,
    LUID* pLogonSessionId,
    HANDLE* phToken,
    MSV1_0_INTERACTIVE_PROFILE** ppProfile,
    DWORD* pWin32Error)
{

    bool result      = false;
    DWORD win32Error = 0;
    *phToken         = 0;

    LUID ignoredLogonSessionId;

    // optional arguments
    if (ppProfile)        *ppProfile   = 0;
    if (pWin32Error)      *pWin32Error = 0;
    if (!pLogonSessionId) pLogonSessionId = &ignoredLogonSessionId;

    LSA_STRING logonProcessName            = { 0 };
    TOKEN_SOURCE sourceContext             = { 's', 'a', 'm', 'p', 'l', 'e' };
    MSV1_0_INTERACTIVE_PROFILE* pProfile = 0;
    ULONG cbProfile = 0;
    QUOTA_LIMITS quotaLimits;
    NTSTATUS substatus;
    DWORD cbLogonRequest;

    MSV1_0_INTERACTIVE_LOGON* pLogonRequest =
        _allocLogonRequest(domain, user, pass, &cbLogonRequest);
    if (!pLogonRequest)
	{
        win32Error = ERROR_NOT_ENOUGH_MEMORY;
        goto cleanup;   
    }

    if (!_newLsaString(&logonProcessName, LOGON_PROCESS_NAME))
	{
        win32Error = ERROR_NOT_ENOUGH_MEMORY;
        goto cleanup;
    }

    // LsaLogonUser - the function from hell
    NTSTATUS status = LsaLogonUser(
        hLsa,
        &logonProcessName,  // we use our logon process name for the "origin name"
        logonType,
        LOGON32_PROVIDER_DEFAULT, // we use MSV1_0 or Kerb, whichever is supported
        pLogonRequest,
        cbLogonRequest,
        0,                  // we do not add any group SIDs
        &sourceContext,
        (void**)&pProfile,  // caller must free this via LsaFreeReturnBuffer 
        &cbProfile,
        pLogonSessionId,
        phToken,
        &quotaLimits,       // we ignore this, but must pass in anyway
        &substatus);

    if (status)
	{
        win32Error = LsaNtStatusToWinError(status);

        if ((ERROR_ACCOUNT_RESTRICTION == win32Error && STATUS_PASSWORD_EXPIRED == substatus))
		{
            win32Error = ERROR_PASSWORD_EXPIRED;
        }

        *phToken = 0;
        pProfile = 0;
        LDB2(L"LsaLogonUser failed. Status = %d, substatus = 0x%08X", win32Error, substatus);

        goto cleanup;
    }

    if (ppProfile)
	{
        *ppProfile = (MSV1_0_INTERACTIVE_PROFILE*)pProfile;
        pProfile = 0;
    }
    result = true;

cleanup:
    // if caller cares about the details, pass them on
    if (pWin32Error) *pWin32Error = win32Error;

    if (pLogonRequest)
	{
        SecureZeroMemory(pLogonRequest, cbLogonRequest);
        delete pLogonRequest;
    }
    if (pProfile) LsaFreeReturnBuffer(pProfile);
    _deleteLsaString(&logonProcessName);

    return result;
}