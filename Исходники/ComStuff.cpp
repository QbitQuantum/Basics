STDAPI DllRegisterServer()
{
    DllUnregisterServer();

    // Register CLSID_NET_PROFILER object.
    if(FAILED(RegisterServer(CLSID_NET_PROFILER, TEXT("Hook Net"))))
        return SELFREG_E_CLASS;

    return S_OK;
}