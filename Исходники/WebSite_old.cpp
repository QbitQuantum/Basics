void CSiteDir::BuildFromDatabase()
{
	WCHAR sql[256];
	swprintf(sql, L"SELECT id,filename,type,file_size,file_date FROM files WHERE parent_id = %d", m_dbid);
	_variant_t va;
	ADODB::_RecordsetPtr recordset = m_pWebSite->m_siteDataConnection->Execute(sql, &va, ADODB::adCmdText);

	CArray<CSiteDir*,CSiteDir*> dirs;

	while (recordset->EndOfFile == false)
	{
		CSiteItem* pItem;

		BYTE type = recordset->Fields->Item[_bstr_t("type")]->Value.lVal;
		if (type == 1)	// Directory
		{
			CSiteDir* pDir = new CSiteDir;
			pItem = pDir;

			strcpy(pDir->m_wfd.cFileName, _bstr_t(recordset->Fields->Item[_bstr_t("filename")]->Value));

			_makepath(pDir->m_pathName.GetBuffer(512), NULL, m_pathName, pDir->m_wfd.cFileName, NULL);
			pDir->m_pathName.ReleaseBuffer();

			dirs.Add(pDir);
		}
		else if (type == 2)	// File
		{
			CSiteFile* pFile = new CSiteFile;
			pItem = pFile;

			strcpy(pFile->m_wfd.cFileName, _bstr_t(recordset->Fields->Item[_bstr_t("filename")]->Value));
			pFile->m_wfd.nFileSizeLow = recordset->Fields->Item[_bstr_t("file_size")]->Value.lVal;
		}
		else
			ATLASSERT(0);

		if (pItem)
		{
			pItem->m_pWebSite = m_pWebSite;
			pItem->m_dbid = recordset->Fields->Item[_bstr_t("id")]->Value.lVal;
		//	pItem->m_name = pItem->m_wfd.cFileName;	// ??

			// lastWriteDate
			double lastWriteTime = recordset->Fields->Item[_bstr_t("file_date")]->Value;
			SYSTEMTIME systime;
			VariantTimeToSystemTime(lastWriteTime, &systime);
			SystemTimeToFileTime(&systime, &pItem->m_wfd.ftLastWriteTime);

			AddChildTail(pItem);
		}

		recordset->MoveNext();
	}

	for (int i = 0; i < dirs.GetSize(); i++)
	{
		dirs[i]->BuildFromDatabase();	// Recurse
	}
}