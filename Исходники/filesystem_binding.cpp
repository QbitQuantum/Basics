	void FilesystemBinding::GetDocumentsDirectory(const ValueList& args, KValueRef result)
	{
#ifdef OS_WIN32
		wchar_t path[MAX_PATH];
		if (!SHGetSpecialFolderPathW(NULL, path, CSIDL_PERSONAL, FALSE))
			throw ValueException::FromString("Could not get Documents path.");
		std::string dir(::WideToUTF8(path));

#elif OS_OSX
		std::string dir([[NSSearchPathForDirectoriesInDomains(
			NSDocumentDirectory, NSUserDomainMask, YES)
			objectAtIndex: 0] UTF8String]);

#elif OS_LINUX
		passwd* user = getpwuid(getuid());
		std::string homeDirectory = user->pw_dir;
		std::string dir(FileUtils::Join(homeDirectory.c_str(), "Documents", NULL));
		if (!FileUtils::IsDirectory(dir))
		{
			dir = homeDirectory;
		}
#endif
		ti::File* file = new ti::File(dir);
		result->SetObject(file);
	}