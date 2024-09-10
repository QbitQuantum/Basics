STDMETHODIMP CTestCases::Terminate(VARIANT_BOOL* pbResult)
{
	TRACE("CTestCases::Terminate\n");

	//Delegate to the derived class...
	VARIANT_BOOL bResult = (VARIANT_BOOL)Terminate();
	
	if(pbResult)
		*pbResult = bResult ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}