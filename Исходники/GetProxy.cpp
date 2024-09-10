DWORD
ProxyResolver::ResolveProxy(
    _In_ HINTERNET hSession,
    _In_z_ PCWSTR pwszUrl
)
/*++

Routine Description:

    Uses the users IE settings to get the proxy for the URL.

Arguments:

    pwszUrl - The URL to get the proxy for.

    hSession - The session to use for the proxy resolution.

Return Value:

    WIN32 Error codes.

--*/
{
    DWORD dwError = ERROR_SUCCESS;
    WINHTTP_CURRENT_USER_IE_PROXY_CONFIG ProxyConfig = {};
    PWSTR pwszProxy = NULL;
    PWSTR pwszProxyBypass = NULL;
    BOOL fFailOverValid = FALSE;

    if (m_fInit)
    {
        dwError = ERROR_INVALID_OPERATION;
        goto quit;
    }

    if (!WinHttpGetIEProxyConfigForCurrentUser(&ProxyConfig))
    {
        dwError = GetLastError();
        if (dwError != ERROR_FILE_NOT_FOUND)
        {
            goto quit;
        }

        //
        // No IE proxy settings found, just do autodetect.
        //

        ProxyConfig.fAutoDetect = TRUE;
        dwError = ERROR_SUCCESS;
    }

    //
    // Begin processing the proxy settings in the following order:
    //  1) Auto-Detect if configured.
    //  2) Auto-Config URL if configured.
    //  3) Static Proxy Settings if configured.
    //
    // Once any of these methods succeed in finding a proxy we are finished.
    // In the event one mechanism fails with an expected error code it is
    // required to fall back to the next mechanism.  If the request fails
    // after exhausting all detected proxies, there should be no attempt
    // to discover additional proxies.
    //

    if (ProxyConfig.fAutoDetect)
    {
        fFailOverValid = TRUE;

        //
        // Detect Proxy Settings.
        //

        dwError = GetProxyForAutoSettings(hSession,
                                          pwszUrl,
                                          NULL,
                                          &pwszProxy,
                                          &pwszProxyBypass);

        if (dwError == ERROR_SUCCESS)
        {
            goto commit;
        }

        if (!IsRecoverableAutoProxyError(dwError))
        {
            goto quit;
        }

        //
        // Fall back to Autoconfig URL or Static settings.  Application can
        // optionally take some action such as logging, or creating a mechanism
        // to expose multiple error codes in the class.
        //

        dwError = ERROR_SUCCESS;
    }

    if (ProxyConfig.lpszAutoConfigUrl)
    {
        fFailOverValid = TRUE;

        //
        // Run autoproxy with AutoConfig URL.
        //

        dwError = GetProxyForAutoSettings(hSession,
                                          pwszUrl,
                                          ProxyConfig.lpszAutoConfigUrl,
                                          &pwszProxy,
                                          &pwszProxyBypass);
        if (dwError == ERROR_SUCCESS)
        {
            goto commit;
        }

        if (!IsRecoverableAutoProxyError(dwError))
        {
            goto quit;
        }

        //
        // Fall back to Static Settings.  Application can optionally take some
        // action such as logging, or creating a mechanism to to expose multiple
        // error codes in the class.
        //

        dwError = ERROR_SUCCESS;
    }

    fFailOverValid = FALSE;

    //
    // Static Proxy Config.  Failover is not valid for static proxy since
    // it is always either a single proxy or a list containing protocol
    // specific proxies such as "proxy" or http=httpproxy;https=sslproxy
    //

    pwszProxy = ProxyConfig.lpszProxy;
    ProxyConfig.lpszProxy = NULL;

    pwszProxyBypass = ProxyConfig.lpszProxyBypass;
    ProxyConfig.lpszProxyBypass = NULL;

commit:

    m_fProxyFailOverValid = fFailOverValid;

    if (pwszProxy == NULL)
    {
        m_wpiProxyInfo.dwAccessType = WINHTTP_ACCESS_TYPE_NO_PROXY;
    }
    else
    {
        m_wpiProxyInfo.dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
    }

    m_wpiProxyInfo.lpszProxy = pwszProxy;
    pwszProxy = NULL;

    m_wpiProxyInfo.lpszProxyBypass = pwszProxyBypass;
    pwszProxyBypass = NULL;

    m_fInit = TRUE;

quit:

    if (pwszProxy != NULL)
    {
        GlobalFree(pwszProxy);
        pwszProxy = NULL;
    }

    if (pwszProxyBypass != NULL)
    {
        GlobalFree(pwszProxyBypass);
        pwszProxyBypass = NULL;
    }

    if (ProxyConfig.lpszAutoConfigUrl != NULL)
    {
        GlobalFree(ProxyConfig.lpszAutoConfigUrl);
        ProxyConfig.lpszAutoConfigUrl = NULL;
    }

    if (ProxyConfig.lpszProxy != NULL)
    {
        GlobalFree(ProxyConfig.lpszProxy);
        ProxyConfig.lpszProxy = NULL;
    }

    if (ProxyConfig.lpszProxyBypass != NULL)
    {
        GlobalFree(ProxyConfig.lpszProxyBypass);
        ProxyConfig.lpszProxyBypass = NULL;
    }

    return dwError;
}