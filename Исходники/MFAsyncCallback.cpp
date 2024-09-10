HRESULT MFAsyncCallback::QueryInterface(REFIID riid, void** ppv)
{
	static const QITAB qit[] =
    {
        QITABENT(MFAsyncCallback, IMFAsyncCallback),
        { 0 }
    };
	return QISearch(this, qit, riid, ppv);
}