	virtual BOOL Write (const CString& filename)
	{
		if (CBCGPBaseInfoWriter::IsFileReadOnly (filename))
		{
			//CFileParser::ReportSaveLoadException (filename, NULL, TRUE, IDP_ERROR_FILE_READONLY);
			return FALSE;
		}

		CFile* pFile = new CStdioFile;
		CFileException fe;

		if (!pFile->Open (filename, GetFlags (), &fe))
		{
			delete pFile;

			//CFileParser::ReportSaveLoadException (filename, &fe, TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
			return FALSE;
		}

		BOOL bResult = FALSE;

		TRY
		{
			CWaitCursor wait;

			bResult = Write (*pFile);
			
			pFile->Close();
			delete pFile;
		}
		CATCH_ALL(e)
		{
			pFile->Abort();
			delete pFile;
		}
		END_CATCH_ALL

		return bResult;
	}