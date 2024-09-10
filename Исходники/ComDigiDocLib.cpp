STDMETHODIMP CComDigiDocLib::longnum2hex(BSTR longNumber, BSTR* pVal)
{
	char *psBuf;
	int   iLen;
	int   iErr;

	BIGNUM *bn=NULL;
	char* str;

	_bstr_t bsTemp(longNumber);
	char *inputt = bsTemp;

	BN_dec2bn(&bn, inputt);
	str = BN_bn2hex(bn);
	BN_free(bn);
	
	iErr = ::oem2unicode(str, &psBuf,&iLen);
	OPENSSL_free(str);

	*pVal = SysAllocString(W2OLE((wchar_t *)psBuf));
	return S_OK;
}