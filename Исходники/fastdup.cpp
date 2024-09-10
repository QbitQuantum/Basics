void FastDup::AddDirectoryTree(const char *path)
{
	std::string v = path;
	char tmp[PATH_MAX+1];
	
	if (path[0] != '/')
	{
		char cwd[PATH_MAX + 1];
		if (!getcwd(cwd, PATH_MAX + 1))
			throw std::runtime_error("Unable to get current directory");
		
		v = PathMerge(cwd, v);
	}
	
	PathResolve(tmp, sizeof(tmp), v.c_str());
	
	if (!DirectoryExists(tmp))
		throw std::runtime_error("Path does not exist or is not a directory");
	
	DirList.push_back(tmp);
}