HRESULT CSimpleDataObjectImpl::SetClipboard()
{
	RETURNIFFAILED(OleSetClipboard(this));
	RETURNIFFAILED(OleFlushClipboard());
	return S_OK;
}