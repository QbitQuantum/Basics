bool CmbFileFind::FindFile(CString path)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT]; 

	const TCHAR* cstr = (LPCTSTR)path;
	_splitpath_s(cstr, (char *)drive, _MAX_DRIVE, (char *)dir, _MAX_DIR, (char *)fname, _MAX_FNAME, (char *)ext, _MAX_EXT);

	char root[MAX_PATH];
	_makepath_s(root, sizeof(root), drive, dir, 0, 0);
	m_rootPath = root;

	if (m_nextInfo)
	{
		delete m_nextInfo;
	}
	m_nextInfo = new WIN32_FIND_DATA;
	m_fileListHandle = ::FindFirstFile(path, m_nextInfo);

	return m_fileListHandle != INVALID_HANDLE_VALUE;	
}