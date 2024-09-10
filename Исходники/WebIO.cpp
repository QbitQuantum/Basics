bool WebIO::GetDirectory(std::string &directory)
{
	directory.clear();

	DWORD size = MAX_PATH;
	char currentDir[MAX_PATH] = { 0 };

	if (FtpGetCurrentDirectoryA(WebIO::m_hConnect, currentDir, &size) == TRUE)
	{
		directory.append(currentDir, size);
		return true;
	}

	return false;
}