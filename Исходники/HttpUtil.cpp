// returns false if failed to download or status code is not 200
// for other scenarios, check HttpRsp
bool  HttpGet(const WCHAR *url, HttpRsp *rspOut)
{
    HINTERNET hReq = nullptr;
    DWORD headerBuffSize = sizeof(DWORD);
    DWORD flags = INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_RELOAD;

    rspOut->error = ERROR_SUCCESS;
    HINTERNET hInet = InternetOpen(USER_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
    if (!hInet)
        goto Error;

    hReq = InternetOpenUrl(hInet, url, nullptr, 0, flags, 0);
    if (!hReq)
        goto Error;

    if (!HttpQueryInfoW(hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &rspOut->httpStatusCode, &headerBuffSize, nullptr)) {
        goto Error;
    }

    for (;;) {
        char buf[1024];
        DWORD dwRead = 0;
        if (!InternetReadFile(hReq, buf, sizeof(buf), &dwRead)) {
            goto Error;
        }
        if (0 == dwRead) {
            break;
        }
        bool ok = rspOut->data.AppendChecked(buf, dwRead);
        if (!ok)
            goto Error;
    }

Exit:
    if (hReq)
        InternetCloseHandle(hReq);
    if (hInet)
        InternetCloseHandle(hInet);
    return HttpRspOk(rspOut);

Error:
    rspOut->error = GetLastError();
    if (0 == rspOut->error)
        rspOut->error = ERROR_GEN_FAILURE;
    goto Exit;
}