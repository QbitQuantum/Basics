void CMFCBindCntrItem::LoadFromMoniker(LPUNKNOWN pUnk, OLECHAR* szwName)
{
	HRESULT hr;
	// Ask the system for a URL Moniker
	IMoniker* pIMoniker;
	hr = CreateURLMoniker(NULL, (LPWSTR)szwName, &pIMoniker);
	if ( SUCCEEDED(hr) )
	{
		// Get the IPersistMoniker interface
		IPersistMoniker* pPMk;
		hr = pUnk->QueryInterface(
								IID_IPersistMoniker,
								(void **)&pPMk);
		if ( SUCCEEDED(hr) )
		{
				// note: do not register our BSC when calling IPM::Load directly
			IBindCtx *pBCtx;
			hr = CreateBindCtx(0, &pBCtx);
			if ( SUCCEEDED(hr) )
			{
				// Call Load on the IPersistMoniker
				hr = pPMk->Load(FALSE, pIMoniker, pBCtx, STGM_READ);
					pBCtx->Release();
			}
			pPMk->Release();
		}
		pIMoniker->Release( );
	}
}