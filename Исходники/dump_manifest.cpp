PIMAGE_RESOURCE_DIRECTORY_ENTRY
FindResourceDirectoryEntryWithName(PVOID root, PIMAGE_RESOURCE_DIRECTORY rd, LPCWSTR name)
{
	PIMAGE_RESOURCE_DIRECTORY_ENTRY entry;
	entry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY) GetPtr(rd, sizeof(*rd));

	ULONG cnt = rd->NumberOfNamedEntries + rd->NumberOfIdEntries;

	for(ULONG i = 0; i < cnt; ++i)
	{
		if(entry[i].NameIsString)
		{
			PIMAGE_RESOURCE_DIR_STRING_U rname;
			rname = (PIMAGE_RESOURCE_DIR_STRING_U) GetPtr(root, entry[i].NameOffset);

			WCHAR tmp[MAX_PATH];
			StringCbCopyNW(tmp, sizeof(tmp), rname->NameString, rname->Length);

			if(wcscmp(tmp, name) == 0)
				return &entry[i]; 
		}
	}

	return NULL;
}