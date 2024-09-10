std::string PathRemoveFolder(const std::string& path)
{
	char* strBuf = new char[path.size() + 1];
	memcpy(strBuf, path.c_str(), path.size());
	strBuf[path.size()] = 0;
	PathStripPathA(strBuf);

	std::string retPath(strBuf);

	delete [] strBuf;

	return retPath;
}