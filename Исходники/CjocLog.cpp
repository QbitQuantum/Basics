void CjocLog::Initialize (std::wstring &strFile, unsigned long lMaxFileSize, bool bAddLogWhenCreateFile)
{
	bool bCreate = false;

	if (strFile.empty () == true){throw JOC_Error_(enjocErrors::err_bad_arguments);}

	FILE *pFile = NULL;
		
	pFile = _wfopen (strFile.c_str (),L"r");
	if (pFile != NULL)
	{
		//Exists
		fclose (pFile);

		//Set file
		m_strFile = strFile;

		struct _stat64i32 buf;
		_wstat(m_strFile.c_str (),&buf);

		if (buf.st_size > lMaxFileSize)
		{
			std::wstring strNewFileName;
			strNewFileName = m_strFile + L".old";

			//Delete .old if exists
			_wremove(strNewFileName.c_str ());

			int nRc = _wrename (m_strFile.c_str (),strNewFileName.c_str ());
			if (nRc != 0){throw JOC_Error_arg_(enjocErrors::err_renaming_file,m_strFile.c_str ());}

			bCreate = true;
		}
	}
	else
	{
		bCreate = true;
	}
	
	if (bCreate == true)
	{
		//Create
		pFile = _wfopen (strFile.c_str (),L"w");
		if (pFile == NULL){throw JOC_Error_arg_(enjocErrors::err_creating_file_for_write,strFile.c_str ());}
		fclose (pFile);

		//Set file
		m_strFile = strFile;

		if (bAddLogWhenCreateFile == true)
			Append((std::wstring)L"Log file created");
	}
}