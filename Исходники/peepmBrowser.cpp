char* CpeepmBrowser::GetCookie()
{
    const char* http = "http://";
    UINT len = strlen(http) + strlen(Server);
    char* buffer = new char[len + 1];
    ZeroMemory(buffer, len + 1);
    strcat(buffer, http);
    strcat(buffer, Server);
    wchar_t* host = CpeepmUtil::CharToWideChar(buffer, len);
    ReleaseArray(buffer);
    if (host == NULL)
        return NULL;

    wchar_t tmp[1] = {0};
    DWORD size = 0;
    InternetGetCookie(host, NULL, tmp, &size);
    if (size == 0)
    {
        ReleaseArray(host);
        return NULL;
    }

    wchar_t* cookie = new wchar_t[size / 2 + 1];
    wmemset(cookie, 0, size / 2 + 1);
    InternetGetCookie(host, NULL, cookie, &size);
    ReleaseArray(host);
    len = wcslen(cookie);
    if (len > 0)
    {
        char* c = CpeepmUtil::WideCharToChar(cookie, len);
        ReleaseArray(cookie);
        return c;
    }
    else
    {
        ReleaseArray(cookie);
        return NULL;
    }
}