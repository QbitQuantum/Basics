std::string WorkspaceGenerator_MSVC8::get_project_guid(const std::string &project)
{
	std::string returnGUID;

	// Check if we already made a GUID earlier. Reuse it if we did.
	LONG result;
	HKEY key = 0;
	result = RegCreateKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Clanlib.org\\ClanLib\\ProjectGUIDs", &key);
	if (result != ERROR_SUCCESS)
		key = 0;
	if (key)
	{
		DWORD type = 0, needed = 0;
		result = RegQueryValueExA(key, project.c_str(), 0, &type, 0, &needed);
		if (result == ERROR_SUCCESS && type == REG_SZ)
		{
			char *buffer = new char[needed];
			result = RegQueryValueExA(key, project.c_str(), 0, &type, (LPBYTE) buffer, &needed);
			if (result == ERROR_SUCCESS)
			{
				returnGUID = buffer;
				delete[] buffer;
				RegCloseKey(key);
				return returnGUID;
			}
			delete[] buffer;
		}
	}

	// Create a new GUID:
	unsigned char *projectGUID = 0;
	GUID guid;
	UuidCreate(&guid);
	UuidToStringA(&guid, &projectGUID);
	_strupr((char *) projectGUID);
	returnGUID = std::string("{") + ((char *) projectGUID) + std::string("}");
	RpcStringFreeA(&projectGUID);

	// Save it to registry:
	if (key)
	{
		result = RegSetValueExA(
			key,
			project.c_str(),
			0,
			REG_SZ,
			(LPBYTE) returnGUID.c_str(),
			(DWORD) returnGUID.length()+1);
		RegCloseKey(key);
	}

	return returnGUID;
}