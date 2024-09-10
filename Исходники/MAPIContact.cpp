bool MAPIContact::SetNotes(const String &szNotes, bool bRTF) {
#ifdef _WIN32_WCE
	return SetPropertyString(PR_BODY, szNotes);
#else
	if(!Contact() || IsNull(szNotes)) 
		return false;
	ULONG nLen = (ULONG)szNotes.GetLength();

	HRESULT hr = E_FAIL;
	LPSTREAM pStream = NULL;
	if(bRTF) {
		if(Contact()->OpenProperty(PR_RTF_COMPRESSED, &IID_IStream, STGM_CREATE | STGM_WRITE, 
								MAPI_MODIFY | MAPI_CREATE, (LPUNKNOWN*)&pStream) == S_OK) {
			IStream *pUncompressed;
			if(WrapCompressedRTFStream(pStream,MAPI_MODIFY, &pUncompressed) == S_OK) {
				hr = pUncompressed->Write(szNotes, nLen*sizeof(TCHAR), NULL);
				if(pUncompressed->Commit(STGC_DEFAULT)==S_OK) 
					pStream->Commit(STGC_DEFAULT);
				RELEASE(pUncompressed);
			}
		}
	} else {
		if(Contact()->OpenProperty(PR_BODY, &IID_IStream, 0, MAPI_MODIFY | MAPI_CREATE, 
																(LPUNKNOWN*)&pStream) == S_OK) 
			hr = pStream->Write(szNotes, (nLen+1)*sizeof(TCHAR), NULL);
	}
	RELEASE(pStream);
	return (hr == S_OK);
#endif
}