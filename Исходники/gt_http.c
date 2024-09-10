int GTHTTP_sendRequest(const char *url,
                       const unsigned char *request, size_t request_length,
                       unsigned char **response, size_t *response_length,
                       char **error)
{
    int res = GT_UNKNOWN_ERROR;
    char *host = NULL, *query = NULL;
    URL_COMPONENTS uc = { sizeof(uc) };
    HINTERNET cnx = NULL, req = NULL;
    DWORD http_res;
    DWORD http_res_len = sizeof(http_res);
    char *http_msg = NULL;
    DWORD http_msg_len = 0;
    unsigned char *resp = NULL;
    size_t resp_len = 0;

    if (url == NULL || response == NULL || response_length == NULL) {
        res = GT_INVALID_ARGUMENT;
        goto cleanup;
    }

    // extract host, port, and query from the URL
    uc.dwHostNameLength = 1;
    uc.dwUrlPathLength = 1;
    uc.dwExtraInfoLength = 1;
    if (!InternetCrackUrlA(url, 0, 0, &uc)) {
        res = map_impl(GetLastError());
        goto cleanup;
    }
    if (uc.lpszHostName == NULL || uc.dwHostNameLength == 0) {
        res = GT_INVALID_ARGUMENT;
        goto cleanup;
    }
    host = GT_malloc(uc.dwHostNameLength + 1);
    if (host == NULL) {
        res = GT_OUT_OF_MEMORY;
        goto cleanup;
    }
    strncpy_s(host, uc.dwHostNameLength + 1, uc.lpszHostName, uc.dwHostNameLength);
    if (uc.lpszUrlPath == NULL || uc.dwUrlPathLength == 0) {
        res = GT_INVALID_ARGUMENT;
        goto cleanup;
    }
    query = GT_malloc(uc.dwUrlPathLength + uc.dwExtraInfoLength + 1);
    if (query == NULL) {
        res = GT_OUT_OF_MEMORY;
        goto cleanup;
    }
    strncpy_s(query, uc.dwUrlPathLength + 1, uc.lpszUrlPath, uc.dwUrlPathLength);
    if (!(uc.lpszExtraInfo == NULL || uc.dwExtraInfoLength == 0)) {
        strncpy_s(query + uc.dwUrlPathLength, uc.dwExtraInfoLength + 1, uc.lpszExtraInfo, uc.dwExtraInfoLength);
    }

    // open the connection and send the request
    cnx = InternetConnectA(session_handle, host, uc.nPort, NULL, NULL, uc.nScheme, 0, 0);
    if (cnx == NULL) {
        res = map_impl(GetLastError());
        goto cleanup;
    }
    req = HttpOpenRequestA(cnx,
                           (request == NULL ? "GET" : "POST"),
                           query, NULL, NULL, NULL,
                           (uc.nScheme == INTERNET_SCHEME_HTTPS ? INTERNET_FLAG_SECURE : 0),
                           0);
    if (req == NULL) {
        res = map_impl(GetLastError());
        goto cleanup;
    }
    if (connect_timeout >= 0) {
        DWORD dw = (connect_timeout == 0 ? 0xFFFFFFFF : connect_timeout * 1000);
        InternetSetOption(req, INTERNET_OPTION_CONNECT_TIMEOUT, &dw, sizeof(dw));
    }
    if (response_timeout >= 0) {
        DWORD dw = (response_timeout == 0 ? 0xFFFFFFFF : response_timeout * 1000);
        InternetSetOption(req, INTERNET_OPTION_SEND_TIMEOUT, &dw, sizeof(dw));
        InternetSetOption(req, INTERNET_OPTION_RECEIVE_TIMEOUT, &dw, sizeof(dw));
    }
again:
    if (!HttpSendRequestA(req, NULL, 0, (LPVOID) request, request_length)) {
        res = map_impl(GetLastError());
        goto cleanup;
    }

    // receive the response
    if (!HttpQueryInfo(req, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
                       &http_res, &http_res_len, 0)) {
        res = map_impl(GetLastError());
        goto cleanup;
    }

    // proxy server requires authentication, prompt user
    if (http_res == HTTP_STATUS_PROXY_AUTH_REQ) {
        if (InternetErrorDlg(GetDesktopWindow(), req,
                             ERROR_INTERNET_INCORRECT_PASSWORD,
                             FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
                             FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
                             FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
                             NULL) == ERROR_INTERNET_FORCE_RETRY) {
            goto again;
        }
    }

    // web server requires authentication, prompt user
    if (http_res == HTTP_STATUS_DENIED) {
        if (InternetErrorDlg(GetDesktopWindow(), req,
                             ERROR_INTERNET_INCORRECT_PASSWORD,
                             FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
                             FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
                             FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
                             NULL) == ERROR_INTERNET_FORCE_RETRY) {
            goto again;
        }
    }

    if (http_res >= 400) {
        res = map_http(http_res);
        if (error != NULL) {
            // we had some error and client code wanted the message
            if (HttpQueryInfoA(req, HTTP_QUERY_STATUS_TEXT, http_msg, &http_msg_len, 0) ||
                    GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
                // unexpected results retrieving the HTTP error message
                // just report the HTTP error code
                goto cleanup;
            }
            http_msg = GT_malloc(http_msg_len);
            if (http_msg == NULL) {
                // no memory for the HTTP error message
                // just report the HTTP error code
                goto cleanup;
            }
            if (!HttpQueryInfoA(req, HTTP_QUERY_STATUS_TEXT, http_msg, &http_msg_len, 0)) {
                // unexpected results retrieving the HTTP error message
                // just report the HTTP error code
                goto cleanup;
            }
            *error = http_msg;
            http_msg = NULL;
        }
        goto cleanup;
    }

    while (1) {
        DWORD add_len = 0x2000; // download in 8K increments
        resp = GT_realloc(resp, resp_len + add_len);
        if (resp == NULL) {
            res = GT_OUT_OF_MEMORY;
            goto cleanup;
        }
        if (!InternetReadFile(req, resp + resp_len, add_len, &add_len)) {
            res = map_impl(GetLastError());
            goto cleanup;
        }
        if (add_len == 0) {
            break;
        }
        resp_len += add_len;
    }

    *response = resp;
    resp = NULL;
    *response_length = resp_len;
    res = GT_OK;

cleanup:

    GT_free(resp);
    GT_free(http_msg);
    if (req != NULL) {
        InternetCloseHandle(req);
    }
    if (cnx != NULL) {
        InternetCloseHandle(cnx);
    }
    GT_free(query);
    GT_free(host);
    return res;
}