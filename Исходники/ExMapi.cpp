BOOL CExMapi::OpenNextMessageStore(LPMAPITABLE lpMsgStoreTable, ULONG ulFlags)
{
	if(!m_pSession) return FALSE;
	if(!lpMsgStoreTable) return FALSE;

	BOOL doLog = m_pCtrl->IsEnableLog();
	if(doLog)
	{
		m_logHelper.LogPAB(L"Function OpenNextMessageStore START.");
	}

	
	m_ulMDBFlags = ulFlags;

	LPSRowSet pRows = NULL;
	const int nProperties = 1;
	SizedSPropTagArray(nProperties,Columns)={nProperties,{PR_ENTRYID}};

	BOOL bResult = FALSE;	
	try
	{
		if(lpMsgStoreTable->SetColumns((LPSPropTagArray)&Columns, 0) == S_OK) 
		{
			while(TRUE) 
			{
				bResult = FALSE;
				if(lpMsgStoreTable->QueryRows(1,0,&pRows) != S_OK)
					MAPIFreeBuffer(pRows);
				else if(pRows->cRows!=1) 
					FreeProws(pRows);
				else 
				{					
					LPMDB pMsgStore = NULL;

					ULONG cbEntryId = pRows->aRow[0].lpProps[0].Value.bin.cb;
					LPENTRYID lpEntryId = (ENTRYID*)pRows->aRow[0].lpProps[0].Value.bin.lpb;
					
					bResult = (m_pSession->OpenMsgStore(NULL,
						cbEntryId,
						lpEntryId,
						NULL,
						MDB_NO_DIALOG | MAPI_BEST_ACCESS,
						&pMsgStore) == S_OK);				

					if(bResult)
					{
						if(m_pMsgStore)
						{
							//check if new open msg store is the same as opened msg store.
							if(AreSame(m_pMsgStore,pMsgStore))
							{
								if(doLog)
								{
									m_logHelper.LogPAB(L"Message Store is already opend.");
								}

								RELEASE(pMsgStore);
								FreeProws(pRows);							
								continue;
							}
							else
							{
								RELEASE(m_pMsgStore);
								m_pMsgStore = pMsgStore;				
								bResult = TRUE;
							}										
						}
						else
						{						
							m_pMsgStore = pMsgStore;				
						}				
					}				
					FreeProws(pRows);
				}
				break;
			}
		}		
	}
	catch(_com_error& e)
	{
		if(doLog)
		{
			m_logHelper.LogPAB(L"OpenNextMessageStore Exception:");
			m_logHelper.LogPAB(e.ErrorMessage());
		}
		return FALSE;
	}
	if(doLog)
	{
		m_logHelper.LogPAB(L"Function OpenNextMessageStore END.");
	}

	return bResult;
}