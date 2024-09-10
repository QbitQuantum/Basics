bool FUFileManager::MakeDirectory(const fstring& directory)
{
	FUUri uri(directory);
	fstring absoluteDirectory = uri.GetAbsolutePath();

#ifdef WIN32
	if (_mkdir(TO_STRING(absoluteDirectory).c_str()) == 0) return true;
	errno_t err; _get_errno(&err);
	if (err == EEXIST) return true;
#elif defined(LINUX)
	if (mkdir(TO_STRING(absoluteDirectory).c_str(), ~0u) == 0) return true; // I think this means all permissions..
#elif defined(__APPLE__)
	fm::string _fname = TO_STRING(directory);
	OSErr err = AddFolderDescriptor('extn', 0, 'relf', 0, 0, 0,(const unsigned char*) _fname.c_str(), false);
#endif // WIN32

	return false;
}