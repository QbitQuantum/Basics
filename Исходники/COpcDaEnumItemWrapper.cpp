// Next
HRESULT COpcDaEnumItemWrapper::Next(
	ULONG               celt,
	OPCITEMATTRIBUTES** ppItemArray,
	ULONG*              pceltFetched
)
{
	COpcLock cLock(*this);

	// check inner server.
	if (m_ipUnknown == NULL)
	{
		return E_FAIL;
	}

	// fetch required interface.
	IEnumOPCItemAttributes* ipInterface = NULL;

	if (FAILED(m_ipUnknown->QueryInterface(IID_IEnumOPCItemAttributes, (void**)&ipInterface)))
	{
		return E_NOTIMPL;
	}

	// invoke method.
	HRESULT hResult = ipInterface->Next(
		celt,
		ppItemArray,
		pceltFetched
	);

	// release interface.
	ipInterface->Release();

	if (hResult == S_OK)
	{
		if (celt > 0 && (*ppItemArray == NULL || *pceltFetched == 0))
		{
			return S_FALSE;
		}
	}

	return hResult;
}