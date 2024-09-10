HWND COccManager::CreateDlgControl(CWnd* pWndParent, HWND hwAfter,
	BOOL bDialogEx, LPDLGITEMTEMPLATE pItem, WORD nMsg, BYTE* lpData, DWORD cb)
{
	LPWSTR pszClass = (LPWSTR)(pItem + 1);
	DLGITEMTEMPLATE dlgItemTmp;

	if (bDialogEx)
	{
		// We have an extended dialog template: copy relevant parts into an
		// ordinary dialog template, because their layouts are different
		DLGITEMTEMPLATEEX* pItemEx = (DLGITEMTEMPLATEEX*)pItem;
		dlgItemTmp.style = pItemEx->style;
		dlgItemTmp.dwExtendedStyle = pItemEx->exStyle;
		dlgItemTmp.x = pItemEx->x;
		dlgItemTmp.y = pItemEx->y;
		dlgItemTmp.cx = pItemEx->cx;
		dlgItemTmp.cy = pItemEx->cy;
		dlgItemTmp.id = (WORD)pItemEx->id;
		pItem = &dlgItemTmp;
		pszClass = (LPWSTR)(pItemEx + 1);
	}

	CRect rect(pItem->x, pItem->y, pItem->x + pItem->cx, pItem->y + pItem->cy);
	::MapDialogRect(pWndParent->m_hWnd, &rect);

	BSTR bstrLicKey = NULL;

	// extract license key data, if any
	if (cb >= sizeof(ULONG))
	{
		ULONG cchLicKey = *(UNALIGNED ULONG*)lpData;
		lpData += sizeof(ULONG);
		cb -= sizeof(ULONG);
		if (cchLicKey > 0)
		{
			bstrLicKey = SysAllocStringLen((LPCOLESTR)lpData, cchLicKey);
			lpData += cchLicKey * sizeof(WCHAR);
			cb -= cchLicKey * sizeof(WCHAR);
		}
	}

	// If WM_OCC_INITNEW, we should have exhausted all of the data by now.
	ASSERT((nMsg != WM_OCC_INITNEW) || (cb == 0));

	CDataBoundProperty* pBindings = NULL;
	CString strDataField;
	WORD ctlidRowSource = 0;
	DISPID defdispid = 0;
	UINT dwType = 0;

	if (nMsg == WM_OCC_LOADFROMSTREAM_EX ||
		nMsg == WM_OCC_LOADFROMSTORAGE_EX)
	{
		// Read the size of the section
		ULONG cbOffset = *(UNALIGNED ULONG*)lpData;
		ULONG cbBindInfo = cbOffset - sizeof(DWORD);
		lpData += sizeof(DWORD);

		ULONG dwFlags = *(UNALIGNED ULONG*)lpData;
		cbBindInfo -= sizeof(DWORD);
		lpData += sizeof(DWORD);
		ASSERT(dwFlags == 1);

		ULONG cbBinding = *(UNALIGNED ULONG*)lpData;
		cbBindInfo -= sizeof(DWORD);
		lpData += sizeof(DWORD);

		while(cbBindInfo > 0)
		{
			DISPID dispid;
			UWORD ctlid;

			dispid = *(UNALIGNED DISPID *)lpData;
			lpData += sizeof(DISPID);
			cbBindInfo -= sizeof(DISPID);
			ctlid =  *(UNALIGNED WORD *)lpData;
			lpData += sizeof(WORD);
			cbBindInfo -= sizeof(WORD);

			if(dispid == DISPID_DATASOURCE)
			{
				defdispid = *(UNALIGNED ULONG*)lpData;
				cbBindInfo -= sizeof(DISPID);
				lpData += sizeof(DISPID);
				dwType = *(UNALIGNED ULONG*)lpData;
				cbBindInfo -= sizeof(DWORD);
				lpData += sizeof(DWORD);

				ASSERT(*(UNALIGNED DISPID *)lpData == DISPID_DATAFIELD);
				lpData += sizeof(DISPID);
				cbBindInfo -= sizeof(DISPID);
				// Skip the string length
				lpData += sizeof(DWORD);
				cbBindInfo -= sizeof(DWORD);
				strDataField = (char *)lpData;
				lpData += strDataField.GetLength()+1;
				cbBindInfo -= strDataField.GetLength()+1;
				ctlidRowSource = ctlid;
			} else
				pBindings = new CDataBoundProperty(pBindings, dispid, ctlid);
		}
		cb -= cbOffset;
	}

	// From now on act as a regular type
	nMsg -= (WM_OCC_LOADFROMSTREAM_EX - WM_OCC_LOADFROMSTREAM);

	GUID clsid;
	HRESULT hr;
	if (pszClass[0] == L'{')
		hr = CLSIDFromString(pszClass, &clsid);
	else
		hr = CLSIDFromProgID(pszClass, &clsid);

#ifdef _DEBUG
	if (FAILED(hr))
	{
		TRACE1("Unable to convert \"%ls\" to a class ID.\n", pszClass);
		TRACE1(">>> Result code: 0x%08lx\n", hr);
		if (pszClass[0] != L'{')
			TRACE0(">>> Is the control properly registered?\n");
	}
#endif

	CMemFile memFile(lpData, cb);
	CMemFile* pMemFile = (nMsg == WM_OCC_INITNEW) ? NULL : &memFile;

	CWnd* pWndNew = NULL;
	COleControlSite* pSite = NULL;

	if (SUCCEEDED(hr) &&
		pWndParent->InitControlContainer() &&
		pWndParent->m_pCtrlCont->CreateControl(NULL, clsid, NULL, pItem->style,
			rect, pItem->id, pMemFile, (nMsg == WM_OCC_LOADFROMSTORAGE),
			bstrLicKey, &pSite))
	{
		ASSERT(pSite != NULL);
		// set ZOrder only!
		SetWindowPos(pSite->m_hWnd, hwAfter, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

		pSite->m_pBindings = pBindings;
		pSite->m_strDataField = strDataField;
		pSite->m_ctlidRowSource = ctlidRowSource;
		pSite->m_defdispid = defdispid;
		pSite->m_dwType = dwType;

		// Determine if this is a DataSource by QI for ICursor
		ICursor* pCursor;
		if (SUCCEEDED(pSite->m_pObject->QueryInterface(IID_ICursor,
			(LPVOID *)&pCursor)))
		{
			pCursor->Release();
            pSite->m_pDataSourceControl = new CDataSourceControl(pSite);
		}
	}

	if (bstrLicKey != NULL)
		SysFreeString(bstrLicKey);

	return (pSite != NULL) ? pSite->m_hWnd : NULL;
}