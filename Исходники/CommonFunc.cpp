/// Make dump file name
tstring GetDumpFilename()
{
	TCHAR szFilename[_MAX_PATH];

	for ( int i=0; i<100; ++i )
	{
		SPrintf(szFilename, _MAX_PATH, TEXT("C:\\ZViewer%s_%d.dmp"), g_strVersion.c_str(), i);

		if ( 0 != _taccess(szFilename, 00) )	///< file not exist
		{
			break;
		}
	}
	tstring strDumpFilename = szFilename;
	return strDumpFilename;
}