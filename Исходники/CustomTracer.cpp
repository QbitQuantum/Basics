HRESULT COMCALL CustomTracer::TestMethod(BSTR bstrInput, BSTR* pbstrOutput)
{
	LOG_ENTRY(TXT("CustomTracer::TestMethod()"));

	HRESULT hr = S_OK;

	try
	{
		// Check output parameters.
		if (pbstrOutput == nullptr)
			throw WCL::ComException(E_POINTER, TXT("pbstrOutput is NULL"));

		// Reverse the input string.
		*pbstrOutput = _wcsrev(::SysAllocString(BSTR2W(bstrInput)));
	}
	COM_CATCH(hr)

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr).c_str());

	return hr;
}