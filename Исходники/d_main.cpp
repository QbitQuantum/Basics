//
// denis - BaseFileSearchDir
// Check single paths for a given file with a possible extension
// Case insensitive, but returns actual file name
//
std::string BaseFileSearchDir(std::string dir, std::string file, std::string ext, std::string hash = "")
{
	std::string found;

	if(dir[dir.length() - 1] != PATHSEPCHAR)
		dir += PATHSEP;

	std::transform(hash.begin(), hash.end(), hash.begin(), toupper);
	std::string dothash = ".";
	if(hash.length())
		dothash += hash;
	else
		dothash = "";

	// denis - list files in the directory of interest, case-desensitize
	// then see if wanted wad is listed
#ifdef UNIX
	// denis - todo -find a way to deal with dir="./" and file="DIR/DIR/FILE.WAD"
	struct dirent **namelist = 0;
	int n = scandir(dir.c_str(), &namelist, 0, alphasort);

	for(int i = 0; i < n && namelist[i]; i++)
	{
		std::string d_name = namelist[i]->d_name;

		M_Free(namelist[i]);

		if(!found.length())
		{
			if(d_name == "." || d_name == "..")
				continue;

			std::string tmp = d_name;
			std::transform(tmp.begin(), tmp.end(), tmp.begin(), toupper);

			if(file == tmp || (file + ext) == tmp || (file + dothash) == tmp || (file + ext + dothash) == tmp)
			{
				std::string local_file = (dir + d_name).c_str();
				std::string local_hash = W_MD5(local_file.c_str());

				if(!hash.length() || hash == local_hash)
				{
					found = d_name;
				}
				else if(hash.length())
				{
					Printf (PRINT_HIGH, "WAD at %s does not match required copy\n", local_file.c_str());
					Printf (PRINT_HIGH, "Local MD5: %s\n", local_hash.c_str());
					Printf (PRINT_HIGH, "Required MD5: %s\n\n", hash.c_str());
				}
			}
		}
	}

	M_Free(namelist);
#else
	if(dir[dir.length() - 1] != PATHSEPCHAR)
		dir += PATHSEP;

	std::string all_ext = dir + "*";
	//all_ext += ext;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(all_ext.c_str(), &FindFileData);
	DWORD dwError = GetLastError();

	if (hFind == INVALID_HANDLE_VALUE)
	{
		Printf (PRINT_HIGH, "FindFirstFile failed for %s\n", all_ext.c_str());
		Printf (PRINT_HIGH, "GetLastError: %d\n", dwError);
		return "";
	}

	while (true)
	{
		if(!FindNextFile(hFind, &FindFileData))
		{
			dwError = GetLastError();

			if(dwError != ERROR_NO_MORE_FILES)
				Printf (PRINT_HIGH, "FindNextFile failed. GetLastError: %d\n", dwError);

			break;
		}

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		std::string tmp = FindFileData.cFileName;
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), toupper);

		if(file == tmp || (file + ext) == tmp || (file + dothash) == tmp || (file + ext + dothash) == tmp)
		{
			std::string local_file = (dir + FindFileData.cFileName).c_str();
			std::string local_hash = W_MD5(local_file.c_str());

			if(!hash.length() || hash == local_hash)
			{
				found = FindFileData.cFileName;
				break;
			}
			else if(hash.length())
			{
				Printf (PRINT_HIGH, "WAD at %s does not match required copy\n", local_file.c_str());
				Printf (PRINT_HIGH, "Local MD5: %s\n", local_hash.c_str());
				Printf (PRINT_HIGH, "Required MD5: %s\n\n", hash.c_str());
			}
		}
	}

	FindClose(hFind);
#endif

	return found;
}