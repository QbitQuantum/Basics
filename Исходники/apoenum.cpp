HRESULT EnumerateAudioProcessingObjects() {
    UINT32 nCount = 0;

    HRESULT hr = EnumerateAPOs(myEnumerateAPOsCallback, &nCount);
    if (FAILED(hr)) {
        ERR(L"EnumerateAPOs failed: hr = 0x%08x", hr);
        return hr;
    }

    LOG(L"APOs found: %u", nCount);

    return S_OK;
}