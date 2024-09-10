	bool ZipFile::init(const std::wstring &p_ResFileName)
	{
		end();

		_wfopen_s(&m_File, p_ResFileName.c_str(), _T("rb"));
		if (!m_File)
			return false;

		// Assuming no extra comment at the end, read the whole end record.
		TZipDirHeader dh;

		fseek(m_File, -(int)sizeof(dh), SEEK_END);
		long dhOffset = ftell(m_File);
		memset(&dh, 0, sizeof(dh));
		fread(&dh, sizeof(dh), 1, m_File);

		// Check
		if (dh.sig != TZipDirHeader::SIGNATURE)
			return false;

		// Go to the beginning of the directory.
		fseek(m_File, dhOffset - dh.dirSize, SEEK_SET);

		// Allocate the data buffer, and read the whole thing.
		m_DirData = new char[dh.dirSize + dh.nDirEntries*sizeof(*m_AppDir)];
		if (!m_DirData)
			return false;
		memset(m_DirData, 0, dh.dirSize + dh.nDirEntries*sizeof(*m_AppDir));
		fread(m_DirData, dh.dirSize, 1, m_File);

		// Now process each entry.
		char *pfh = m_DirData;
		m_AppDir = (const TZipDirFileHeader **)(m_DirData + dh.dirSize);

		bool success = true;

		for (int i = 0; i < dh.nDirEntries && success; i++)
		{
			TZipDirFileHeader &fh = *(TZipDirFileHeader*)pfh;

			// Store the address of nth file for quicker access.
			m_AppDir[i] = &fh;

			// Check the directory entry integrity.
			if (fh.sig != TZipDirFileHeader::SIGNATURE)
				success = false;
			else
			{
				pfh += sizeof(fh);

				// Convert UNIX slashes to DOS backlashes.
				for (int j = 0; j < fh.fnameLen; j++)
				if (pfh[j] == '/')
					pfh[j] = '\\';

				char fileName[_MAX_PATH];
				memcpy(fileName, pfh, fh.fnameLen);
				fileName[fh.fnameLen] = 0;
				_strlwr_s(fileName, _MAX_PATH);
				std::string spath = fileName;
				m_ZipContentsMap[spath] = i;

				// Skip name, extra and comment fields.
				pfh += fh.fnameLen + fh.xtraLen + fh.cmntLen;
			}
		}
		if (!success)
		{
			SAFE_DELETE_ARRAY(m_DirData);
		}
		else
		{
			m_NumEntries = dh.nDirEntries;
		}

		return success;
	}