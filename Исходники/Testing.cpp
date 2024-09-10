// Given a directory remove the files located within it and then the directory itself
void removeDirectory(std::string directory) {
	std::string CWD = getCurrentDirectory();
	directory = CWD + DIR_SEPARATOR + directory;

	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile((directory + DIR_SEPARATOR + "*").c_str(), &data);
	if (h != NULL) {
		SetFileAttributes(directory.c_str(), FILE_ATTRIBUTE_NORMAL);
		FindNextFile(h, &data); // ..
		FindNextFile(h, &data); // .
		do {
			std::string filename = directory + DIR_SEPARATOR + data.cFileName;
			if (!SetFileAttributes(filename.c_str(), FILE_ATTRIBUTE_NORMAL)) {
				logEvent(ERROR,filename + ": " + ConvertLastErrorToString());
			}
			int result = _unlink(filename.c_str());
			if (result != 0) {
				logEvent(ERROR, filename + ": " + ConvertLastErrorToString());
			}
		} while (FindNextFile(h,&data));
		FindClose(h);
	}
	_rmdir(directory.c_str());

}