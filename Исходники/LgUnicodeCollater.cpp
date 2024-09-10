/*----------------------------------------------------------------------------------------------
	Do a direct string comparison.
----------------------------------------------------------------------------------------------*/
STDMETHODIMP LgUnicodeCollater::Compare(BSTR bstrValue1, BSTR bstrValue2,
	LgCollatingOptions colopt, int * pnVal)
{
	BEGIN_COM_METHOD
	ChkComBstrArg(bstrValue1);
	ChkComBstrArg(bstrValue2);
	ChkComOutPtr(pnVal);

	HRESULT hr;

	int cchw1;
	int cchw2;

	IgnoreHr(hr = SortKeyRgch(bstrValue1, BstrLen(bstrValue1), colopt, 0, NULL, &cchw1));
	if (FAILED(hr))
		return hr;
	IgnoreHr(hr = SortKeyRgch(bstrValue2, BstrLen(bstrValue2), colopt, 0, NULL, &cchw2));
	if (FAILED(hr))
		return hr;

	OLECHAR * pchKey1 = (OLECHAR *) _alloca(cchw1 * isizeof(OLECHAR));
	OLECHAR * pchKey2 = (OLECHAR *) _alloca(cchw2 * isizeof(OLECHAR));

	IgnoreHr(hr = SortKeyRgch(bstrValue1, BstrLen(bstrValue1), colopt, cchw1, pchKey1, &cchw1));
	if (FAILED(hr))
		return hr;
	IgnoreHr(hr = SortKeyRgch(bstrValue2, BstrLen(bstrValue2), colopt, cchw2, pchKey2, &cchw2));
	if (FAILED(hr))
		return hr;
	int nVal = u_strncmp(pchKey1, pchKey2, min(cchw1, cchw2));
	if (!nVal)
	{
		// equal as far as length of shortest key
		if (BstrLen(bstrValue1) < BstrLen(bstrValue2))
			nVal = -1;
		else if (BstrLen(bstrValue1) > BstrLen(bstrValue2))
			nVal = 1;
	}
	*pnVal = nVal;
	END_COM_METHOD(g_fact, IID_ILgCollatingEngine);
}