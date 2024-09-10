HRESULT CpiReadPropertyList(
	LPWSTR* ppwzData,
	CPI_PROPERTY** ppPropList
	)
{
	HRESULT hr = S_OK;

	CPI_PROPERTY* pItm = NULL;
	LPWSTR pwzName = NULL;

	// clear list if it already contains items
	if (*ppPropList)
		CpiFreePropertyList(*ppPropList);
	*ppPropList = NULL;

	// read property count
	int iPropCnt = 0;
	hr = WcaReadIntegerFromCaData(ppwzData, &iPropCnt);
	ExitOnFailure(hr, "Failed to read property count");

	for (int i = 0; i < iPropCnt; i++)
	{
		// allocate new element
		pItm = (CPI_PROPERTY*)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CPI_PROPERTY));
		if (!pItm)
			ExitFunction1(hr = E_OUTOFMEMORY);

		// Name
		hr = WcaReadStringFromCaData(ppwzData, &pwzName);
		ExitOnFailure(hr, "Failed to read name");
		StringCchCopyW(pItm->wzName, countof(pItm->wzName), pwzName);

		// Value
		hr = WcaReadStringFromCaData(ppwzData, &pItm->pwzValue);
		ExitOnFailure(hr, "Failed to read property value");

		// add to list
		if (*ppPropList)
			pItm->pNext = *ppPropList;
		*ppPropList = pItm;
		pItm = NULL;
	}

	hr = S_OK;

LExit:
	// clean up
	ReleaseStr(pwzName);

	if (pItm)
		CpiFreePropertyList(pItm);

	return hr;
}