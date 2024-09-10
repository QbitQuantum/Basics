HANDLE
ApsOpenSourceFile(
	__in PWSTR SourceFolder,
	__in PWSTR SpecifiedPath,
	__out PWSTR *RealPath
	)
{
	HANDLE FileHandle;
	size_t Size;
	size_t Count;
	BOOL Status;
	LIST_ENTRY ListHead;
	PLIST_ENTRY ListEntry;
	PSTRING_ENTRY Entry;
	PWSTR Buffer;
	WCHAR BaseName[MAX_PATH];
	WCHAR ExtentName[16];

	*RealPath = NULL;
	FileHandle = INVALID_HANDLE_VALUE;

	ASSERT(SpecifiedPath != NULL);
	ASSERT(RealPath != NULL);

	if (!SourceFolder) {

		//
		// If source folder is not specified, directly open
		// the file by given path
		//

		FileHandle = CreateFile(SpecifiedPath, GENERIC_READ, 
								FILE_SHARE_READ, NULL, OPEN_EXISTING, 
								FILE_ATTRIBUTE_NORMAL, NULL);

		if (FileHandle == INVALID_HANDLE_VALUE) {
			return INVALID_HANDLE_VALUE;
		}

		//
		// Duplicate specified string to real path
 		//

		Count = wcslen(SpecifiedPath) + 1;
		Size = Count * sizeof(WCHAR);
		*RealPath = (PWSTR)ApsMalloc(Size);
		wcscpy_s(*RealPath, Count, SpecifiedPath);

		return FileHandle;
	}

	//
	// Build source file base name
	//

	BaseName[0] = 0;
	ExtentName[0] = 0;

	_wsplitpath(SpecifiedPath, NULL, NULL, BaseName, ExtentName);
	if (ExtentName[0] != 0) {
		wcscat(BaseName, ExtentName);
	}

	Buffer = (PWSTR)ApsMalloc(APS_PAGESIZE);

	//
	// Build source folder list
	//

	InitializeListHead(&ListHead);
	ApsSplitUnicodeString(SourceFolder, L';', &ListHead);

	//
	// Enum each source folder to scan the file
	//

	Status = FALSE;
	while (IsListEmpty(&ListHead) != TRUE) {

		ListEntry = RemoveHeadList(&ListHead);
		Entry = CONTAINING_RECORD(ListEntry, STRING_ENTRY, ListEntry);
		Status = SearchTreeForFileW((PCWSTR)Entry->Buffer, BaseName, Buffer);

		if (Status) {
			*RealPath = Buffer;
			break;
		}

		ApsFree(Entry->Buffer);
		ApsFree(Entry);
	}

	//
	// Clean other folder strings
	//

	while (IsListEmpty(&ListHead) != TRUE) {
		ListEntry = RemoveHeadList(&ListHead);
		Entry = CONTAINING_RECORD(ListEntry, STRING_ENTRY, ListEntry);
		ApsFree(Entry->Buffer);
		ApsFree(Entry);
	}

	if (Status) {

		//
		// Open the source file
		//

		FileHandle = CreateFile(Buffer, GENERIC_READ, 
								FILE_SHARE_READ, NULL, OPEN_EXISTING, 
								FILE_ATTRIBUTE_NORMAL, NULL);

		if (FileHandle == INVALID_HANDLE_VALUE) {
			ApsFree(Buffer);
			*RealPath = NULL;
		}
	}
	
	return FileHandle;
}