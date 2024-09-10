BOOL ReadWAB(LPADRBOOK pAdrBook, 
			 LPWABOBJECT pWABObject, 
			 AdrBookTable **ppTable,
			 UINT *pNumEntries)
{
    ULONG ulObjType =   0;
	LPMAPITABLE lpAB =  NULL;
    LPTSTR * lppszArray=NULL;
    ULONG cRows =       0;
    LPSRowSet lpRow =   NULL;
	LPSRowSet lpRowAB = NULL;
    LPABCONT  lpContainer = NULL;
	int cNumRows = 0;
    int nRows=0;
	int nCount = 0;

    HRESULT hr = E_FAIL;

    ULONG lpcbEID;
	LPENTRYID lpEID = NULL;

    // Get the entryid of the root PAB container
    //
    hr = pAdrBook->GetPAB( &lpcbEID, &lpEID);

	ulObjType = 0;

    // Open the root PAB container
    // This is where all the WAB contents reside
    //
    hr = pAdrBook->OpenEntry(lpcbEID,
					    		(LPENTRYID)lpEID,
						    	NULL,
							    0,
							    &ulObjType,
							    (LPUNKNOWN *)&lpContainer);

	pWABObject->FreeBuffer(lpEID);

	lpEID = NULL;
	
    if(HR_FAILED(hr))
        goto exit;

    // Get a contents table of all the contents in the
    // WABs root container
    //
    hr = lpContainer->GetContentsTable( 0,
            							&lpAB);

    if(HR_FAILED(hr))
        goto exit;

    // Order the columns in the ContentsTable to conform to the
    // ones we want - which are mainly DisplayName, EntryID and
    // ObjectType
    // The table is gauranteed to set the columns in the order 
    // requested
    //
	hr =lpAB->SetColumns( (LPSPropTagArray)&ptaEid, 0 );

    if(HR_FAILED(hr))
        goto exit;


    // Reset to the beginning of the table
    //
	hr = lpAB->SeekRow( BOOKMARK_BEGINNING, 0, NULL );

    if(HR_FAILED(hr))
        goto exit;

    // Read all the rows of the table one by one
    //
	do {

		hr = lpAB->QueryRows(1,	0, &lpRowAB);

        if(HR_FAILED(hr))
            break;

        if(lpRowAB)
        {
            cNumRows = lpRowAB->cRows;

		    if (cNumRows)
		    {
                LPTSTR szName = lpRowAB->aRow[0].lpProps[ieidPR_DISPLAY_NAME].Value.lpszA;
				LPTSTR szEmail = NULL;
                LPENTRYID lpEID = (LPENTRYID) lpRowAB->aRow[0].lpProps[ieidPR_ENTRYID].Value.bin.lpb;
                ULONG cbEID = lpRowAB->aRow[0].lpProps[ieidPR_ENTRYID].Value.bin.cb;
				LPMAILUSER pMailUser = NULL;
				ULONG ulObjType = 0;
				ULONG ulValues;
				LPSPropValue lpPropArray;

				*ppTable = (AdrBookTable *) realloc(*ppTable, 
										sizeof(AdrBookTable) * (nCount+1));

				(*ppTable)[nCount].szName = 
										(char *) calloc(strlen(szName)+1, 1);
				strcpy((*ppTable)[nCount].szName, szName);

				if (lpRowAB->aRow[0].lpProps[ieidPR_OBJECT_TYPE].Value.l == 
					MAPI_MAILUSER)
				{
					pAdrBook->OpenEntry(cbEID,
								lpEID,
								NULL,         // interface
								0,            // flags
								&ulObjType,
								(LPUNKNOWN *)&pMailUser);

					if(pMailUser)
					{
						pMailUser->GetProps((LPSPropTagArray) &ptaEmail, 
									0, 
									&ulValues, 
									&lpPropArray);
						
						pMailUser->Release();
					}
					
					if ((lpPropArray[iemailPR_EMAIL_ADDRESS].ulPropTag & 
							0xffff) == PT_ERROR)
					{
						szEmail = 
							lpPropArray[iemailPR_DISPLAY_NAME].Value.lpszA;
					}
					else
						szEmail = 
							lpPropArray[iemailPR_EMAIL_ADDRESS].Value.lpszA;
					
					if (szEmail != NULL)
					{
						(*ppTable)[nCount].szEmail = 
										(char *) calloc(strlen(szEmail)+1, 1);
	
						strcpy((*ppTable)[nCount].szEmail, szEmail);
					}
					else
					{
						(*ppTable)[nCount].szEmail = 
										(char *) calloc(strlen("")+1, 1);

						strcpy((*ppTable)[nCount].szEmail, "");
					}

					pWABObject->FreeBuffer(lpPropArray);
				}
				else
					(*ppTable)[nCount].szEmail = NULL;
				
				nCount++;
		    }
		    FreeProws(pWABObject, lpRowAB);		
        }

	}while ( SUCCEEDED(hr) && cNumRows && lpRowAB)  ;

exit:

	if ( lpContainer )
		lpContainer->Release();

	if ( lpAB )
		lpAB->Release();

	*pNumEntries = nCount;

	if (SUCCEEDED(hr))
		return TRUE;
	else
		return FALSE;
}