//
// Description:
//  Retrieves that the service manage uses to launch the YoNTMA binary as a
//  service.
//
// Parameters:
//  ppszServiceExecutionString - On success, contains the command line string
//      used to launch YoNTMA (including arguments). Caller must free with
//      HB_SAFE_FREE.
//
HRESULT GetServiceExecutionString(__out PTSTR* ppszServiceExecutionString)
{
    HRESULT hr;
    DWORD rc;
    SC_HANDLE hService = NULL;
    LPQUERY_SERVICE_CONFIG pQueryServiceConfig = NULL;
    DWORD cbQueryServiceConfig;
    DWORD cbQueryServiceConfigRequired;
    PTSTR pszServiceExecutionStringLocal = NULL;
    size_t cchServiceExecutionStringLocal;
    size_t cbServiceExecutionStringLocal;

    hr = OpenYontmaService(&hService);
    if(HB_FAILED(hr)) {
        goto cleanexit;
    }

    QueryServiceConfig(hService,
                       NULL,
                       0,
                       &cbQueryServiceConfigRequired);

    rc = GetLastError();

    //
    // QueryServiceConfig succeeded with a zero-sized buffer? Something is wrong.
    //

    if(rc == ERROR_SUCCESS) {
        hr = E_UNEXPECTED;
        goto cleanexit;
    }
    else if(rc != ERROR_INSUFFICIENT_BUFFER) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto cleanexit;
    }

    cbQueryServiceConfig = cbQueryServiceConfigRequired;
    pQueryServiceConfig = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LMEM_FIXED, cbQueryServiceConfig);
    if(!pQueryServiceConfig) {
        hr = E_OUTOFMEMORY;
        goto cleanexit;
    }

    if(!QueryServiceConfig(hService,
                           pQueryServiceConfig,
                           cbQueryServiceConfig,
                           &cbQueryServiceConfigRequired)) {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto cleanexit;
    }

    cchServiceExecutionStringLocal = _tcslen(pQueryServiceConfig->lpBinaryPathName);
    hr = SizeTAdd(cchServiceExecutionStringLocal,
                  1,
                  &cchServiceExecutionStringLocal);
    if(HB_FAILED(hr)) {
        goto cleanexit;
    }

    hr = SizeTMult(cchServiceExecutionStringLocal, sizeof(TCHAR), &cbServiceExecutionStringLocal);
    if(HB_FAILED(hr)) {
        goto cleanexit;
    }

    pszServiceExecutionStringLocal = (PTSTR)malloc(cbServiceExecutionStringLocal);
    if(!pszServiceExecutionStringLocal) {
        hr = E_OUTOFMEMORY;
        goto cleanexit;
    }

    hr = StringCchCopy(pszServiceExecutionStringLocal,
                       cchServiceExecutionStringLocal,
                       pQueryServiceConfig->lpBinaryPathName);
    if(HB_FAILED(hr)) {
        goto cleanexit;
    }

    *ppszServiceExecutionString = pszServiceExecutionStringLocal;
    pszServiceExecutionStringLocal = NULL;

cleanexit:
    HB_SAFE_CLOSE_SERVICE_HANDLE(hService);
    HB_SAFE_LOCAL_FREE(pQueryServiceConfig);
    HB_SAFE_FREE(pszServiceExecutionStringLocal);

    return hr;
}