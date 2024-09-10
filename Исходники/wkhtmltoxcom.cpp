STDAPI DllUnregisterServerLocal(void)
{
    // registers object, typelib and all interfaces in typelib
	AtlSetPerUserRegistration(true);
    HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}