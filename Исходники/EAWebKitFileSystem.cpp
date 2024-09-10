bool FileSystemDefault::DeleteDirectory(const char* path)
{
    // The following is copied from the EAIO package.
    // This code is not smart enough to do a recursive delete, but the one in EAIO is.
	// We need to implement a recursive delete.

    // Windows doesn't like it when the directory path ends with a 
    // separator (e.g. '\') character, so we correct for this if needed.
    if(path && *path)
	{

		const size_t nStrlen = strlen(path);

		if((path[nStrlen - 1] != '/') && (path[nStrlen - 1] != '\\'))
		{
			#if defined(EA_PLATFORM_MICROSOFT)
				return (RemoveDirectoryA(path) != 0);
			#elif defined(EA_PLATFORM_UNIX) || defined(CS_UNDEFINED_STRING)
				return (rmdir(path) == 0);
			#endif
		}

		// Else we need to remove the separator.
		char pathMod[EA::WebKit::FileSystem::kMaxPathLength];
		EAW_ASSERT_MSG(nStrlen < EA::WebKit::FileSystem::kMaxPathLength, "Directory path exceeds max path length");
		memcpy(pathMod, path, nStrlen - 1);   // Force 0 terminator in place of directory separator
		pathMod[nStrlen - 1] = 0;

		return DeleteDirectory(pathMod);  // Call ourselves recursively.
	}
	
	return false;
}