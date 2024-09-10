STDAPI
DllUnregisterServer(void)
{
    SHDeleteKeyW(HKEY_CLASSES_ROOT, szNetConnectClass);
    SHDeleteKeyW(HKEY_LOCAL_MACHINE, szNamespaceKey);
    return S_OK;
}