// if I try to use MAPI_UNICODE when UNICODE is defined I get the MAPI_E_BAD_CHARWIDTH 
// error so I force narrow strings here
BOOL CMAPIEx::GetProfileName(CString& strProfileName)
{
	BOOL bResult=FALSE;
#ifndef _WIN32_WCE
	if(!m_pSession) return FALSE;

	LPSRowSet pRows=NULL;
	const int nProperties=2;
	SizedSPropTagArray(nProperties, Columns)={nProperties,{PR_DISPLAY_NAME_A, PR_RESOURCE_TYPE}};

	IMAPITable*	pStatusTable;
	if(m_pSession->GetStatusTable(0, &pStatusTable)==S_OK) 
	{
		if(pStatusTable->SetColumns((LPSPropTagArray)&Columns, 0)==S_OK) 
		{
			while(pStatusTable->QueryRows(1, 0, &pRows)==S_OK) 
			{
				if(pRows->cRows!=1) FreeProws(pRows);
				else if(pRows->aRow[0].lpProps[1].Value.ul==MAPI_SUBSYSTEM) 
				{
					strProfileName=(LPSTR)GetValidString(pRows->aRow[0].lpProps[0]);
					FreeProws(pRows);
					bResult=TRUE;
				} 
				else 
				{
					FreeProws(pRows);
					continue;
				}
				break;
			}
		}
		RELEASE(pStatusTable);
	}
#endif
	return bResult;
}