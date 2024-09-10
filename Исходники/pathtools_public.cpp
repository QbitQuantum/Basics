/** Sets the path of the current working directory. Returns true if this was successful. */
bool Path_SetWorkingDirectory(const std::string& sPath)
{
	bool bSuccess;
#if defined( _WIN32 )
	std::wstring wsPath = UTF8to16(sPath.c_str());
	bSuccess = 0 == _wchdir(wsPath.c_str());
#else
	bSuccess = 0 == chdir(sPath.c_str());
#endif
	return bSuccess;
}