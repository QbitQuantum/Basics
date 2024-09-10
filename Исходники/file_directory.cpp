FDirectory::FDirectory(const char * directory)
: FResourceFile(NULL, NULL)
{
	FString dirname;

	#ifdef _WIN32
		directory = _fullpath(NULL, directory, _MAX_PATH);
	#else
		// Todo for Linux: Resolve the path befire using it
	#endif
	dirname = directory;
	dirname.ReplaceChars('\\', '/');
	if (dirname[dirname.Len()-1] != '/') dirname += '/';
	Filename = copystring(dirname);
}