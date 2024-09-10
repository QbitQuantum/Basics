HRESULT MakeSubStorage(LPSTORAGE pIRootStorage, 
						LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						bool &fNew, bool fDirect, CLSID clsID)
{       
LPSTORAGE pIStorage;
HRESULT hr;                                                     

DWORD dw = 0;

DWORD dwMode =	STGM_READWRITE | 
				STGM_SHARE_EXCLUSIVE ;	

	if (fDirect) dwMode = dwMode | STGM_DIRECT;
	else dwMode = dwMode | STGM_TRANSACTED;

	if (NULL == pIRootStorage) 	                   
		return ResultFromScode(STG_E_INVALIDPOINTER);

	USES_CONVERSION;
	hr = pIRootStorage -> OpenStorage (	A2OLE(strStorName), 
										NULL, dwMode, NULL,
										0, &pIStorage);
	if (FAILED(hr)) {
		if (STG_E_FILENOTFOUND == GetScode(hr)) {
			hr = pIRootStorage -> CreateStorage (	A2OLE(strStorName), 
													dwMode, 0, 0, &pIStorage);
			if (SUCCEEDED(hr)) {
				hr = WriteClassStg (pIStorage, clsID);
				fNew = true;
			}
			else {
				*ppISubStorage = NULL;
				return hr;
			}
		}
		else {
			*ppISubStorage = NULL;
			return hr;
		}
	}
						
	hr = TestclsID (pIStorage, clsID);
	if (FAILED(hr)) { pIStorage -> Release(); return hr; }
	
	*ppISubStorage = pIStorage;
	
return NOERROR;
} 