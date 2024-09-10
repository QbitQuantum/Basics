HRESULT OLEAUTPS_DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
  return NdrDllGetClassObject(rclsid, riid, ppv, OLEAUT32_ProxyFileList,
                              &CLSID_PSDispatch, &PSFactoryBuffer);
}