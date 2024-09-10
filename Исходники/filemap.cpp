/**
* Scans a sound folder for non-WMA files.
* @param srcPath Path to scan.
*/
void FileMap::scanSoundFolder(const std::string &srcPath)
{
	WIN32_FIND_DATAA data;
	string srcPathSearch = srcPath + "\\*";
	HANDLE hFind = FindFirstFileA(srcPathSearch.c_str(), &data);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		// No files found.
		return;
	}

	do
	{
		// NOTE: This will hide *all* files starting with '.'.
		// SADX doesn't use any files starting with '.',
		// so this won't cause any problems.
		if (data.cFileName[0] == '.')
		{
			continue;
		}
		else if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && stricmp(".wma", PathFindExtensionA(data.cFileName)))
		{
			// Create the mod filename and original filename.
			string modFile = srcPath + "\\" + string(data.cFileName);
			transform(modFile.begin(), modFile.end(), modFile.begin(), ::tolower);
			char pathcstr[MAX_PATH];
			strncpy(pathcstr, modFile.c_str(), sizeof(pathcstr));
			PathRenameExtensionA(pathcstr, ".wma");
			string origFile = pathcstr;
			m_fileMap[origFile] = { modFile };
		}
	} while (FindNextFileA(hFind, &data) != 0);
	FindClose(hFind);
}