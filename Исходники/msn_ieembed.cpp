void IEEmbed::navigate(NETLIBHTTPREQUEST *nlhr)
{
	WCHAR *szUrl = mir_a2u(nlhr->szUrl);
	BSTR bstrHeaders;
    LPSAFEARRAY psa;
	LPSTR pPostData;
    VARIANT vPostData = {0}, vHeaders = {0};

	bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
    V_VT(&vHeaders) = VT_BSTR;
    V_BSTR(&vHeaders) = bstrHeaders;
    VariantInit(&vPostData);
    psa = SafeArrayCreateVector(VT_UI1, 0, nlhr->dataLength);
    SafeArrayAccessData(psa, (LPVOID*)&pPostData);
	memcpy(pPostData, nlhr->pData, nlhr->dataLength);
    SafeArrayUnaccessData(psa);
    V_VT(&vPostData) = VT_ARRAY | VT_UI1;
    V_ARRAY(&vPostData) = psa;
	pWebBrowser->Navigate(szUrl, NULL, NULL, &vPostData, &vHeaders);
	SysFreeString(bstrHeaders);
	VariantClear(&vPostData);
	mir_free(szUrl);
}