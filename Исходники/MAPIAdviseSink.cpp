bool CMAPIAdviseSink::_GetIgnoredFolders()
{
  LPSPropValue rgprops = NULL;
  // LPSPropValue lppPropArray = NULL;
  ULONG cValues = 0;
  // IMAPIFolder *pPOPInboxFolder = NULL;
  
  SizedSPropTagArray(1, rgFolderTags) = {1, { /* PR_IPM_OUTBOX_ENTRYID, */ PR_CE_IPM_DRAFTS_ENTRYID, } };
  
  HRESULT hr = m_pStore->GetProps((LPSPropTagArray)&rgFolderTags, MAPI_UNICODE, &cValues, &rgprops);
  if(FAILED(hr))
    return false;
  
  for (ULONG i = 0; i < 1; i++)
  {
    ULONG cbEntryID = rgprops[i].Value.bin.cb;
    LPENTRYID lpEntryID = (LPENTRYID)rgprops[i].Value.bin.lpb;
    
    rawEntryID* reID = new rawEntryID;
    reID->cbSize = cbEntryID;
    reID->lpEntryID = (LPBYTE)lpEntryID;
    
    //_ignoredFolders.push_back(reID);
    
    IMAPIFolder* pFolder = NULL;
    hr = m_pStore->OpenEntry(
      cbEntryID,
      lpEntryID,
      NULL, 
      MAPI_MODIFY,
      NULL, 
      (LPUNKNOWN*)&pFolder);
	if (!pFolder) {
		MAPIFreeBuffer(rgprops);
		return false;
	}

    SizedSPropTagArray(1, ptaFolder) = {1, {PR_DISPLAY_NAME}};
    LPSPropValue rgFolderProps = NULL;
    pFolder->GetProps((LPSPropTagArray)&ptaFolder, MAPI_UNICODE, &cValues, &rgFolderProps);
    LPWSTR lpFolderName = rgFolderProps[0].Value.lpszW;
    
  }
  
  MAPIFreeBuffer(rgprops);
  
  return true;
}