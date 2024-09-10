STDMETHODIMP CoFoldersMonitor::Invoke(DISPID dispidMember, REFIID riid,
									  LCID lcid, WORD wFlags, 
									  DISPPARAMS* pdispparams, VARIANT* pvarResult,
									  EXCEPINFO* pexcepinfo, UINT* puArgErr)
{
	HRESULT hr = DispInvoke(static_cast<IDispatch*>(this), 
		m_typeInfo,
		dispidMember,
		wFlags,
		pdispparams,
		pvarResult,
		pexcepinfo,
		puArgErr);

	_ASSERT(SUCCEEDED(hr));

	return hr;
}