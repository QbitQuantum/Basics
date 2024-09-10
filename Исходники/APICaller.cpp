wchar_t *APICaller::GetHeader(HINTERNET request, int req)
{
    wchar_t *headerBuffer = NULL;
    DWORD bytesRead = 0;

    // Get header info
    WinHttpQueryHeaders(request, WINHTTP_QUERY_CONTENT_ENCODING, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &bytesRead, WINHTTP_NO_HEADER_INDEX);
    if (bytesRead > 0) {
        headerBuffer = new wchar_t[bytesRead / sizeof(wchar_t)];
        WinHttpQueryHeaders(request, WINHTTP_QUERY_CONTENT_ENCODING, WINHTTP_HEADER_NAME_BY_INDEX, headerBuffer, &bytesRead, WINHTTP_NO_HEADER_INDEX);
    }

    return headerBuffer;
}