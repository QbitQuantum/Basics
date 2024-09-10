//PRIVATE: Delete file with index 0 et rename all file i to i-1 until m_filenr-1
//After this function, the file with index m_filenr-1 is free (it doesn't exist)
void CLog::renameFiles(const wchar_t *root_filename)
{
	//We remove the file 0
	std::wstring src;
	src=root_filename;
	src+=L"0.log";

#ifdef WIN32
	_wremove(src.c_str());
#else
	remove(utilStringNarrow(src).c_str());
#endif

	std::wstring dest;
	wchar_t isrc[5];
	wchar_t idest[5];
#ifdef WIN32
	struct _stat results;
#else
	struct stat results;
#endif

	//For all file until m_filenr-1
	// 1 become 0
	// 2 become 1
	//i+1 become i
	//m_filenr-1 become m_filenr-2
	for(int i=0;i<m_filenr;i++)
	{
		swprintf_s(isrc,5,L"%d",i+1);
		swprintf_s(idest,5,L"%d",i);

		//if the source does not exist, we stop
		src=root_filename;
		src+=isrc;
		src+=L".log";

#ifdef WIN32
		if (_wstat(src.c_str(), &results) != 0)
			break;
#else
		if (stat(utilStringNarrow(src).c_str(), &results) != 0)
			break;
#endif
		dest=root_filename;
		dest+=idest;
		dest+=L".log";

		//Rename of the file
#ifdef WIN32
		_wrename(src.c_str(),dest.c_str());
#else
		rename(utilStringNarrow(src).c_str(),utilStringNarrow(dest).c_str());
#endif
	}
}