CFileAccess::CFileAccess(const TCHAR* FileName)
{
	m_FileName = new TCHAR[_tcslen(FileName) + 1];
	m_Journal.FileName = new TCHAR[_tcslen(FileName) + 5];
	_tcscpy_s(m_FileName, _tcslen(FileName) + 1, FileName);
	_tcscpy_s(m_Journal.FileName, _tcslen(FileName) + 5, FileName);
	_tcscat_s(m_Journal.FileName, _tcslen(FileName) + 5, _T(".jrn"));

	m_ReadOnly = false;
	m_LastSize = 0;
	m_Size = 0;
	m_Journal.Use = false;
	m_Journal.hFile = 0;
	m_Journal.BufUse = 0;

	m_LastAllocTime = _time32(NULL);
}