char * CCoordTransService::CoordTransToStringEx (
	double dX, double dY, bool isX, char *pBuffer, int iLen)
{
	if (m_fIsInitialized) {
		try {
		CComBSTR bstr;
		CCSPoint pt (dX, dY);

			if (isX) {
				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&pt, &bstr, NULL, NULL));
			} else {
				THROW_FAILED_HRESULT(m_CTF -> ToStrings (&pt, NULL, &bstr, NULL));
			}

			USES_CONVERSION;
			iLen = min(bstr.Length(), iLen-1);
			strncpy (pBuffer, OLE2A(bstr), iLen);
			pBuffer[iLen] = '\0';
			return pBuffer;

		} catch (_com_error &e) {
			ShowError (_COM_ERROR(e), IDS_CSSERRORCAPTION, g_cbCoordTransToStringEx);
			return NULL;
		}
	
	} 
	ShowError (TRIAS02_E_CSSNOTINITIALIZED, IDS_CSSERRORCAPTION, g_cbCoordTransToStringEx);
	return NULL;
}