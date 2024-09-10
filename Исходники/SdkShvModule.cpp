/// Registers the SDK SHV with the NAP Server.
HRESULT CSdkShvModule::RegisterSdkShv() throw()
{
    HRESULT hr = S_OK;

    /// Pointer to the INapServerManagement interface
    CComPtr<INapServerManagement> pSHVMgmt = NULL;
    /// Registration Information
    NapComponentRegistrationInfo shvInfo;

    ZeroMemory (&shvInfo, sizeof(shvInfo));
    hr = pSHVMgmt.CoCreateInstance(CLSID_NapServerManagement,
                           NULL,
                           CLSCTX_INPROC_SERVER);
    if (FAILED(hr))
    {
        DebugPrintfW(L"RegisterSdkShv: CoCreateInstance Failed with %#x",hr);
        goto Cleanup;
    }

    hr = FillShvComponentRegistrationInfo(&shvInfo);
    if(FAILED(hr))
    {
        DebugPrintfW(L"RegisterSdkShv:: FillShvComponentRegistrationInfo Failed with %#x",hr);
        goto Cleanup;
    }

     hr = pSHVMgmt->RegisterSystemHealthValidator(&shvInfo,(CLSID *)&__uuidof(CSampleShv));
       if (FAILED(hr))
    {
        DebugPrintfW(L"RegisterSdkShv:: RegisterSystemHealthValidator failed %#x", hr); 
        goto Cleanup;
    }

    Cleanup:
    FreeComponentRegistration(&shvInfo);
    return hr;
}