bool MCFileSystemListEntries(const char *p_folder, uint32_t p_options, MCFileSystemListCallback p_callback, void *p_context)
{
	bool t_success;
	t_success = true;

	char *t_pattern;
	t_pattern = nil;
	if (t_success)
		t_success = MCCStringFormat(t_pattern, "%s%s", p_folder, MCCStringEndsWith(p_folder, "/") ? "*" : "/*");

	void *t_native_pattern;
	t_native_pattern = nil;
	if (t_success)
		t_success = MCFileSystemPathToNative(t_pattern, t_native_pattern);

	HANDLE t_find_handle;
	WIN32_FIND_DATAW t_find_data;
	t_find_handle = INVALID_HANDLE_VALUE;
	if (t_success)
	{
		t_find_handle = FindFirstFileW((LPCWSTR)t_native_pattern, &t_find_data);
		if (t_find_handle == INVALID_HANDLE_VALUE)
			t_success = false;
	}

	while(t_success)
	{
		char *t_entry_filename;
		if (t_success)
			t_success = MCFileSystemPathFromNative(t_find_data . cFileName, t_entry_filename);

		MCFileSystemEntry t_entry;
		if (t_success)
		{
			t_entry . type = (t_find_data . dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ? kMCFileSystemEntryFolder : kMCFileSystemEntryFile;
			MCStringCreateWithCString(t_entry_filename, t_entry.filename);
			//t_entry . filename = t_entry_filename;

			t_success = p_callback(p_context, t_entry);
		}

		MCCStringFree(t_entry_filename);

		////

		if (!FindNextFileW(t_find_handle, &t_find_data))
		{
			if (GetLastError() == ERROR_NO_MORE_FILES)
				break;

			t_success = false;
		}
	}

	if (t_find_handle != INVALID_HANDLE_VALUE)
		FindClose(t_find_handle);

	MCMemoryDeallocate(t_native_pattern);
	MCCStringFree(t_pattern);

	return t_success;
}