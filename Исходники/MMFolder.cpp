// Search folder for entry ID of child folder by name.
HRESULT HrMAPIFindFolderW(
	_In_ LPMAPIFOLDER lpFolder,        // pointer to folder
	_In_z_ LPCWSTR lpszName,           // name of child folder to find
	_Out_opt_ ULONG* lpcbeid,          // pointer to count of bytes in entry ID
	_Deref_out_opt_ LPENTRYID* lppeid) // pointer to entry ID pointer
{
	DebugPrint(DBGGeneric,"HrMAPIFindFolderW: Locating folder \"%ws\"\n", lpszName);
	HRESULT hRes = S_OK;
	LPMAPITABLE lpTable = NULL;
	LPSRowSet lpRow = NULL;
	LPSPropValue lpRowProp = NULL;
	ULONG i = 0;

	enum
	{
		ePR_DISPLAY_NAME_W,
		ePR_ENTRYID,
		NUM_COLS
	};
	static const SizedSPropTagArray(NUM_COLS, rgColProps) =
	{
		NUM_COLS,
		PR_DISPLAY_NAME_W,
		PR_ENTRYID
	};

	if (!lpcbeid || !lppeid) return MAPI_E_INVALID_PARAMETER;
	*lpcbeid = 0;
	*lppeid  = NULL;
	if (!lpFolder) return MAPI_E_INVALID_PARAMETER;

	WC_MAPI(lpFolder->GetHierarchyTable(MAPI_UNICODE | MAPI_DEFERRED_ERRORS, &lpTable));
	if (SUCCEEDED(hRes) && lpTable)
	{
		WC_MAPI(HrQueryAllRows(lpTable, (LPSPropTagArray)&rgColProps, NULL, NULL, 0, &lpRow));
	}

	if (SUCCEEDED(hRes) && lpRow)
	{
		for (i = 0; i < lpRow->cRows; i++)
		{
			lpRowProp = lpRow->aRow[i].lpProps;

			if (PR_DISPLAY_NAME_W == lpRowProp[ePR_DISPLAY_NAME_W].ulPropTag &&
				_wcsicmp(lpRowProp[ePR_DISPLAY_NAME_W].Value.lpszW, lpszName) == 0 &&
				PR_ENTRYID == lpRowProp[ePR_ENTRYID].ulPropTag)
			{
				WC_H(MAPIAllocateBuffer(lpRowProp[ePR_ENTRYID].Value.bin.cb, (LPVOID*)lppeid));
				if (SUCCEEDED(hRes) && lppeid)
				{
					*lpcbeid = lpRowProp[ePR_ENTRYID].Value.bin.cb;
					CopyMemory(*lppeid, lpRowProp[ePR_ENTRYID].Value.bin.lpb, *lpcbeid);
				}
				break;
			}
		}
	}

	if (!*lpcbeid)
	{
		hRes = MAPI_E_NOT_FOUND;
	}

	FreeProws(lpRow);
	if (lpTable) lpTable->Release();

	return hRes;
} // HrMAPIFindFolderW