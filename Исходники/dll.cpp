STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib

    HRESULT hr = _Module.RegisterServer();

    // Notify WMP that plugin has been added

    WMPNotifyPluginAddRemove();

    return hr;
}