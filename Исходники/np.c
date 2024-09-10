static DWORD FspNpGetCredentials(
    HWND hwndOwner, PWSTR Caption, DWORD PrevNpResult,
    DWORD CredentialsKind,
    PBOOL PSave,
    PWSTR UserName, ULONG UserNameSize/* in chars */,
    PWSTR Password, ULONG PasswordSize/* in chars */)
{
    DWORD NpResult;
    CREDUI_INFOW UiInfo;

    memset(&UiInfo, 0, sizeof UiInfo);
    UiInfo.cbSize = sizeof UiInfo;
    UiInfo.hwndParent = hwndOwner;
    UiInfo.pszCaptionText = Caption;
    UiInfo.pszMessageText = L"Enter credentials to unlock this file system.";

#if !defined(FSP_NP_CREDUI_PROMPT_NEW)
    NpResult = CredUIPromptForCredentialsW(&UiInfo, L"NONE", 0, 0,
        UserName, UserNameSize,
        Password, PasswordSize,
        PSave,
        CREDUI_FLAGS_GENERIC_CREDENTIALS |
        CREDUI_FLAGS_DO_NOT_PERSIST |
        CREDUI_FLAGS_ALWAYS_SHOW_UI |
        (0 != PrevNpResult ? CREDUI_FLAGS_INCORRECT_PASSWORD : 0) |
        (0 != PSave ? CREDUI_FLAGS_SHOW_SAVE_CHECK_BOX : 0) |
        (FSP_NP_CREDENTIALS_PASSWORD == CredentialsKind ? 0/*CREDUI_FLAGS_KEEP_USERNAME*/ : 0));
#else
    WCHAR Domain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
    ULONG AuthPackage = 0;
    PVOID InAuthBuf = 0, OutAuthBuf = 0;
    ULONG InAuthSize, OutAuthSize, DomainSize;

    InAuthSize = 0;
    if (!CredPackAuthenticationBufferW(
            CRED_PACK_GENERIC_CREDENTIALS, UserName, Password, 0, &InAuthSize) &&
        ERROR_INSUFFICIENT_BUFFER != GetLastError())
    {
        NpResult = GetLastError();
        goto exit;
    }

    InAuthBuf = MemAlloc(InAuthSize);
    if (0 == InAuthBuf)
    {
        NpResult = ERROR_NO_SYSTEM_RESOURCES;
        goto exit;
    }

    if (!CredPackAuthenticationBufferW(
        CRED_PACK_GENERIC_CREDENTIALS, UserName, Password, InAuthBuf, &InAuthSize))
    {
        NpResult = GetLastError();
        goto exit;
    }

    NpResult = CredUIPromptForWindowsCredentialsW(&UiInfo, PrevNpResult,
        &AuthPackage, InAuthBuf, InAuthSize, &OutAuthBuf, &OutAuthSize, PSave,
        CREDUIWIN_GENERIC | (0 != PSave ? CREDUIWIN_CHECKBOX : 0));
    if (ERROR_SUCCESS != NpResult)
        goto exit;

    DomainSize = sizeof Domain / sizeof Domain[0];
    if (!CredUnPackAuthenticationBufferW(0, OutAuthBuf, OutAuthSize,
        UserName, &UserNameSize, Domain, &DomainSize, Password, &PasswordSize))
    {
        NpResult = GetLastError();
        goto exit;
    }

    NpResult = ERROR_SUCCESS;

exit:
    if (0 != OutAuthBuf)
    {
        SecureZeroMemory(OutAuthBuf, OutAuthSize);
        CoTaskMemFree(OutAuthBuf);
    }

    if (0 != InAuthBuf)
    {
        SecureZeroMemory(InAuthBuf, InAuthSize);
        MemFree(InAuthBuf);
    }
#endif

    return NpResult;
}