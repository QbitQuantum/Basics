_Check_return_ HRESULT SearchContentsTableForName(
	_In_ LPMAPITABLE pTable,
	_In_z_ LPCTSTR szName,
	ULONG PropTagToCompare,
	_Deref_out_opt_ LPSPropValue *lppPropsFound)
{
	HRESULT			hRes = S_OK;

	LPSRowSet		pRows = NULL;

	enum
	{
		abPR_ENTRYID,
		abPR_DISPLAY_NAME,
		abPR_RECIPIENT_TYPE,
		abPR_ADDRTYPE,
		abPR_DISPLAY_TYPE,
		abPropTagToCompare,
		abNUM_COLS
	};

	const SizedSPropTagArray(abNUM_COLS, abCols) =
	{
		abNUM_COLS,
		PR_ENTRYID,
		PR_DISPLAY_NAME,
		PR_RECIPIENT_TYPE,
		PR_ADDRTYPE,
		PR_DISPLAY_TYPE,
		PropTagToCompare
	};

	*lppPropsFound = NULL;
	if (!pTable || !szName) return MAPI_E_INVALID_PARAMETER;

	DebugPrint(DBGGeneric, _T("SearchContentsTableForName: Looking for \"%s\"\n"), szName);

	// Set a restriction so we only find close matches
	LPSRestriction	lpSRes = NULL;

	EC_H(CreateANRRestriction(
		PR_ANR,
		szName,
		NULL,
		&lpSRes));

	EC_MAPI(pTable->SetColumns((LPSPropTagArray)&abCols, TBL_BATCH));

	// Jump to the top of the table...
	EC_MAPI(pTable->SeekRow(
		BOOKMARK_BEGINNING,
		0,
		NULL));

	// ..and jump to the first matching entry in the table
	EC_MAPI(pTable->Restrict(
		lpSRes,
		NULL
		));

	// Now we iterate through each of the matching entries
	if (!FAILED(hRes)) for (;;)
	{
		hRes = S_OK;
		if (pRows) FreeProws(pRows);
		pRows = NULL;
		EC_MAPI(pTable->QueryRows(
			1,
			NULL,
			&pRows));
		if (FAILED(hRes) || !pRows || (pRows && !pRows->cRows)) break;

		// An error at this point is an error with the current entry, so we can continue this for statement
		// Unless it's an allocation error. Those are bad.
		if (PropTagToCompare == pRows->aRow->lpProps[abPropTagToCompare].ulPropTag &&
			CheckStringProp(&pRows->aRow->lpProps[abPropTagToCompare], PT_TSTRING))
		{
			DebugPrint(DBGGeneric, _T("SearchContentsTableForName: found \"%s\"\n"), pRows->aRow->lpProps[abPropTagToCompare].Value.LPSZ);
			if (lstrcmpi(szName, pRows->aRow->lpProps[abPropTagToCompare].Value.LPSZ) == 0)
			{
				DebugPrint(DBGGeneric, _T("SearchContentsTableForName: This is an exact match!\n"));
				// We found a match! Return it!
				EC_MAPI(ScDupPropset(
					abNUM_COLS,
					pRows->aRow->lpProps,
					MAPIAllocateBuffer,
					lppPropsFound));
				break;
			}
		}
	}

	if (!*lppPropsFound)
	{
		DebugPrint(DBGGeneric, _T("SearchContentsTableForName: No exact match found.\n"));
	}
	MAPIFreeBuffer(lpSRes);
	if (pRows) FreeProws(pRows);
	return hRes;
} // SearchContentsTableForName