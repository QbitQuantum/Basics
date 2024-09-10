HRESULT MiniPlayer::CoCreateInstanceAx(LPCTSTR ax, REFCLSID rclsid, IUnknown *punkOuter, REFIID riid, LPVOID *ppv)
{
	HINSTANCE hInst = _loadedLibs[ax];
	if(hInst == NULL)
		hInst = CoLoadLibrary(const_cast<LPOLESTR>(ax), 0);
	if(!hInst) return -1;
	_loadedLibs[ax] = hInst;
	LPFNGETCLASSOBJECT pfnDllGetObjectClass = reinterpret_cast<LPFNGETCLASSOBJECT>(GetProcAddress(hInst, "DllGetClassObject"));
	if(!pfnDllGetObjectClass) return -1;

	IClassFactory *pClsFactory = NULL;
	HRESULT hr = pfnDllGetObjectClass(rclsid, IID_IClassFactory, (void **)&pClsFactory);
	IF_CHK(hr, "Unable to get Class Factory.");

	return pClsFactory->CreateInstance(punkOuter, riid, ppv);

Cleanup:
	if(hInst) CoFreeLibrary(hInst);
	return hr;
}