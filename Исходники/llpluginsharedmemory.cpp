bool LLPluginSharedMemory::attach(const std::string &name, size_t size)
{
	mName = name;
	mSize = size;

	mImpl->mMapFile = OpenFileMappingA(
				FILE_MAP_ALL_ACCESS,		// read/write access
				FALSE,						// do not inherit the name
				mName.c_str());				// name of mapping object
	
	if(mImpl->mMapFile == NULL)
	{
		LL_WARNS("Plugin") << "OpenFileMapping failed: " << GetLastError() << LL_ENDL;
		return false;
	}
		
	return map();
}