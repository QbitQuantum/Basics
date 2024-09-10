HRESULT dhGetObjectEx(LPCOLESTR szPathName, LPCOLESTR szProgId, REFIID riid,
		         DWORD dwClsContext, LPVOID lpvReserved, void ** ppv)
{
	HRESULT hr;

	DH_ENTER(L"GetObjectEx");

	if ((!szProgId && !szPathName) || !riid || !ppv || lpvReserved) return DH_EXIT(E_INVALIDARG, szProgId);

	if (szPathName)
	{

		if (!szProgId)
		{
			hr = CoGetObject(szPathName, NULL, riid, ppv);
		}
		else
		{
			IPersistFile * ppf = NULL;

			hr = dhCreateObjectEx(szProgId, &IID_IPersistFile, dwClsContext, NULL, (void **) &ppf);

			if (SUCCEEDED(hr)) hr = ppf->lpVtbl->Load(ppf, szPathName, 0);
			if (SUCCEEDED(hr)) hr = ppf->lpVtbl->QueryInterface(ppf, riid, ppv);

			if (ppf) ppf->lpVtbl->Release(ppf);
		}
	}
	else
	{

		CLSID clsid;
		IUnknown * pUnk = NULL;

		if (L'{' == szProgId[0])
			hr = CLSIDFromString((LPOLESTR) szProgId, &clsid);
		else
			hr = CLSIDFromProgID(szProgId, &clsid);

		if (SUCCEEDED(hr)) hr = GetActiveObject(&clsid, NULL, &pUnk);
		if (SUCCEEDED(hr)) hr = pUnk->lpVtbl->QueryInterface(pUnk, riid, ppv);

		if (pUnk) pUnk->lpVtbl->Release(pUnk);
	}

	return DH_EXIT(hr, szProgId);
}