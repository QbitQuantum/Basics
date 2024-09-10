int __stdcall SevenZipArchive::pGetArchiveItem (
		ArchiveItemInfo *pItem
		)
{
	if ( (int)m_nItemsNumber == -1)
		return E_EOF;

	int nResult = E_BROKEN;

	CPropVariant value;

	if ( m_pArchive->GetProperty (m_nItemsNumber, kpidPath, &value) == S_OK )
	{
		if ( value.vt == VT_BSTR )
			WideCharToMultiByte (CP_OEMCP, 0, value.bstrVal, -1, pItem->pi.FindData.cFileName, sizeof (pItem->pi.FindData.cFileName), NULL, NULL);
		else
		{
			strcpy (pItem->pi.FindData.cFileName, FSF.PointToName (m_lpFileName));
			CutTo (pItem->pi.FindData.cFileName, '.', true);
		}

		if ( m_pArchive->GetProperty (m_nItemsNumber, kpidAttrib, &value) == S_OK )
		{
			if ( value.vt == VT_UI4 )
				pItem->pi.FindData.dwFileAttributes = value.ulVal;
		}

		if ( m_pArchive->GetProperty (m_nItemsNumber, kpidIsDir, &value) == S_OK )
		{
			if ( value.vt == VT_BOOL )
			{
				if ( value.boolVal == VARIANT_TRUE )
					pItem->pi.FindData.dwFileAttributes |= FILE_ATTRIBUTE_DIRECTORY;
			}
		}

		if ( m_pArchive->GetProperty (m_nItemsNumber, kpidSize, &value) == S_OK )
		{
			unsigned __int64 size = VariantToInt64 (&value);

			pItem->pi.FindData.nFileSizeLow = (DWORD)size;
			pItem->pi.FindData.nFileSizeHigh = (DWORD)(size >> 32);
		}

		if ( m_pArchive->GetProperty (m_nItemsNumber, kpidPackSize, &value) == S_OK )
		{
			unsigned __int64 size = VariantToInt64 (&value);

			pItem->pi.PackSize = (DWORD)size;
			pItem->pi.PackSizeHigh = (DWORD)(size >> 32);
		}