BOOL COleObjectFactory::VerifyLicenseKey(BSTR bstrKey)
{
	// May be overridden by subclass

	BOOL bLicensed = FALSE;
	BSTR bstr = NULL;

	if ((bstrKey != NULL) && GetLicenseKey(0, &bstr))
	{
		ASSERT(bstr != NULL);

		// if length and content match, it's good!

		UINT cch = SysStringByteLen(bstr);
		if ((cch == SysStringByteLen(bstrKey)) &&
			(memcmp(bstr, bstrKey, cch) == 0))
		{
			bLicensed = TRUE;
		}

		SysFreeString(bstr);
	}

	return bLicensed;
}