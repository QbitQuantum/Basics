STDMETHODIMP [!output CLASS_NAME]::GetPropValueName (LONG index, BSTR *pBstrValueName) {
	if ( pBstrValueName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the 2 lines below)
	WCHAR buffer [5] ; //----- This should be enough
	*pBstrValueName =::SysAllocString (_itow (index, buffer, 10)) ; //----- Show simply the numbers in the combo

	return (S_OK) ;
}