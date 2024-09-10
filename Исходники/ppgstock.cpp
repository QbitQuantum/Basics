void CStockPropPage::FillPropnameList(REFGUID guid, int nIndirect, CComboBox& combo)
{
	USES_CONVERSION;

	combo.ResetContent();
	UINT cProps = 0;

	ULONG nObjects;
	LPDISPATCH* ppDisp = GetObjectArray(&nObjects);

	if (ppDisp != NULL)
	{
		LPTYPEINFO pTypeInfo;
		LPTYPEATTR pTypeAttr;
		LPVARDESC pVarDesc;
		ULONG iObj;
		WORD iProp;
		BSTR rgbstr[1];
		UINT cName;

		// Get the property sheet locale
		LPPROPERTYPAGESITE pPageSite;
		if ((pPageSite = GetPageSite()) != NULL)
			if (FAILED(pPageSite->GetLocaleID(&m_lcid)))
				m_lcid = 0;

		// Iterate through all objects.

		for (iObj = 0; iObj < nObjects; iObj++)
		{
			pTypeInfo = NULL;
			if ((ppDisp[iObj] != NULL) &&
				SUCCEEDED(ppDisp[iObj]->GetTypeInfo(0, m_lcid, &pTypeInfo)))
			{
				ASSERT(pTypeInfo != NULL);
				pTypeAttr = NULL;
				if (SUCCEEDED(pTypeInfo->GetTypeAttr(&pTypeAttr)))
				{
					ASSERT(pTypeAttr != NULL);

					// Iterate through all properties of object.

					for (iProp = 0; iProp < pTypeAttr->cVars; iProp++)
					{
						pVarDesc = NULL;
						if (SUCCEEDED(pTypeInfo->GetVarDesc(iProp, &pVarDesc)))
						{
							// Check whether property has desired type

							if (!(pVarDesc->wVarFlags & VARFLAG_FHIDDEN) &&
								AfxOleTypeMatchGuid(pTypeInfo,
									&pVarDesc->elemdescVar.tdesc, guid,
									nIndirect))
							{
								// Get property name and insert into list.

								if (SUCCEEDED(pTypeInfo->GetNames(
										pVarDesc->memid, rgbstr, 1, &cName)))
								{
									// Don't insert duplicates.

									LPCTSTR lpstr = OLE2CT(rgbstr[0]);
									if (combo.FindString(-1, lpstr)
											== CB_ERR)
									{
										int iItem = combo.AddString(lpstr);
										if (iItem >= 0)
										{
											combo.SetItemData(iItem, (DWORD)pVarDesc->memid);
											++cProps;
										}
									}

									SysFreeString(rgbstr[0]);
								}
							}
							pTypeInfo->ReleaseVarDesc(pVarDesc);
						}
					}

					pTypeInfo->ReleaseTypeAttr(pTypeAttr);
				}
				pTypeInfo->Release();
			}
		}
	}

	// Select the first one
	m_iPropName = 0;            // Prevents save from happening
	if (combo.SetCurSel(0) != CB_ERR)
		combo.GetLBText(0, m_strPropName);

	// Disable or set the size of the combo, as appropriate
	if (cProps <= 1)
		combo.EnableWindow(FALSE);
	else
		_AfxSizeComboToContent(&combo);

	UpdateData(FALSE);
	SetModifiedFlag(FALSE);
}