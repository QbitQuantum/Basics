STDAPI DllRegisterServer()
{
    if (!IsWindowsVistaOrGreater())
        return E_FAIL;

    return DllRegisterServer(true);
}