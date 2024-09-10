	return !(attribute & FILE_ATTRIBUTE_DIRECTORY);
}

bool FileDispatcher::IsValid(const string& file)
{
	DWORD attributes = GetFileAttributesA(file.c_str());
	return attributes != INVALID_FILE_ATTRIBUTES;
}

vector<string> FileDispatcher::TraverseDirectory(string& const basepath)
{
	vector<string> files_and_directories;

	string path = basepath + "\\*";
	WIN32_FIND_DATAA find_data;
	HANDLE find_data_handle = FindFirstFileA(path.c_str(), &find_data);

	if (find_data_handle == INVALID_HANDLE_VALUE) {
		return files_and_directories;
	}

	while (true) {
		if (string(find_data.cFileName) != "." &&
			string(find_data.cFileName) != "..") {
			files_and_directories.push_back(find_data.cFileName);
		}
		if (!FindNextFileA(find_data_handle, &find_data)) break;
	}
	FindClose(find_data_handle);
	return files_and_directories;
