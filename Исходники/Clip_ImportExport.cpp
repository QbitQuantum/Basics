//##ModelId=474D30760272
bool CClip_ImportExport::ExportToSqliteDB(CppSQLite3DB &db)
{
	bool bRet = false;
	try
	{
		//Add to Main Table
		m_Desc.Replace(_T("'"), _T("''"));
		db.execDMLEx(_T("insert into Main values(NULL, %d, '%s');"), CURRENT_EXPORT_VERSION, m_Desc);
		long lId = (long)db.lastRowId();

		//Add to Data table
		CClipFormat* pCF;
		CppSQLite3Statement stmt = db.compileStatement(_T("insert into Data values (NULL, ?, ?, ?, ?);"));

		for(int i = m_Formats.GetSize()-1; i >= 0 ; i--)
		{
			pCF = & m_Formats.ElementAt(i);

			stmt.bind(1, lId);
			stmt.bind(2, GetFormatName(pCF->m_cfType));
			long lOriginalSize = GlobalSize(pCF->m_hgData);
			stmt.bind(3, lOriginalSize);

			const unsigned char *Data = (const unsigned char *)GlobalLock(pCF->m_hgData);
			if(Data)
			{
				//First compress the data
				long lZippedSize = compressBound(lOriginalSize);
				Bytef *pZipped = new Bytef[lZippedSize];
				if(pZipped)
				{				
					int nZipReturn = compress(pZipped, (uLongf *)&lZippedSize, (const Bytef *)Data, lOriginalSize);
					if(nZipReturn == Z_OK)
					{
						stmt.bind(4, pZipped, lZippedSize);
					}

					delete []pZipped;
					pZipped = NULL;
				}
			}
			GlobalUnlock(pCF->m_hgData);

			stmt.execDML();
			stmt.reset();

			m_Formats.RemoveAt(i);
		}

		bRet = true;
	}
	CATCH_SQLITE_EXCEPTION_AND_RETURN(false)

	return bRet;
}