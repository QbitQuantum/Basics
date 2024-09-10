void sendPUTRequest(const std::string& server, const std::string& data)
{
    HRESULT hr;
    CLSID clsid;
    IWinHttpRequest *pIWinHttpRequest = NULL;

    _variant_t varFalse(false);
    _variant_t varData(data.c_str());

    hr = CLSIDFromProgID(L"WinHttp.WinHttpRequest.5.1", &clsid);
    if (SUCCEEDED(hr)){
        hr = CoCreateInstance(clsid, NULL,
            CLSCTX_INPROC_SERVER,
            IID_IWinHttpRequest,
            (void **)&pIWinHttpRequest);
    }

    if (SUCCEEDED(hr)){
        hr = pIWinHttpRequest->SetTimeouts(1000, 1000, 2000, 1000);
    }

    if (SUCCEEDED(hr)){
        _bstr_t method("PUT");
        _bstr_t url(server.c_str());
        hr = pIWinHttpRequest->Open(method, url, varFalse);
    }

    if (SUCCEEDED(hr)){
        hr = pIWinHttpRequest->Send(varData);
    }

    pIWinHttpRequest->Release();
}