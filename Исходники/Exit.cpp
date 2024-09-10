HRESULT
CCertExitSample::_WriteCertToFile(
    IN ICertServerExit *pServer,
    IN BYTE const *pbCert,
    IN DWORD cbCert)
{
    HRESULT hr;
    BSTR strCertFile = NULL;
    DWORD cbWritten;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    WCHAR wszDir[MAX_PATH];
    WCHAR *pwszPath = NULL;
    WCHAR wszFile[cwcDWORDSPRINTF+5]; //format "requestid.cer"
    VARIANT varRequestID;

    VariantInit(&varRequestID);

    // Old functionality asked requester to pass in a CertFile attribute with
    // the output request file name. After the security review we decided
    // to not allow file name from user but to build it at server. Still, we 
    // don't want to start publishing all certificates, so we'll maintain the
    // CertFile property; if present, we'll just ignore its content, if not 
    // present we won't publish.
    hr = exitGetRequestAttribute(pServer, wszPROPEXITCERTFILE, &strCertFile);
    if (S_OK != hr)
    {
	DBGPRINT((
	    fDebug,
	    "Exit:exitGetRequestAttribute(%ws): %x%hs\n",
	    wszPROPEXITCERTFILE,
	    hr,
	    CERTSRV_E_PROPERTY_EMPTY == hr? " EMPTY VALUE" : ""));
	if (CERTSRV_E_PROPERTY_EMPTY == hr)
	{
	    hr = S_OK;
	}
	goto error;
    }

    // build file name as "requestid.cer"

    hr = exitGetProperty(
        pServer,
        TRUE,  // fRequest,
        wszPROPREQUESTREQUESTID,
        PROPTYPE_LONG,
        &varRequestID);
    _JumpIfErrorStr(hr, error, "Exit:exitGetProperty", wszPROPREQUESTREQUESTID);

    wsprintf(wszFile, L"%d.cer", V_I4(&varRequestID));
    
    hr = _ExpandEnvironmentVariables(
		    L"%SystemRoot%\\System32\\" wszCERTENROLLSHAREPATH L"\\",
		    wszDir,
		    ARRAYSIZE(wszDir));
    _JumpIfError(hr, error, "_ExpandEnvironmentVariables");

    hr = ceBuildPathAndExt(wszDir, wszFile, NULL, &pwszPath);
    _JumpIfError(hr, error, "ceBuildPathAndExt");

    // open file & write binary cert out.

    hFile = CreateFile(
		    pwszPath,
		    GENERIC_WRITE,
		    0,			// dwShareMode
		    NULL,		// lpSecurityAttributes
		    CREATE_NEW,
		    FILE_ATTRIBUTE_NORMAL,
		    NULL);		// hTemplateFile
    if (INVALID_HANDLE_VALUE == hFile)
    {
	hr = ceHLastError();
	_JumpErrorStr(hr, error, "Exit:CreateFile", pwszPath);
    }
    if (!WriteFile(hFile, pbCert, cbCert, &cbWritten, NULL))
    {
	hr = ceHLastError();
	_JumpErrorStr(hr, error, "Exit:WriteFile", pwszPath);
    }
    if (cbWritten != cbCert)
    {
	hr = STG_E_WRITEFAULT;
	DBGPRINT((
	    fDebug,
	    "Exit:WriteFile(%ws): attempted %x, actual %x bytes: %x\n",
	    pwszPath,
	    cbCert,
	    cbWritten,
	    hr));
	goto error;
    }

error:

    if (INVALID_HANDLE_VALUE != hFile)
    {
	CloseHandle(hFile);
    }
    if (NULL != pwszPath)
    {
	LocalFree(pwszPath);
    }
    if (NULL != strCertFile)
    {
	SysFreeString(strCertFile);
    }
    return(hr);
}