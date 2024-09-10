BOOL CFileTextLines::Load(const CString& sFilePath, int lengthHint /* = 0*/)
{
	m_LineEndings = EOL_AUTOLINE;
	m_UnicodeType = CFileTextLines::AUTOTYPE;
	RemoveAll();
	m_endings.clear();
	if(lengthHint != 0)
	{
		Reserve(lengthHint);
	}

	if (PathIsDirectory(sFilePath))
	{
		m_sErrorString.Format(IDS_ERR_FILE_NOTAFILE, (LPCTSTR)sFilePath);
		return FALSE;
	}

	if (!PathFileExists(sFilePath))
	{
		//file does not exist, so just return SUCCESS
		return TRUE;
	}

	CAutoFile hFile = CreateFile(sFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (!hFile)
	{
		SetErrorString();
		return FALSE;
	}

	LARGE_INTEGER fsize;
	if (!GetFileSizeEx(hFile, &fsize))
	{
		SetErrorString();
		return false;
	}
	if (fsize.HighPart)
	{
		// file is way too big for us
		m_sErrorString.LoadString(IDS_ERR_FILE_TOOBIG);
		return FALSE;
	}

	// If new[] was done for type T delete[] must be called on a pointer of type T*,
	// otherwise the behavior is undefined.
	// +1 is to address possible truncation when integer division is done
	wchar_t* pFileBuf = new wchar_t[fsize.LowPart/sizeof(wchar_t) + 1];
	DWORD dwReadBytes = 0;
	if (!ReadFile(hFile, pFileBuf, fsize.LowPart, &dwReadBytes, NULL))
	{
		delete [] pFileBuf;
		SetErrorString();
		return FALSE;
	}
	if (m_UnicodeType == CFileTextLines::AUTOTYPE)
	{
		m_UnicodeType = this->CheckUnicodeType(pFileBuf, dwReadBytes);
	}
	if (m_LineEndings == EOL_AUTOLINE)
	{
		m_LineEndings = CheckLineEndings(pFileBuf, min(10000, dwReadBytes));
	}
	hFile.CloseHandle();

	if (m_UnicodeType == CFileTextLines::BINARY)
	{
		m_sErrorString.Format(IDS_ERR_FILE_BINARY, (LPCTSTR)sFilePath);
		delete [] pFileBuf;
		return FALSE;
	}

	// we may have to convert the file content
	if ((m_UnicodeType == UTF8)||(m_UnicodeType == UTF8BOM))
	{
		int ret = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pFileBuf, dwReadBytes, NULL, 0);
		wchar_t * pWideBuf = new wchar_t[ret];
		int ret2 = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pFileBuf, dwReadBytes, pWideBuf, ret);
		if (ret2 == ret)
		{
			delete [] pFileBuf;
			pFileBuf = pWideBuf;
			dwReadBytes = ret2;
		} else
			delete [] pWideBuf;
	}
	else if (m_UnicodeType == ASCII)
	{
		int ret = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCSTR)pFileBuf, dwReadBytes, NULL, 0);
		wchar_t * pWideBuf = new wchar_t[ret];
		int ret2 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCSTR)pFileBuf, dwReadBytes, pWideBuf, ret);
		if (ret2 == ret)
		{
			delete [] pFileBuf;
			pFileBuf = pWideBuf;
			dwReadBytes = ret2;
		}
		else
			delete [] pWideBuf;
	}
	// fill in the lines into the array
	wchar_t * pTextBuf = pFileBuf;
	wchar_t * pLineStart = pFileBuf;
	if (m_UnicodeType == UNICODE_LE)
	{
		// UTF16 have two bytes per char
		dwReadBytes/=2;
	}
	if ((m_UnicodeType == UTF8BOM)||(m_UnicodeType == UNICODE_LE))
	{
		// ignore the BOM
		++pTextBuf;
		++pLineStart;
		--dwReadBytes;
	}

	for (DWORD i = 0; i<dwReadBytes; ++i)
	{
		if (*pTextBuf == '\r')
		{
			if ((i + 1) < dwReadBytes)
			{
				if (*(pTextBuf+1) == '\n')
				{
					// crlf line ending
					CString line(pLineStart, (int)(pTextBuf-pLineStart));
					Add(line, EOL_CRLF);
					pLineStart = pTextBuf+2;
					++pTextBuf;
					++i;
				}
				else
				{
					// cr line ending
					CString line(pLineStart, (int)(pTextBuf-pLineStart));
					Add(line, EOL_CR);
					pLineStart =pTextBuf+1;
				}
			}
		}
		else if (*pTextBuf == '\n')
		{
			// lf line ending
			CString line(pLineStart, (int)(pTextBuf-pLineStart));
			Add(line, EOL_LF);
			pLineStart =pTextBuf+1;
		}
		++pTextBuf;
	}
	if (pLineStart < pTextBuf)
	{
		CString line(pLineStart, (int)(pTextBuf-pLineStart));
		Add(line, EOL_NOENDING);
		m_bReturnAtEnd = false;
	}
	else
		m_bReturnAtEnd = true;

	delete [] pFileBuf;

	return TRUE;
}