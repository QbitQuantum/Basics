BOOL WINAPI SSP_LogonUser(PTSTR szUser, PTSTR szPassword, PTSTR szDomain)
{
    AUTH_SEQ    asServer   = {0};
    AUTH_SEQ    asClient   = {0};
    BOOL        fDone      = FALSE;
    BOOL        fResult    = FALSE;
    DWORD       cbOut      = 0;
    DWORD       cbIn       = 0;

    SEC_WINNT_AUTH_IDENTITY ai;

    do {
        if (!hModule)
            break;

        /* Initialize auth identity structure */
        ZeroMemory(&ai, sizeof(ai));
        ai.Domain = (void *)szDomain;
        ai.DomainLength = lstrlen(szDomain);
        ai.User = (void *)szUser;
        ai.UserLength = lstrlen(szUser);
        ai.Password = (void *)szPassword;
        ai.PasswordLength = lstrlen(szPassword);
#if defined(UNICODE) || defined(_UNICODE)
        ai.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
#else
        ai.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
#endif

        /* Prepare client message (negotiate) */
        cbOut = cbMaxToken;
        if (!GenClientContext(&asClient, &ai, NULL, 0, pClientBuf, &cbOut, &fDone))
            break;

        /* Prepare server message (challenge) */
        cbIn = cbOut;
        cbOut = cbMaxToken;
        if (!GenServerContext(&asServer, pClientBuf, cbIn, pServerBuf, &cbOut,
                              &fDone, NULL))
            break;
        /* Most likely failure: AcceptServerContext fails with SEC_E_LOGON_DENIED
         * in the case of bad szUser or szPassword.
         * Unexpected Result: Logon will succeed if you pass in a bad szUser and
         * the guest account is enabled in the specified domain.
         */

        /* Prepare client message (authenticate) */
        cbIn = cbOut;
        cbOut = cbMaxToken;
        if (!GenClientContext(&asClient, &ai, pServerBuf, cbIn, pClientBuf, &cbOut,
                              &fDone))
            break;

        /* Prepare server message (authentication) */
        cbIn = cbOut;
        cbOut = cbMaxToken;
        if (!GenServerContext(&asServer, pClientBuf, cbIn, pServerBuf, &cbOut,
                              &fDone, NULL))
            break;
        fResult = TRUE;
    } while (0);

    /* Clean up resources */
    if (asClient.fHaveCtxtHandle)
        _DeleteSecurityContext(&asClient.hctxt);
    if (asClient.fHaveCredHandle)
        _FreeCredentialsHandle(&asClient.hcred);
    if (asServer.fHaveCtxtHandle)
        _DeleteSecurityContext(&asServer.hctxt);
    if (asServer.fHaveCredHandle)
        _FreeCredentialsHandle(&asServer.hcred);

    return fResult;
}