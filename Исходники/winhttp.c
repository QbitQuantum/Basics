void
shoes_winhttp_headers(HINTERNET req, shoes_download_handler handler, void *data)
{ 
  DWORD size;
  WinHttpQueryHeaders(req, WINHTTP_QUERY_RAW_HEADERS,
    WINHTTP_HEADER_NAME_BY_INDEX, NULL, &size, WINHTTP_NO_HEADER_INDEX);

  if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    int whdrlen = 0, hdrlen = 0;
    LPCWSTR whdr;
    LPSTR hdr = SHOE_ALLOC_N(CHAR, MAX_PATH);
    LPCWSTR hdrs = SHOE_ALLOC_N(WCHAR, size/sizeof(WCHAR));
    BOOL res = WinHttpQueryHeaders(req, WINHTTP_QUERY_RAW_HEADERS,
      WINHTTP_HEADER_NAME_BY_INDEX, (LPVOID)hdrs, &size, WINHTTP_NO_HEADER_INDEX);
    if (res)
    {
      for (whdr = hdrs; whdr - hdrs < size / sizeof(WCHAR); whdr += whdrlen)
      {
        WideCharToMultiByte(CP_UTF8, 0, whdr, -1, hdr, MAX_PATH, NULL, NULL);
        hdrlen = strlen(hdr);
        HTTP_HEADER(hdr, hdrlen, handler, data);
        whdrlen = wcslen(whdr) + 1;
      }
    }
    SHOE_FREE(hdrs);
    SHOE_FREE(hdr);
  }
}