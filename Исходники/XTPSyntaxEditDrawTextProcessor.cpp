int CXTPSyntaxEditDrawTextProcessor::ExpandChars(LPCTSTR pszChars, CString& strBuffer,
									  int nDispPos, BOOL bEnableWhiteSpace)
{
	m_arExpandCharsBuffer.RemoveAll();

	for (LPCTSTR p = pszChars; p && *p != 0; p = _tcsinc(p))
	{
		if (*p == _T('\t'))
		{
			int nSpaces = m_nTabSize - (nDispPos % m_nTabSize);

			BOOL bFirstWhiteSpaceChar = bEnableWhiteSpace;
			for (int i = 0; i < nSpaces; i++)
			{
				if (bFirstWhiteSpaceChar)
				{
					//strBuffer += (TCHAR)(unsigned char)0xBB;
					m_arExpandCharsBuffer.AddData((TCHAR)(unsigned char)0xBB);
					bFirstWhiteSpaceChar = FALSE;
				}
				else
				{
					//strBuffer += _T(' ');
					m_arExpandCharsBuffer.AddData(_T(' '));
				}
			}
			nDispPos += nSpaces;
		}
		else
		{
			if (bEnableWhiteSpace && *p == _T(' '))
				m_arExpandCharsBuffer.AddData((TCHAR)(unsigned char)0xB7); //strBuffer += (TCHAR)(unsigned char)0xB7;
			else
			{
				m_arExpandCharsBuffer.AddData(*p); //strBuffer += *p;

				#ifndef _UNICODE
				if (_tcsinc(p) > p + 1)
				{
					ASSERT(_tcsinc(p) == p + 2);
					m_arExpandCharsBuffer.AddData(*(p+1));
				}
				#endif
			}
#ifdef XTP_FIXED
// multi-byte character : display length  2
// single-byte character : display length 1
			if (isleadbyte( *p ))
				nDispPos += 2;
			else
				nDispPos++;
#else
			nDispPos++;
#endif
		}
	}
	m_arExpandCharsBuffer.AddData(_T('\0'));

	strBuffer = m_arExpandCharsBuffer.GetData();

	return nDispPos;
}