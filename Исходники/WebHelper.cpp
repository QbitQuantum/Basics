HRESULT WebHelper::OpenURLWithData(const WCHAR *wszURL, const BYTE *pbPostData, DWORD cbData)
{
    // This string is the header needed for HTTP POST actions.
    const LPWSTR POST_HEADER_DATA = L"Content-Type: application/x-www-form-urlencoded\r\n";

    if (!wszURL)
    {
        return E_INVALIDARG;
    }

    if (!m_pBrowser)
    {
        return E_UNEXPECTED;
    }
    
    HRESULT hr = S_OK;
    BSTR    bstrURL = NULL;
    VARIANT vtEmpty;
    VARIANT vtHeader;
    VARIANT vtPostData;

    VariantInit(&vtEmpty);
    VariantInit(&vtHeader);
    VariantInit(&vtPostData);

    // Allocate a BSTR for the URL.
    bstrURL = SysAllocString(wszURL);
    if (bstrURL == NULL)
    {
        hr = E_OUTOFMEMORY;
    }

    // Allocate a BSTR for the header.
    if (SUCCEEDED(hr))
    {
        vtHeader.bstrVal = SysAllocString(POST_HEADER_DATA);
        if (vtHeader.bstrVal == NULL)
        {
            hr = E_OUTOFMEMORY;
        }
        else
        {
            vtHeader.vt = VT_BSTR;
        }
    }


    if (SUCCEEDED(hr))
    {
        if ( pbPostData )
        {
            // Convert the POST data to a safe array in a variant. The safe array type is VT_UI1.

            void *pvData = NULL;
            SAFEARRAY *saPostData = SafeArrayCreateVector(VT_UI1, 0, cbData);
            if (saPostData == NULL)
            {
                hr = E_OUTOFMEMORY;
            }

            if (SUCCEEDED(hr))
            {
                hr = SafeArrayAccessData(saPostData, &pvData);
            }

            if (SUCCEEDED(hr))
            {
                CopyMemory((BYTE*)pvData, pbPostData, cbData);
                hr = SafeArrayUnaccessData(saPostData);
            }

            if (SUCCEEDED(hr))
            {
                vtPostData.vt = VT_ARRAY | VT_UI1;
                vtPostData.parray = saPostData;
            }
        }
    }



    // Make the IE window visible.
    if (SUCCEEDED(hr))
    {
        hr = m_pBrowser->put_Visible(VARIANT_TRUE);
        LOG_MSG_IF_FAILED(L"put_Visible)", hr);
    }

    // Navigate to the URL.
    if (SUCCEEDED(hr))
    {
        hr = m_pBrowser->Navigate(bstrURL, &vtEmpty, &vtEmpty, &vtPostData, &vtHeader);
        LOG_MSG_IF_FAILED(L"Navigate", hr);
    }

    SysFreeString(bstrURL);

    VariantClear(&vtEmpty);
    VariantClear(&vtHeader);
    VariantClear(&vtPostData);

    return hr;
}