CHexFileList::CHexFileList(UINT nStart, LPCTSTR lpszSection, int nSize, int nMaxDispLen /*= AFX_ABBREV_FILENAME_LEN*/)
		: CRecentFileList(nStart, lpszSection, _T("File%d"), nSize, nMaxDispLen)
{
	// Set up the default values
	// Note: the default scheme should always be empty in which case a file extension
	// scheme is searched for then a scheme based on current char set is used
	// Also note that some values are set in the default string here just to show the fields
	// and are overwritten with the current default value from the registry below.
	// The entries correspond to the parm_num enum as:
	//               CMD                           SEL     CS DOC  GRP                        FORMAT
	//               | TOP    LEFT   BOTTOM RIGHT  |-| POS  HL| COLS   FONT    HEIGHT         |
	//               | |      |      |      |      | | | MK  DISPLAY OFF       |  OEMFONT  HEIGHT
	default_data_ = "1|-30000|-30000|-30000|-30000|0|0|0|0||||0|16|4|0|Courier|16|Terminal|18|default";
	SetDefaults();

	ASSERT(AfxGetMainWnd() != NULL);

	// Get user's Application Data folder
	if (!::GetDataPath(filename_))
		return;

	filename_ += CString(lpszSection);   // append file name

	// Create HexEdit folder within that
	if (!MakeSureDirectoryPathExists(filename_))
	{
		filename_.Empty();
		return;
	}

	size_t capacity = 256;    // Initial vector capacities
#ifdef _DEBUG
	capacity = 1;     // Force reallocation sooner in debug to catch bad iterator bugs
#else
	// Work out roughly how many recent files we have from the recent file list's file size
	struct _stat stat;
	if (::_stat(filename_, &stat) != -1)
		capacity = stat.st_size / 100;  // Most lines of the text file are longer than 100 chars
#endif
	name_.reserve(capacity);
	hash_.reserve(capacity);
	opened_.reserve(capacity);
	open_count_.reserve(capacity);
	data_.reserve(capacity);

	ver_ = -1;
}