HRESULT __stdcall Sorter::Invoke( DISPID dispid, REFIID riid, LCID lcid,
								   WORD wFlags, DISPPARAMS * params, VARIANT * result, 
								   EXCEPINFO * pExceptInfo, UINT * puArgErr
							     )
{
	// check that the client is requesting the default interface (IAdd)
	if( !IsEqualIID( riid, IID_NULL ) )
	{	return DISP_E_UNKNOWNINTERFACE; }

	if( !Sorter::pITypeInfo )
	{
		HRESULT hr = Sorter::loadITypeInfo();
		if( !SUCCEEDED(hr) ) return hr;
	}

	return DispInvoke( this, Sorter::pITypeInfo, dispid, wFlags, params, result, pExceptInfo, puArgErr );
}