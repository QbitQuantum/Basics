static LPWSTR
QueryWindowsProxySettings(const url_scheme scheme, LPCSTR host)
{
    LPWSTR proxy = NULL;
    BOOL auto_detect = TRUE;
    LPWSTR auto_config_url = NULL;
    WINHTTP_CURRENT_USER_IE_PROXY_CONFIG proxy_config;

    if (WinHttpGetIEProxyConfigForCurrentUser(&proxy_config))
    {
        proxy = proxy_config.lpszProxy;
        auto_detect = proxy_config.fAutoDetect;
        auto_config_url = proxy_config.lpszAutoConfigUrl;
        GlobalFree(proxy_config.lpszProxyBypass);
    }

    if (auto_detect)
    {
        LPWSTR old_url = auto_config_url;
        DWORD flags = WINHTTP_AUTO_DETECT_TYPE_DHCP | WINHTTP_AUTO_DETECT_TYPE_DNS_A;
        if (WinHttpDetectAutoProxyConfigUrl(flags, &auto_config_url))
            GlobalFree(old_url);
    }

    if (auto_config_url)
    {
        HINTERNET session = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_NO_PROXY,
            WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
        if (session)
        {
            int size = _snwprintf(NULL, 0, L"%s://%S", UrlSchemeStr(scheme), host) + 1;
            LPWSTR url = malloc(size * sizeof(WCHAR));
            if (url)
            {
                _snwprintf(url, size, L"%s://%S", UrlSchemeStr(scheme), host);

                LPWSTR old_proxy = proxy;
                WINHTTP_PROXY_INFO proxy_info;
                WINHTTP_AUTOPROXY_OPTIONS options = {
                    .fAutoLogonIfChallenged = TRUE,
                    .dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL,
                    .lpszAutoConfigUrl = auto_config_url,
                    .dwAutoDetectFlags = 0,
                    .lpvReserved = NULL,
                    .dwReserved = 0
                };

                if (WinHttpGetProxyForUrl(session, url, &options, &proxy_info))
                {
                    GlobalFree(old_proxy);
                    GlobalFree(proxy_info.lpszProxyBypass);
                    proxy = proxy_info.lpszProxy;
                }
                free(url);
            }
            WinHttpCloseHandle(session);
        }
        GlobalFree(auto_config_url);
    }

    return proxy;
}


static VOID
ParseProxyString(LPWSTR proxy_str, url_scheme scheme,
                 LPCSTR *type, LPCWSTR *host, LPCWSTR *port)
{
    if (proxy_str == NULL)
        return;

    LPCWSTR delim = L"; ";
    LPWSTR token = wcstok(proxy_str, delim);

    LPCWSTR scheme_str = UrlSchemeStr(scheme);
    LPCWSTR socks_str = UrlSchemeStr(SOCKS_URL);

    /* Token format: [<scheme>=][<scheme>"://"]<server>[":"<port>] */
    while (token)
    {
        BOOL match = FALSE;
        LPWSTR eq = wcschr(token, '=');
        LPWSTR css = wcsstr(token, L"://");

        /*
         * If the token has a <scheme>, test for the one we're looking for.
         * If we're looking for a https proxy, socks will also do.
         * If it's a proxy without a <scheme> it's only good for https.
         */
        if (eq || css)
        {
            if (wcsbegins(token, scheme_str))
            {
                match = TRUE;
            }
            else if (scheme == HTTPS_URL && wcsbegins(token, socks_str))
            {
                match = TRUE;
                scheme = SOCKS_URL;
            }
        }
        else if (scheme == HTTPS_URL)
        {
            match = TRUE;
        }

        if (match)
        {
            LPWSTR server = token;
            if (css)
                server = css + 3;
            else if (eq)
                server = eq + 1;

            /* IPv6 addresses are surrounded by brackets */
            LPWSTR port_delim;
            if (server[0] == '[')
            {
                server += 1;
                LPWSTR end = wcschr(server, ']');
                if (end == NULL)
                    continue;
                *end++ = '\0';

                port_delim = (*end == ':' ? end : NULL);
            }
            else
            {
                port_delim = wcsrchr(server, ':');
                if (port_delim)
                    *port_delim = '\0';
            }

            *type = (scheme == HTTPS_URL ? "HTTP" : "SOCKS");
            *host = server;
            if (port_delim)
                *port = port_delim + 1;
            else
                *port = (scheme == HTTPS_URL ? L"80": L"1080");

            break;
        }
        token = wcstok(NULL, delim);
    }
}


/*
 * Respond to management interface PROXY notifications
 * Input format: REMOTE_NO,PROTOCOL,HOST
 */
void
OnProxy(connection_t *c, char *line)
{
    LPSTR proto, host;
    char *pos = strchr(line, ',');
    if (pos == NULL)
        return;

    proto = ++pos;
    pos = strchr(pos, ',');
    if (pos == NULL)
        return;

    *pos = '\0';
    host = ++pos;
    if (host[0] == '\0')
        return;

    LPCSTR type = "NONE";
    LPCWSTR addr = L"", port = L"";
    LPWSTR proxy_str = NULL;

    if (o.proxy_source == manual)
    {
        if (o.proxy_type == http && streq(proto, "TCP"))
        {
            type = "HTTP";
            addr = o.proxy_http_address;
            port = o.proxy_http_port;
        }
        else if (o.proxy_type == socks)
        {
            type = "SOCKS";
            addr = o.proxy_socks_address;
            port = o.proxy_socks_port;
        }
    }
    else if (o.proxy_source == windows)
    {
        url_scheme scheme = (streq(proto, "TCP") ? HTTPS_URL : SOCKS_URL);
        proxy_str = QueryWindowsProxySettings(scheme, host);
        ParseProxyString(proxy_str, scheme, &type, &addr, &port);
    }

    char cmd[128];
    snprintf(cmd, sizeof(cmd), "proxy %s %S %S", type, addr, port);
    cmd[sizeof(cmd) - 1] = '\0';
    ManagementCommand(c, cmd, NULL, regular);

    GlobalFree(proxy_str);
}