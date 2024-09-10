SFMFile::SFMFile(LPCSTR lpszPathName, char cCommentChar, BOOL bForWriting)
:	m_forWriting(bForWriting),
	m_stream(lpszPathName, ios::in | ios::nocreate),
	m_bNothingLogged(TRUE),
	m_cCommentChar(cCommentChar),
	m_bDidOutputSkippedCommentNotice(FALSE)
{
	USES_CONVERSION;
	m_pathName = A2CT(lpszPathName); // used when reporting errors
}