/***********************************************************************
 *           NdrDllUnregisterProxy [RPCRT4.@]
 */
HRESULT WINAPI NdrDllUnregisterProxy(HMODULE hDll,
                                    const ProxyFileInfo **pProxyFileList,
                                    const CLSID *pclsid)
{
  static const WCHAR clsidW[] = {'C','L','S','I','D','\\',0};
  static const WCHAR interfaceW[] = {'I','n','t','e','r','f','a','c','e','\\',0};
  WCHAR keyname[50];
  WCHAR clsid[39];

  TRACE("(%p,%p,%s)\n", hDll, pProxyFileList, debugstr_guid(pclsid));
  if (pclsid)
      format_clsid( clsid, pclsid );
  else if ((*pProxyFileList)->TableSize > 0)
      format_clsid( clsid,(*pProxyFileList)->pStubVtblList[0]->header.piid);
  else
      return E_NOINTERFACE;

  /* unregister interfaces */
  while (*pProxyFileList) {
    unsigned u;
    for (u=0; u<(*pProxyFileList)->TableSize; u++) {
      CInterfaceStubVtbl *proxy = (*pProxyFileList)->pStubVtblList[u];
      PCInterfaceName name = (*pProxyFileList)->pNamesArray[u];

      TRACE("unregistering %s %s\n", debugstr_a(name), debugstr_guid(proxy->header.piid));

      strcpyW( keyname, interfaceW );
      format_clsid( keyname + strlenW(keyname), proxy->header.piid );
      SHDeleteKeyW(HKEY_CLASSES_ROOT, keyname);
    }
    pProxyFileList++;
  }

  /* unregister clsid */
  strcpyW( keyname, clsidW );
  strcatW( keyname, clsid );
  SHDeleteKeyW(HKEY_CLASSES_ROOT, keyname);

  return S_OK;
}