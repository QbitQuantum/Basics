static int filefind_index_number_of_links_helper(lua_State* L, struct FileFindInfo* info) {
#if defined(_WIN32)
	HANDLE handle;
	BY_HANDLE_FILE_INFORMATION fileInformation;

	char fullPath[MAX_PATH];
	strcpy(fullPath, info->path);
	strcat(fullPath, info->fd.cFileName);

	handle = CreateFile(fullPath, 0, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (handle == INVALID_HANDLE_VALUE) {
		lua_pushnumber(L, 0);
		return 1;
	}
	if (GetFileInformationByHandle(handle, &fileInformation) == FALSE) {
		CloseHandle(handle);
		lua_pushnumber(L, 0);
		return 1;
	}
	CloseHandle(handle);

	lua_pushnumber(L, fileInformation.nNumberOfLinks);
#else
	lua_pushnumber(L, 0);
#endif
	return 1;
}