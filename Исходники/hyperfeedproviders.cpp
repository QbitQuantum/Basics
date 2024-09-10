HRESULT CExeModule::UnregisterServer(BOOL bUnRegTypeLib, const CLSID* pCLSID)
{
	CComPtr<ICatRegister> spcr;
	HRESULT hr = spcr.CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC);
	if(SUCCEEDED(hr) && spcr!=NULL)
	{
			CATID catid = CATID_PriceProviders;
			CComBSTR bs;
			ProgIDFromCLSID(CLSID_ProviderInfo, &bs);
			spcr->UnRegisterClassImplCategories( CLSID_ProviderInfo, 1, &catid);
	}
	return CComModule::UnregisterServer(bUnRegTypeLib, pCLSID);
}