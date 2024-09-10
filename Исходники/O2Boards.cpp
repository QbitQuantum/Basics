// ---------------------------------------------------------------------------
//	Load()
//	2channel.brd形式のファイルから読み込む
// ---------------------------------------------------------------------------
bool
O2Boards::
Load(const wchar_t *fn)
{
	const wchar_t *filename = fn ? fn : filepath.c_str();

#ifdef _WIN32
	struct _stat st;
	if (_tstat(filename, &st) == -1)
		return false;
#else /** VC++ function equivalent */
	struct stat st;
	string unixFilename;
	FromUnicode(_T(DEFAULT_XML_CHARSET), filename, unixFilename);
	if (_tstat(unixFilename.c_str(), &st) == -1)
		return false;
#endif


	if (st.st_size == 0)
		return false;

	FILE *fp;
#ifdef _WIN32
	if (_tfopen_s(&fp, filename, _T("rb")) != 0)
		return false;
#else /** VC++ _s function equivalent */
	if (fopen_s(&fp, unixFilename.c_str(), "rb") != 0)
		return false;
#endif

	string buff;
	buff.resize(st.st_size);
	fread(&buff[0], 1, st.st_size, fp);
	fclose(fp);

	wstring unicode;
	if (!ToUnicode(L"shift_jis", buff, unicode))
		return false;

	BoardsLock.Lock();
	boards.clear();
	BoardsLock.Unlock();

	std::wstringstream ss(unicode);
	std::wstring line;
	std::wstring category;

	std::getline(ss, line); //skip first line
	while (!ss.fail()) {
		std::getline(ss, line);
		if (line.empty())
			continue;
		if (*(line.end()-1) == L'\r')
			line.erase(line.end()-1);

		boost::wregex regex(L"^\t?([^[\t]+)\t([^[\t]+)(?:\t([^[\t]+))?$");
		boost::wsmatch m;
		boost::regex_match(line, m, regex);

		if (line[0] != L'\t') {
			category = m.str(1);
		}
		else {
			const wchar_t *domain = host2domain(m.str(1).c_str());
			if (!domain)
				continue;
			O2Board brd;
			brd.bbsname = m.str(2);
			brd.title = m.str(3);
			brd.category = category;
			brd.host = m.str(1);
			brd.domain = domain;

			BoardsLock.Lock();
			O2BoardArrayIt it = std::find(boards.begin(), boards.end(), brd);
			if (it == boards.end())
				boards.push_back(brd);
			BoardsLock.Unlock();
		}
	}
	LastModified = st.st_mtime;

	/*
	TRACEA("st.st_mtime:");
	TRACEA(ctime(&st.st_mtime));
	TRACEA("bbsmenu_lastmodified:");
	TRACEA(ctime(&bbsmenu_lastmodified));
	*/

	return true;
}