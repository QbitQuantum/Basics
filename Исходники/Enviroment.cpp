std::vector<FileListItem> Enviroment::getFilesInDirectory(const std::string& directory)
{
	HANDLE dir;
	WIN32_FIND_DATAA file_data;
	std::vector<FileListItem> out;

	if ((dir = FindFirstFileA((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
	{
		return std::vector<FileListItem>();
	}

	do
	{
		const std::string file_name = file_data.cFileName;
		const std::string full_file_name = file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
		{
			continue;
		}

		FileListItem item;
		size_t lastindex = full_file_name.find_last_of(".");
		if (lastindex != std::string::npos)
		{
			item.Filename = full_file_name.substr(0, lastindex);
		}
		else
		{
			item.Filename = full_file_name;
		}

		if (is_directory)
		{
			item.Filename = "[" + item.Filename + "]";
		}

		item.Extension = is_directory ? "" : PathFindExtensionA(file_data.cFileName);
		item.Size = is_directory ? 0 : (file_data.nFileSizeHigh * (MAXDWORD + 1) + file_data.nFileSizeLow) / 1024 ; //To kilobytes
		item.CreationDate = file_data.ftCreationTime;

		out.push_back(item);
	} while (FindNextFileA(dir, &file_data));

	FindClose(dir);
	return out;
}