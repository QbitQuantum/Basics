/// <summary>
/// <para name='Name'>OpenDefaultMessageStore</para>
/// <para name='Purpose'>Find and open the default message store</para>
/// </summary>
/// <param name='lppDefaultMDB'>[out] Pointer to the opened default message store</param>
/// <returns>HRESULT</returns>
/// <remarks>
/// <para name='Notes'>Adapted from MFCMapi's MAPIStoreFunctions.cpp\OpenDefaultMessageStore()</para>
/// <para name='Author'></para>
/// <para name='LastModified'>29Jan2016</para>
/// </remarks>
STDMETHODIMP ZybraxiSoft::CMailbox::OpenDefaultMessageStore(LPMDB * lppDefaultMDB)
{
	HRESULT					hr = S_OK;
	LPMAPITABLE				pStoresTable = NULL;
	SPropValue				sPropVal;
	static SRestriction		sRes;
	LPSRowSet				pSRowSet = NULL;

	// Set up an enum to mask the numbers into pretty text
	enum
	{
		EID,
		NUM_COLS
	};

	// Set up a constant SPropTagArray
	/*static const SizedSPropTagArray(NUM_COLS, sptEIDCol) =
	{
		NUM_COLS,
		PR_ENTRYID,
	};*/
	static const struct _SPropTagArray_sptEIDCol
	{
		ULONG NUM_COLS;
		ULONG aulPropTag[1];
	} sptEIDCol =
	{
		NUM_COLS,
		PR_ENTRYID
	};

	// Get our message stores table
	// See https://msdn.microsoft.com/en-us/library/cc839751(v=office.15).aspx
	if (FAILED(hr = m_lpSession->GetMsgStoresTable(
		0,					// ulFlags (not sure why we don't use MAPI_UNICODE)
		&pStoresTable)))	// [out] lppTable
	{
		ERROR_MSG_W_HR("Unable to get message stores table", hr);
		goto CLEANUP;
	}

	// Set up our property value to restrict against
	sPropVal.ulPropTag = PR_DEFAULT_STORE;			// The proptag to check
	sPropVal.Value.b = true;						// what to check against

	// Set up to restrict so QueryRows gets only the default store
	sRes.rt = RES_PROPERTY;								// Compare if property
	sRes.res.resProperty.ulPropTag = PR_DEFAULT_STORE;	// PR_DEFAULT_STORE
	sRes.res.resProperty.relop = RELOP_EQ;				// is equal to
	sRes.res.resProperty.lpProp = &sPropVal;			// this property value

	// Run the query
	// See https://msdn.microsoft.com/en-us/library/office/cc815764.aspx
	if (FAILED(hr = HrQueryAllRows(
		pStoresTable,
		(LPSPropTagArray)&sptEIDCol,
		&sRes,
		NULL,
		0,
		&pSRowSet)))
	{
		ERROR_MSG_W_HR("HrQueryAllRows failed", hr);
		goto CLEANUP;
	}

	// Always check to see if we actually returned some rows
	if (pSRowSet && pSRowSet->cRows)
	{
		// Check to make sure we only returned one default
		// We'll use the first one regardless, but let's sound
		// a warning anyway.
		if (pSRowSet->cRows > 1)
		{
			WARN("We returned more than on Default store!");
		}

		// Open the message store
		if (FAILED(hr = DoOpenMsgStore(
			&pSRowSet->aRow[0].lpProps[EID].Value.bin,
			MDB_WRITE,
			lppDefaultMDB)))
		{
			ERROR_MSG_W_HR("DoOpenMsgStore failed.", hr);
			goto CLEANUP;
		}
	}
	else
		hr = MAPI_E_NOT_FOUND;

CLEANUP:
	if (pSRowSet)
	{
		FreeProws(pSRowSet);
		pSRowSet = NULL;
	}

	if (pStoresTable)
	{
		pStoresTable->Release();
		pStoresTable = NULL;
	}

	return hr;
}