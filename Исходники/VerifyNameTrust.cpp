BOOL
IsFilePublisherTrusted(
    LPCWSTR pwszFileName
)
{
    BOOL trusted = FALSE;
    DWORD lastError;
    GUID wvtProvGuid = WINTRUST_ACTION_GENERIC_VERIFY_V2;

    //
    // Initialize structure for WinVerifyTrust call
    //

    WINTRUST_DATA wtd = { 0 };
    WINTRUST_FILE_INFO wtfi = { 0 };

    wtd.cbStruct = sizeof(WINTRUST_DATA);
    wtd.pPolicyCallbackData = NULL;
    wtd.pSIPClientData = NULL;
    wtd.dwUIChoice = WTD_UI_NONE;
    wtd.fdwRevocationChecks = WTD_REVOKE_WHOLECHAIN;
    wtd.dwUnionChoice = WTD_CHOICE_FILE;
    wtd.pFile = &wtfi;
    wtd.dwStateAction = WTD_STATEACTION_VERIFY;
    wtd.hWVTStateData = NULL;
    wtd.pwszURLReference = NULL;
    wtd.dwProvFlags = WTD_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT;

    wtfi.cbStruct = sizeof(WINTRUST_FILE_INFO);
    wtfi.pcwszFilePath = pwszFileName;
    wtfi.hFile = NULL;
    wtfi.pgKnownSubject = NULL;

    //
    // Check the file's Authenticode signature
    //

    if (S_OK != WinVerifyTrust((HWND)INVALID_HANDLE_VALUE, &wvtProvGuid, &wtd))
    {
        lastError = GetLastError();
        goto Cleanup;
    }

    //
    // Get provider data
    //

    CRYPT_PROVIDER_DATA* pProvData = WTHelperProvDataFromStateData(wtd.hWVTStateData);
    if (NULL == pProvData)
    {
        lastError = GetLastError();
        goto Cleanup;
    }

    //
    // Get the signer
    //

    CRYPT_PROVIDER_SGNR* pProvSigner = WTHelperGetProvSignerFromChain(pProvData, 0, FALSE, 0);
    if (NULL == pProvSigner)
    {
        lastError = GetLastError();
        goto Cleanup;
    }

    if (!IsTrustedRootKey(pProvSigner->pChainContext))
    {
        goto Cleanup;
    }

    if (!IsTrustedPublisherName(pProvSigner->pChainContext))
    {
        goto Cleanup;
    }

    //
    // If we made it this far, we can trust the file
    //

    trusted = TRUE;

Cleanup:
    //
    // Close the previously-opened state data handle
    //

    wtd.dwStateAction = WTD_STATEACTION_CLOSE;
    WinVerifyTrust((HWND)INVALID_HANDLE_VALUE, &wvtProvGuid, &wtd);

    return trusted;
}