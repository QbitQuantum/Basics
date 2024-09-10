HRESULT CGeometricSchemeHandler::OnSourceOpen(_In_ IMFAsyncResult *pResult)
{
    ComPtr<IUnknown> spState = pResult->GetStateNoAddRef();
    if (!spState)
    {
        return MF_E_UNEXPECTED;
    }
    ComPtr<IMFAsyncResult> spSavedResult;
    HRESULT hr = S_OK;

    hr = spState.As(&spSavedResult);
    if (FAILED(hr))
    {
        return hr;
    }

    ComPtr<IUnknown> spunkSource;
    ComPtr<IMFMediaSource> spSource;
    hr = spSavedResult->GetObject(&spunkSource);

    if (SUCCEEDED(hr))
    {
        hr = spunkSource.As(&spSource);
        if (SUCCEEDED(hr))
        {
            CGeometricMediaSource *pSource = static_cast<CGeometricMediaSource *>(spSource.Get());
            hr = pSource->EndOpen(pResult);
        }
    }

    spSavedResult->SetStatus(hr);    
    hr = MFInvokeCallback(spSavedResult.Get());

    return hr;
}