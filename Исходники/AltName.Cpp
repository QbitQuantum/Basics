HRESULT
CCertEncodeAltName::_SetErrorInfo(
    IN HRESULT hrError,
    IN WCHAR const *pwszDescription)
{
    assert(FAILED(hrError) || S_OK == hrError || S_FALSE == hrError);
    if (FAILED(hrError))
    {
	HRESULT hr;

	hr = ceDispatchSetErrorInfo(
			    hrError,
			    pwszDescription,
			    wszCLASS_CERTENCODEALTNAME,
			    &IID_ICertEncodeAltName);
	assert(hr == hrError);
    }
    return(hrError);
}