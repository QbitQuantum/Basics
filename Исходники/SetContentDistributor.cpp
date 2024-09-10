HRESULT SetContentDistributor(WCHAR *pszFilename, WCHAR *pszProvider)
{
    CComPtr<IWMMetadataEditor> spEditor;
    HRESULT hr = WMCreateEditor(&spEditor);
    if (SUCCEEDED(hr))
    {
        hr = spEditor->Open(pszFilename);
        if (SUCCEEDED(hr))
        {
            CComPtr<IWMHeaderInfo> spHeaderInfo;
            hr = spEditor->QueryInterface(__uuidof(IWMHeaderInfo), reinterpret_cast<void**>(&spHeaderInfo));
            if (SUCCEEDED(hr))
            {
                WORD wLength = sizeof(WCHAR)*(wcslen(pszProvider) + 1);
                hr = spHeaderInfo->SetAttribute(0, g_wszWMContentDistributor, WMT_TYPE_STRING, (const BYTE*)pszProvider, wLength);
            }
            spEditor->Flush();
            spEditor->Close();
        }
    }

    return hr;
}