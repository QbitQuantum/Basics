FARINTERNAL UtContentsStmTo10NativeStm
	(LPSTORAGE pstg, REFCLSID rclsid, BOOL fDeleteSrcStm, UINT FAR* puiStatus)
{
	CLIPFORMAT	cf;
	LPOLESTR	lpszUserType = NULL;
	HRESULT		error;
	LPSTREAM	pstmSrc = NULL;
	LPSTREAM	pstmDst = NULL;
			
	*puiStatus = NULL;
	
	if (error = ReadFmtUserTypeStg(pstg, &cf, &lpszUserType))
		return error;
		
	
	if (! ((cf == CF_DIB  && rclsid == CLSID_PBrush)
			|| (cf == CF_METAFILEPICT && rclsid == CLSID_MSDraw))) {
		error = ResultFromScode(DV_E_CLIPFORMAT);
		goto errRtn;
	}
			
	if (error = pstg->OpenStream(OLE_CONTENTS_STREAM, NULL,
						(STGM_READ|STGM_SHARE_EXCLUSIVE),
						0, &pstmSrc)) {
		*puiStatus |= CONVERT_NOSOURCE;	

		// check whether OLE10_NATIVE_STREAM exists
		if (pstg->OpenStream(OLE10_NATIVE_STREAM, NULL,
				(STGM_READ|STGM_SHARE_EXCLUSIVE), 0, &pstmDst))
			*puiStatus |= CONVERT_NODESTINATION;
		else {
			pstmDst->Release();
			pstmDst = NULL;
		}
		
		goto errRtn;
	}
	
	if (error = OpenOrCreateStream(pstg, OLE10_NATIVE_STREAM, &pstmDst)) {
		*puiStatus |= CONVERT_NODESTINATION;						
		goto errRtn;
	}
	
	if (cf == CF_METAFILEPICT)
		error = UtPlaceableMFStmToMSDrawNativeStm(pstmSrc, pstmDst);
	else
		error = UtDIBFileStmToPBrushNativeStm(pstmSrc, pstmDst);
	
errRtn:
	if (pstmDst)
		pstmDst->Release();
			
	if (pstmSrc)
		pstmSrc->Release();
	
	if (error == NOERROR) {
		LPOLESTR lpszProgId = NULL;
		ProgIDFromCLSID(rclsid, &lpszProgId);
		
		error = WriteFmtUserTypeStg(pstg,
						RegisterClipboardFormat(lpszProgId),
						lpszUserType);

		if (lpszProgId)
			delete lpszProgId;
	}
	
	if (error == NOERROR) {
		if (fDeleteSrcStm)				
			pstg->DestroyElement(OLE_CONTENTS_STREAM);
	} else {
		pstg->DestroyElement(OLE10_NATIVE_STREAM);	
	}	
	
	if (lpszUserType)
		delete lpszUserType;
	
	return error;
}