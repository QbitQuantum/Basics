void FileImpl::linkToImpl(const std::string& path, int type) const
{
	poco_assert (!_path.empty());

	if (type == 0)
	{
		if (CreateHardLinkA(path.c_str(), _path.c_str(), NULL) == 0)
			handleLastErrorImpl(_path);
	}
	else
	{
#if _WIN32_WINNT >= 0x0600 && defined(SYMBOLIC_LINK_FLAG_DIRECTORY)
		DWORD flags = 0;
		if (isDirectoryImpl()) flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
#ifdef SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE
		flags |= SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;
#endif
		if (CreateSymbolicLinkA(path.c_str(), _path.c_str(), flags) == 0)
			handleLastErrorImpl(_path);
#else
		throw Poco::NotImplementedException("Symbolic link support not available in used version of the Windows SDK")
#endif

	}
}