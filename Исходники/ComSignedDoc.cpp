STDMETHODIMP CComSignedDoc::createDataFile(BSTR szFileName, BSTR szContentType, BSTR szMimeType, long nSize, VARIANT baDigest, long nDigLen, BSTR szDigType, BSTR szCharset, IComDataFile *pStoreTo)
{
	SAFEARRAY* pArr;
	byte HUGEP* pData;
	USES_CONVERSION;
	
	if(!m_pSignedDoc)
		return S_OK;
	// analyze digest array
	if ((V_VT(&baDigest) != VT_EMPTY)
		  && (V_VT(&baDigest) == VT_ARRAY)) {
		pArr = V_ARRAY(&baDigest);
		if ((SafeArrayGetDim(pArr) <= 0)
			|| (SafeArrayAccessData(pArr, (void HUGEP**)&pData) != S_OK))
	  pData = NULL;
	} else {
		pData = NULL;
	}


    DataFile* pDataFile = NULL;

	char *p1 = GetBSTR(szFileName);
	char *p2 = GetBSTR(szContentType);
	char *p3 = GetBSTR(szMimeType);
	char *p4 = GetBSTR(szDigType);
	char *p5 = GetBSTR(szCharset);

	::DataFile_new(&pDataFile, m_pSignedDoc, NULL, 
					p1, p2, p3, nSize, pData, nDigLen, p4, p5);

	if (pData)
	    SafeArrayUnaccessData(pArr);

	if (pDataFile != (DataFile*)0) {
		CComDataFile* pComDataFile =  (CComDataFile*)pStoreTo;
		pComDataFile->shiftStructPointer(pDataFile);
		pComDataFile->setSignedDoc(m_pSignedDoc); 
	}
	return S_OK;
}