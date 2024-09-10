bool PLH::IATHook::FindIATFunc(const char* LibraryName,const char* FuncName, PIMAGE_THUNK_DATA* pFuncThunkOut,const char* Module)
{
	bool UseModuleName = true;
	if (Module == NULL || Module[0] == '\0')
		UseModuleName = false;

	HINSTANCE hInst = GetModuleHandleA(UseModuleName ? Module:NULL);
	if (!hInst)
	{
		PostError(RuntimeError(RuntimeError::Severity::UnRecoverable, "PolyHook IATHook:Failed to find Module"));
		return false;
	}

	ULONG Sz;
	PIMAGE_IMPORT_DESCRIPTOR pImports = (PIMAGE_IMPORT_DESCRIPTOR)
		ImageDirectoryEntryToDataEx(hInst, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &Sz, nullptr);

	for (int i = 0; pImports[i].Characteristics != 0; i++)
	{
		char* _ModuleName = (char*)ResolveRVA(hInst, pImports[i].Name);
		if (_stricmp(_ModuleName, LibraryName) != 0)
			continue;

		//Original holds the API Names
		PIMAGE_THUNK_DATA pOriginalThunk = (PIMAGE_THUNK_DATA)
			ResolveRVA(hInst, pImports->OriginalFirstThunk);

		//FirstThunk is overwritten by loader with API addresses, we change this
		PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)
			ResolveRVA(hInst, pImports->FirstThunk);
		
		if (!pOriginalThunk)
		{
			PostError(RuntimeError(RuntimeError::Severity::Critical, "PolyHook IATHook:PE Files without OriginalFirstThunk are unsupported"));
			return false;
		}

		//Table is null terminated, increment both tables
		for (; pOriginalThunk->u1.Function != NULL; pOriginalThunk++,pThunk++)
		{
			if (IMAGE_SNAP_BY_ORDINAL(pOriginalThunk->u1.Ordinal))
			{
				XTrace("Import By Ordinal:[Ordinal:%d]\n",IMAGE_ORDINAL(pOriginalThunk->u1.Ordinal));
				continue;
			}

			PIMAGE_IMPORT_BY_NAME pImport = (PIMAGE_IMPORT_BY_NAME)
				ResolveRVA(hInst, pOriginalThunk->u1.AddressOfData);

			XTrace("Import By Name: [Ordinal:%d] [Name:%s]\n", IMAGE_ORDINAL(pOriginalThunk->u1.Ordinal),pImport->Name);

			//Check the name of API given by OriginalFirthThunk
			if (_stricmp(FuncName, pImport->Name) != 0)
				continue;
			
			/*Name matched in OriginalFirstThunk, return FirstThunk
			so we can changed it's address*/
			*pFuncThunkOut = pThunk;
			return true;
		}
	}
	PostError(RuntimeError(RuntimeError::Severity::UnRecoverable, "PolyHook IATHook:Failed to find import"));
	return false;
}