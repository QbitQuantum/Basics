STDMETHODIMP CompositeOverlayImpl<B>::put_Overlays(LPSAFEARRAY newVal)
{
	ClearAndDestroy();
	long lb = 0;
	long ub = 0;
	if( !(newVal->fFeatures & FADF_DISPATCH) )
		return E_INVALIDARG;

	HRESULT hr = ::SafeArrayGetUBound(newVal, 1, &ub);
	hr = ::SafeArrayGetLBound(newVal, 1, &lb);

	IDispatch *pDisp;
	IOverlay *pOverlay;
	long indices[1];
	for (int i=lb; i<=ub; i++)
	{
		indices[0] = i;
		pDisp = 0;
		::SafeArrayGetElement(newVal, indices, &pDisp);
		if (pDisp)
		{
			if (SUCCEEDED(pDisp->QueryInterface(__uuidof(IOverlay), (void**)&pOverlay)))
			{
				AtlTrace("Added overlay to composite\n");
				Add(pOverlay);
				pOverlay->Release();
			}
			pDisp->Release();
		}
	}

	return S_OK;
}