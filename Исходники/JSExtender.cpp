HRESULT CJSProxyObj::QueryInterface(REFIID riid, void **ppvObject)
{
	ATLASSERT(ppvObject != NULL);
	if (ppvObject == nullptr)
		return E_POINTER;
	*ppvObject = nullptr;

	if (InlineIsEqualGUID(riid, IID_NULL))
		return E_NOINTERFACE;

	if (InlineIsEqualUnknown(riid) ||
		InlineIsEqualGUID(riid, __uuidof(IDispatch)) ||
		InlineIsEqualGUID(riid, m_EventIID))
	{
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	else
		return E_NOINTERFACE;
}