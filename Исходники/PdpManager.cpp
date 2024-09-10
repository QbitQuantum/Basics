//=============================================================================
//=============================================================================
std::string CPdpManager::GetFilePath(unsigned  int idx )const
{
	string Path = GetProjectPath();
	string PathFile;

	vector<char> absPath;
	Path += GetFileName(idx);

	absPath.resize(MAX_PATH+1);
	if (0 == _fullpath(&(absPath[0]), Path.c_str(),absPath.size()))
		return "";

	return &(absPath[0]);
}