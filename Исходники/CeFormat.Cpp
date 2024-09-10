HRESULT 
ceFormatCertsrvStringArray(
    IN BOOL    fURL,
    IN LPCWSTR pwszServerName_p1_2,
    IN LPCWSTR pwszSanitizedName_p3_7, 
    IN DWORD   iCert_p4,
    IN LPCWSTR pwszDomainDN_p5,
    IN LPCWSTR pwszConfigDN_p6, 
    IN DWORD   iCRL_p8,
    IN BOOL    fDeltaCRL_p9,
    IN BOOL    fDSAttrib_p10_11,
    IN DWORD   cStrings,
    IN LPCWSTR *apwszStringsIn,
    OUT LPWSTR *apwszStringsOut)
{
    HRESULT hr = S_OK;
    LPCWSTR apwszInsertionArray[100];  // 100 'cause this is the max number of insertion numbers allowed by FormatMessage
    LPWSTR    pwszCurrent = NULL;
    BSTR      strShortMachineName = NULL;
    DWORD     i;
    WCHAR *pwszSanitizedDSName = NULL;
    WCHAR wszCertSuffix[cwcFILENAMESUFFIXMAX];
    WCHAR wszCRLSuffix[cwcFILENAMESUFFIXMAX];
    WCHAR wszDeltaCRLSuffix[cwcFILENAMESUFFIXMAX];
    WCHAR const *pwszT;


    ZeroMemory(apwszStringsOut, cStrings * sizeof(apwszStringsOut[0]));
    ZeroMemory(apwszInsertionArray, sizeof(apwszInsertionArray));

    // Format the template into a real name

    // Initialize the insertion string array.
    // Machine DNS name (%1)    

    assert(L'1' == wszFCSAPARM_SERVERDNSNAME[1]);
    apwszInsertionArray[1 - 1] = pwszServerName_p1_2;

    // Short Machine Name (%2)

    assert(L'2' == wszFCSAPARM_SERVERSHORTNAME[1]);
    strShortMachineName = SysAllocString(pwszServerName_p1_2);
    if (strShortMachineName == NULL)
    {
        hr = E_OUTOFMEMORY;
        _JumpIfError(hr, error, "SysAllocString");
    }

    pwszCurrent = wcschr(strShortMachineName, L'.');
    if(pwszCurrent)
    {
        *pwszCurrent = 0;
    }
    apwszInsertionArray[2 - 1] = strShortMachineName;

    // sanitized name (%3)

    assert(L'3' == wszFCSAPARM_SANITIZEDCANAME[1]);
    apwszInsertionArray[3 - 1] = pwszSanitizedName_p3_7;  

    // Cert filename suffix (%4)

    assert(L'4' == wszFCSAPARM_CERTFILENAMESUFFIX[1]);
    wszCertSuffix[0] = L'\0';
    if (0 != iCert_p4)
    {
        wsprintf(wszCertSuffix, L"(%u)", iCert_p4);
    }
    apwszInsertionArray[4 - 1] = wszCertSuffix;  

    assert(L'5' == wszFCSAPARM_DOMAINDN[1]);
    apwszInsertionArray[5 - 1] = pwszDomainDN_p5;

    assert(L'6' == wszFCSAPARM_CONFIGDN[1]);
    apwszInsertionArray[6 - 1] = pwszConfigDN_p6;

    // Don't pass pwszSanitizedName_p3_7 to SysAllocStringLen with the extended
    // length to avoid faulting past end of pwszSanitizedName_p3_7.

    assert(L'7' == wszFCSAPARM_SANITIZEDCANAMEHASH[1]);
    hr = ceSanitizedNameToDSName(pwszSanitizedName_p3_7, &pwszSanitizedDSName);
    _JumpIfError(hr, error, "ceSanitizedNameToDSName");

    apwszInsertionArray[7 - 1] = pwszSanitizedDSName;

    // CRL filename suffix (%8)

    assert(L'8' == wszFCSAPARM_CRLFILENAMESUFFIX[1]);
    wszCRLSuffix[0] = L'\0';
    if (0 != iCRL_p8)
    {
        wsprintf(wszCRLSuffix, L"(%u)", iCRL_p8);
    }
    apwszInsertionArray[8 - 1] = wszCRLSuffix;  

    assert(L'9' == wszFCSAPARM_CRLDELTAFILENAMESUFFIX[1]);
    wszDeltaCRLSuffix[0] = L'\0';
    if (fDeltaCRL_p9)
    {
        wcscpy(wszDeltaCRLSuffix, L"+");
    }
    apwszInsertionArray[9 - 1] = wszDeltaCRLSuffix;  

    assert(L'1' == wszFCSAPARM_DSCRLATTRIBUTE[1]);
    assert(L'0' == wszFCSAPARM_DSCRLATTRIBUTE[2]);
    pwszT = L"";
    if (fDSAttrib_p10_11)
    {
	pwszT = fDeltaCRL_p9?
		    wszDSSEARCHDELTACRLATTRIBUTE :
		    wszDSSEARCHBASECRLATTRIBUTE;
    }
    apwszInsertionArray[10 - 1] = pwszT;  

    assert(L'1' == wszFCSAPARM_DSCACERTATTRIBUTE[1]);
    assert(L'1' == wszFCSAPARM_DSCACERTATTRIBUTE[2]);
    pwszT = L"";
    if (fDSAttrib_p10_11)
    {
	pwszT = wszDSSEARCHCACERTATTRIBUTE;
    }
    apwszInsertionArray[11 - 1] = pwszT;  

    for (i = 0; i < cStrings; i++)
    {
        if (0 == FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			    FORMAT_MESSAGE_FROM_STRING |
			    FORMAT_MESSAGE_ARGUMENT_ARRAY,
			(VOID *) apwszStringsIn[i],
			0,              // dwMessageID
			0,              // dwLanguageID
			(LPWSTR) &apwszStringsOut[i], 
			(DWORD)wcslen(apwszStringsIn[i]),
			(va_list *) apwszInsertionArray))
        {
            hr = ceHLastError();
	    _JumpError(hr, error, "FormatMessage");
        }
	if (fURL)
	{
	    WCHAR *pwsz;
	    
	    hr = ceInternetCanonicalizeUrl(apwszStringsOut[i], &pwsz);
	    _JumpIfError(hr, error, "ceInternetCanonicalizeUrl");

	    LocalFree(apwszStringsOut[i]);
	    apwszStringsOut[i] = pwsz;
	}
    }

error:
    if (S_OK != hr)
    {
	for (i = 0; i < cStrings; i++)
	{
	    if (NULL != apwszStringsOut[i])
	    {
		LocalFree(apwszStringsOut[i]);
		apwszStringsOut[i] = NULL;
	    }
	}
    }
    if(strShortMachineName)
    {
        SysFreeString(strShortMachineName);
    }
    if (NULL != pwszSanitizedDSName)
    {
        LocalFree(pwszSanitizedDSName);
    }
    return (hr);
}