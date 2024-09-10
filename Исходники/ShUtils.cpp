/**
 * Create a default IExtractIcon component for an icon in the module's resource.
 */
HRESULT SHCreateModuleExtractIcon(int iIconIndex, REFIID riid, LPVOID* ppRetVal)
{
   ATLASSERT(iIconIndex>=0);
   ATLASSERT(ppRetVal!=NULL);
   ATLASSERT(*ppRetVal==NULL);
   WCHAR wszDllFilename[MAX_PATH] = { 0 };
   ::GetModuleFileNameW(_pModule->GetModuleInstance(), wszDllFilename, MAX_PATH);
   CComPtr<IDefaultExtractIconInit> spExIcon;
   HR( ::SHCreateDefaultExtractIcon(IID_PPV_ARGS(&spExIcon)) );
   HR( spExIcon->SetFlags(GIL_PERINSTANCE) );
   HR( spExIcon->SetNormalIcon(wszDllFilename, -iIconIndex) );
   return spExIcon->QueryInterface(riid, ppRetVal);
}