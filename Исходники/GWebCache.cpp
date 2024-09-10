void GWebCache::WriteWebCacheURLsToFile()
{
	UINT i;

	// Open the hosts.dat file for writing...if the open fails, then who cares
	CStdioFile file;
	MakeSureDirectoryPathExists("Host Cache\\");
	if(file.Open("Host Cache\\web_cache_urls.txt",CFile::modeCreate|CFile::modeWrite|CFile::typeText|CFile::shareDenyNone)==FALSE)
	{
		return;
	}

	for(i=0;i<v_web_cache_urls.size();i++)
	{
		file.WriteString(v_web_cache_urls[i].c_str());
		file.WriteString("\n");
	}

	file.Close();
}