bool MAPIStorageAdviser::AdviseAll()
{
  IMAPISession* pSession = InitIMAPISession();
  IMAPITable* pStoresTable = GetStoresTable(pSession); 
  
  SizedSPropTagArray(2, tblColumns) = {2, {PR_DISPLAY_NAME, PR_ENTRYID}};
  pStoresTable->SetColumns((LPSPropTagArray)&tblColumns, 0);
  
  for(;;) {
    SRowSet * pRowSet = NULL;

    pStoresTable->QueryRows(1, 0, &pRowSet);
    
    if(pRowSet->cRows != 1)
      break;

    ASSERT(pRowSet->aRow[0].cValues == tblColumns.cValues);
    SPropValue* pVal = pRowSet->aRow[0].lpProps;

    ASSERT(pVal[0].ulPropTag == PR_DISPLAY_NAME);
    ASSERT(pVal[1].ulPropTag == PR_ENTRYID);

    LPWSTR lpStoreName = pRowSet->aRow[0].lpProps[0].Value.lpszW;

    // Open Store
    LPBYTE pEntry = (LPBYTE)pRowSet->aRow[0].lpProps[1].Value.bin.lpb;
    ULONG ulStoreBytes = pRowSet->aRow[0].lpProps[1].Value.bin.cb;

    IMsgStore* pStore = _GetStoreFromEntryID(pSession, ulStoreBytes, pEntry);
    if (pStore == NULL)
    {
      continue;
    }
    
	if (AddSink(pStore) == true) {
	}else{
	}

    pStore->Release();
    
    FreeProws(pRowSet);
  }
  
  pStoresTable->Release();
  pSession->Release();
  
  return true;
}