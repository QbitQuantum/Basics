const char *iTunesLibrary::GetMusicLibraryXMLFileName(std::string &buf)
{
#if defined(WIN32)
	TCHAR szPath[_MAX_PATH];
    LPITEMIDLIST pidl;
	IMalloc *pMalloc;

	szPath[0] = '\0';
	SHGetMalloc( &pMalloc );
    if(SHGetSpecialFolderLocation(NULL, CSIDL_MYMUSIC, &pidl) == S_OK)
    { 
        SHGetPathFromIDList(pidl,szPath);
        pMalloc->Free(pidl);
    }
    pMalloc->Release();

	buf = szPath;
	buf += "\\";
	buf += ITUNES_XML_DIR_NAME;
	buf += "\\";
	buf += ITUNES_XML_FILE_NAME;
#else
#endif
	return buf.c_str();
}