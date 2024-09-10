UINT COXFileChanger::Run()
	// --- In      :
	// --- Out     : 
	// --- Returns : occurences of found match or replacement
	// --- Effect  : perform search/replace
	{
	int  M = PtrToInt(m_pSearch->GetSize());
	// ... search text/binary length
	int	 M_1 = M - 1;
	// ... array max subscript
	int	 MM_1 = M + M_1;
	// ... i shift value when found
	int	 n = 0;
	// ... actual bytes read from the file at one time
	int	 i = 0;
	// ... scanning position pointer of file buffer
	int	 j = 0;
	// ... scanning position pointer of search text/binary
	int	 w = 0;
	// ... write position pointer in the loaded file buffer
	int	 t = 0;
	// ... temp value
	int	 skip[255];					
	// ... skip array for each byte value

	LONG lPos0 = 0;
	// ... file position of the current buffer[0]
	LONG nCurInPos = 0;
	// ... loading position of the input file
	LONG nInPos = 0;
	// ... match found position of the input file
	LONG nCurOutPos = 0;
	// ... writing position of the output file
	LONG nOutPos = 0;
	// ... replace text/binary position of the output file
	LONG nChPos = 0;
	// ... position of prev/next char for whole word match
	LONG nChPosMax = 0;
	// ... maximum file position of prev/next char for whole word match
	UINT nResult = 0;
	// ... match occurence
	BYTE* pBuffer = NULL;	
	// ... file buffer

	BOOL bEOF = FALSE;
	// ... end of file
	BOOL bContinue = TRUE;
	// ... default bContinue value
	BOOL bReplace = GetFlag(m_nFlagReplace);
	// ... Replace() (TRUE) or Search() (FALSE)
	BOOL bText = GetFlag(m_nFlagText);
	// ... whether text search
	BOOL bMatchCase = (!bText || GetFlag(m_nFlagMatchCase));
	// ... whether case-insensitive
	BOOL bWholeWord = (bText && GetFlag(m_nFlagWholeWord));
	// ... whether whole word
	char ch = '\0';
	// ... prev/next char for whole word match
	CString sSafeStack;
	// Increases the stack size
	
	if (M == 0)
		{
		TRACE0("COXFileChanger::Run(): aborted: zero length search text/binary encountered.\r\n");
		return 0;
		}

	if (m_nBufferSize < M)
		{
		TRACE0("COXFileChanger::Run(): aborted: length of search text/binary exceeds upper limit.\r\n");
		return 0;
		}

	// Initialize skip array
	for (j = 0; j < 256; j++) 
		skip[j] = M;
	for (j = 0, t = M; j < M; j++) 
		skip[m_pSearch->GetAt(j)] = --t;
	if (!bMatchCase) 
		for (j = 0, t = M; j < M; j++) 
			skip[m_pSearchOppositeCase->GetAt(j)] = --t;
		
	try
		{
		// Alllocate the buffer
		pBuffer = new BYTE[m_nBufferSize];

		OpenFiles();
		nChPosMax = (LONG) m_pFileIn->GetLength() - 1;
		while (!bEOF && (n = m_pFileIn->Read(pBuffer, m_nBufferSize)) > 0)
			{
			bEOF = (n < m_nBufferSize);
			if (!bContinue && bReplace)
				{ 
				// Cycle until all remaining contents are copied
				m_pFileOut->Write(pBuffer, n);
				continue;
				}

			if (!bContinue || n < M) 
				break;
			i = - M; w = 0;
			while (bContinue)
				{
				// search one occurence
				for (i += MM_1, j = M_1; 0 <= j && i < n; i--, j--)
					{
					while (pBuffer[i] != m_pSearch->GetAt(j) && (bMatchCase || 
						   pBuffer[i] != m_pSearchOppositeCase->GetAt(j)))
						{
						t = skip[pBuffer[i]];
						i += __max(M - j, t);
						if (n <= i)	
							{
							i++; 
							break;
							}
						j = M_1;
						}
					}
				// out of buffer boundary
				if (n <= i)
					{
					if (bReplace) 
						m_pFileOut->Write(pBuffer + w, (bEOF ? n : i - M_1) - w);
					if (!bEOF) 
						lPos0 = (LONG) m_pFileIn->Seek(i - M_1 - n, CFile::current);
					break;
					}

				i++;
				nCurInPos = (LONG) m_pFileIn->GetPosition();
				nInPos = lPos0 + i;
				
				// test wholeword match
				if (bWholeWord)
					{
					nChPos = i - 1;
					for (t = 0; t < 2; t++)
						{
						// look in buffer first
						if (0 <= nChPos && nChPos < n)
							ch = *(pBuffer + nChPos);
						else
							{ // look in the file
							nChPos += lPos0;
							if (0 <= nChPos && nChPos <= nChPosMax)
								{
								m_pFileIn->Seek(nChPos, CFile::begin);
								m_pFileIn->Read(&ch, 1);
								}
							else 
								// beginning or the end of the file
								ch = ' ';
							}
						if (isalnum(ch)) 
							break;
						nChPos = i + M;
						}
					if (t < 2)
						{
						m_pFileIn->Seek(nCurInPos, CFile::begin);
						i -= M_1;
						continue;
						}
					}

				// found one match
				bContinue = GetFlag(m_nFlagAll);
				m_pFileIn->Seek(nInPos, CFile::begin);
				if (bReplace)
					{
					if (OnPreReplace(m_pFileIn, nInPos, bContinue))
						{
						nResult++;
						m_pFileOut->Write(pBuffer + w, i - w);
						nOutPos = (LONG) m_pFileOut->GetPosition();
						m_pFileOut->Write(m_pReplace->GetData(), PtrToUint(m_pReplace->GetSize()));
						w = i + M;
						nCurOutPos = (LONG) m_pFileOut->GetPosition();
						m_pFileOut->Seek(nOutPos, CFile::begin);
						OnPostReplace(m_pFileOut, nOutPos);
						m_pFileOut->Seek(nCurOutPos, CFile::begin);
						}
					if (!bContinue)	
						m_pFileOut->Write(pBuffer + w, n - w);
					}
				else
					{
					if (OnFound(m_pFileIn, nInPos, bContinue))
						nResult++;
					}
				m_pFileIn->Seek(nCurInPos, CFile::begin);
				}
			}
		CloseFiles();
		}
	catch (...)
		{
		if (!GetFlag(m_nFlagUseCFile))
			{
			CString sTempFileName = m_pFileOut->GetFilePath();
			m_pFileIn->Abort();
			m_pFileOut->Abort();
			if (bReplace && GetFlag(m_nFlagOverwrite) && !sTempFileName.IsEmpty())
				::DeleteFile(sTempFileName);
			}
		m_pFileIn = NULL;
		m_pFileOut = NULL;
		delete[] pBuffer;
		pBuffer = NULL;
		throw;
		}

	// Clean up
	delete[] pBuffer;
	pBuffer = NULL;
	m_pFileIn = NULL;
	m_pFileOut = NULL;
	return nResult;
	}