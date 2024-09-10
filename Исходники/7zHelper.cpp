HRESULT __stdcall CArchiveExtractCallback::GetStream (
	unsigned int index,
	ISequentialOutStream **outStream,
	int askExtractMode
	)
{
	CPropVariant value;

	IInArchive *archive = m_pArchive->m_pArchive;

	if ( askExtractMode == 0 ) //extract
	{
		if ( archive->GetProperty (index, kpidPath, &value) != S_OK )
			return S_OK; //!!! to return error

		char szArcFileName[MAX_PATH];
		char szFullName[MAX_PATH];

		if ( value.vt == VT_BSTR )
			WideCharToMultiByte (CP_OEMCP, 0, value.bstrVal, -1, szArcFileName, MAX_PATH, NULL, NULL);
		else
		{
			//strcpy (szArcFileName, FSF.PointToName (m_pArchive->m_lpFileName));
			//CutTo (szArcFileName, '.', true);
			ATLASSERT(FALSE);
		}

		strcpy (szFullName, m_lpDestPath.c_str());
		PathAppendA(szFullName, szArcFileName);

		if ( (int)m_nLastProcessed == -1 )
			m_nLastProcessed = 0;

		FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
		DWORD dwFileAttributes = 0;

		memset (&ftCreationTime, 0, sizeof (FILETIME));
		memset (&ftLastAccessTime, 0, sizeof (FILETIME));
		memset (&ftLastWriteTime, 0, sizeof (FILETIME));

		if ( archive->GetProperty (index, kpidAttrib, &value) == S_OK )
		{
			if ( value.vt == VT_UI4 )
				dwFileAttributes = value.ulVal;
		}

		if ( archive->GetProperty (index, kpidCTime, &value) == S_OK )
		{
			if ( value.vt == VT_FILETIME )
				memcpy (&ftCreationTime, &value.filetime, sizeof (FILETIME));
		}

		if ( archive->GetProperty (index, kpidATime, &value) == S_OK )
		{
			if ( value.vt == VT_FILETIME )
				memcpy (&ftLastAccessTime, &value.filetime, sizeof (FILETIME));
		}

		if ( archive->GetProperty (index, kpidMTime, &value) == S_OK )
		{
			if ( value.vt == VT_FILETIME )
				memcpy (&ftLastWriteTime, &value.filetime, sizeof (FILETIME));
		}

		bool bIsFolder = false;

		if ( archive->GetProperty (index, kpidIsDir, &value) == S_OK )
		{
			if (value.vt == VT_BOOL)
				bIsFolder = (value.boolVal == VARIANT_TRUE);
		}

		if ( bIsFolder || dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY )
		{
			*outStream = NULL;
			CreateDirEx (szFullName, dwFileAttributes);
		}
		else
		{
			CreateDirs (szFullName);
			COutFile *file = new COutFile (szFullName);
			if ( file->Open () )
			{
				file->SetAttributes (dwFileAttributes);
				file->SetTime (&ftCreationTime, &ftLastAccessTime, &ftLastWriteTime);
				*outStream = file;

				m_files.push_back( szFullName );
			}
			else
				delete file;
		}
	}
	else
		*outStream = NULL;

	return S_OK;
}